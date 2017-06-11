//     RGB Matrix Project - RGBLEDMatrix
//     Copyright (C) 2017 Michael Kamprath
//
//     This file is part of RGB Matrix Project.
// 
//     RGB Matrix Project is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     RGB Matrix Project is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with RGB Matrix Project.  If not, see <http://www.gnu.org/licenses/>.

#include <Arduino.h>
#include "RGBLEDMatrix.h"

#define SPICACHEPADBITS(rows,cols)	(rows*3 + cols)%8 ? 8 - (rows*3 + cols)%8 : 0
#define SPICACHESIZE(rows,cols)	1+((rows*3 + cols)-1)/8

#define MAX_SCAN_PASS_COUNT 8
const unsigned long UPDATE_INTERVAL = 300;

RGBLEDMatrix* gSingleton = 0;
unsigned int gtcnt2StartValue;

RGBLEDMatrix::RGBLEDMatrix( 
	int rows,
	int columns
) :		TimerAction(UPDATE_INTERVAL),
		_rows(rows),
		_columns(columns),
		_screen_data(rows,columns),
		_screenBitFrames(),
		_spi()
{
	if (gSingleton == nullptr) {
		gSingleton = this;
	}

	_screenBitFrames[0] = new LEDMatrixBits(rows, columns*3);
	_screenBitFrames[1] = new LEDMatrixBits(rows, columns*3);
	_screenBitFrames[2] = new LEDMatrixBits(rows, columns*3);
	_screenBitFrames[3] = new LEDMatrixBits(rows, columns*3);
	_screenBitFrames[4] = new LEDMatrixBits(rows, columns*3);
	_screenBitFrames[5] = new LEDMatrixBits(rows, columns*3);
	_curScreenBitFrames = &_screenBitFrames[0];
	_screenBigFrameToggle = false;
	
	_scanPass = 1;
	_scanRow = 0;
}

size_t RGBLEDMatrix::maxFrameCountForValue(unsigned char value) {
	switch (value) {
		case 0:
			return 0;
			break;
		case B00010000:
		case B00000100:
		case B00000001:
			return 1;
			break;
		case B00100000:
		case B00001000:
		case B00000010:		
			return 2;
			break;
		case B00110000:
		case B00001100:
		case B00000011:		
		default:
			return 3;
			break;
	}
}

void RGBLEDMatrix::copyScreenDataToBits(const RGBImage& image) {
	size_t idxOffset = 0;
	if (!_screenBigFrameToggle) {
		idxOffset = 3;
	}

	_screenBitFrames[0+idxOffset]->reset();
	_screenBitFrames[1+idxOffset]->reset();
	_screenBitFrames[2+idxOffset]->reset();

	for (int row = 0; row < this->rows(); row++) {
		this->setRowBitsForFrame(row, 1, _screenBitFrames[0+idxOffset], image);
		this->setRowBitsForFrame(row, 2, _screenBitFrames[1+idxOffset], image);
		this->setRowBitsForFrame(row, 3, _screenBitFrames[1+idxOffset], image);
	}
	
	noInterrupts(); // disable all interrupts
	_screenBigFrameToggle = !_screenBigFrameToggle;
	_curScreenBitFrames = &_screenBitFrames[0+idxOffset];
	interrupts(); // enable all interrupts
}

void RGBLEDMatrix::setRowBitsForFrame(
	int row,
	size_t frame,
	LEDMatrixBits* framePtr,
	const RGBImage& image
) {	
	if (!framePtr->isRowMemoized(row)) {
		bool rowNeedsPower = false;
		size_t colBitIdex = 0;
		for (int col = 0; col < _columns; col++) {
			short rgbValue = image.pixel(row, col);

			// a form of Binary Code Modulation is used to control
			// the LED intensity at variou levels.
		
			// red
			short redValue = rgbValue & RED_MASK;
			if (redValue && frame <= RGBLEDMatrix::maxFrameCountForValue(redValue) ) {
				framePtr->setColumnControlBit(row,colBitIdex,true);
				rowNeedsPower = true;
			}
			colBitIdex++;
			
			// green
			short greenValue = rgbValue & GREEN_MASK;
			if (greenValue && frame <= RGBLEDMatrix::maxFrameCountForValue(greenValue) ) {
				framePtr->setColumnControlBit(row,colBitIdex,true);
				rowNeedsPower = true;
			}
			colBitIdex++;
					
			// blue
			short blueValue = (rgbValue & BLUE_MASK);
			if (blueValue && frame <= RGBLEDMatrix::maxFrameCountForValue(blueValue) ) {
				framePtr->setColumnControlBit(row,colBitIdex,true);
				rowNeedsPower = true;
			}
			colBitIdex++;
			
		}
	
		framePtr->setRowControlBit(row,rowNeedsPower);
	}	
}

void RGBLEDMatrix::shiftOutRow( int row, int scanPass ) {
	int frameIdx = 0;
	if (scanPass > 4) {
		frameIdx = 2;
	} else if (scanPass > 1) {
		frameIdx = 1;
	}
	_curScreenBitFrames[frameIdx]->transmitRow(row, _spi);
}

void RGBLEDMatrix::shiftOutCurrentRow( void ) {
	this->shiftOutRow( _scanRow, _scanPass );
	
	_scanRow++;
	if (_scanRow >= this->rows()) {
		_scanRow = 0;
		_scanPass++;
		if (_scanPass >= MAX_SCAN_PASS_COUNT) {
			_scanPass = 1;
		}
	}	
}

void RGBLEDMatrix::action() {    
	// if this is row 0 for scan pass zero, copy the buffer 
	// to the data space if dirty
	if (_scanRow == 0 && _scanPass == 1 && !_drawingActive && _screen_data.isDirty()) {
	
		this->copyScreenDataToBits(_screen_data);
		_screen_data.setNotDirty();
	}
}

void RGBLEDMatrix::startScanning(void) {
	noInterrupts(); // disable all interrupts
	
  	TIMSK2 &= ~(1<<TOIE2); // disable timer overflow interupt

	// SET timer2 to count up mode
	TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
	TCCR2B &= ~(1<<WGM22);

	// set clock to I/O clock
  	ASSR &= ~(1<<AS2);
 
  	// overflow only mode
  	TIMSK2 &= ~(1<<OCIE2A);
  	
  	// configure to fire about every 100us
	TCCR2B |= (1<<CS22) | (1<<CS20); 
	TCCR2B &= ~(1<<CS21);
 
	/* We need to calculate a proper value to load the timer counter.
	 * (CPU frequency) / (prescaler value) = 125000 Hz = 8us.
	 * 100us / 8us = 12.5 --> 13.
	 * MAX(uint8) + 1 - 13 = 244;
	 */
	gtcnt2StartValue = 244; 
 
	// load counter start point and enable the timer
	TCNT2 = gtcnt2StartValue;
	TIMSK2 |= (1<<TOIE2);
	
  	interrupts(); // enable all interrupts
}

void stopScanning(void) {
  	TIMSK2 &= ~(1<<TOIE2); // disable timer overflow interupt
}

ISR(TIMER2_OVF_vect) {
	noInterrupts(); 
	// reload the timer
	TCNT2 = gtcnt2StartValue;
	// shift out next row
	gSingleton->shiftOutCurrentRow();
  	interrupts(); 
}
