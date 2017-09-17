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

// #define SPICACHEPADBITS(rows,cols)	(rows*3 + cols)%8 ? 8 - (rows*3 + cols)%8 : 0
// #define SPICACHESIZE(rows,cols)	1+((rows*3 + cols)-1)/8

const unsigned long UPDATE_INTERVAL = 2000;

RGBLEDMatrix* gSingleton = NULL;

RGBLEDMatrix::RGBLEDMatrix( 
	int rows,
	int columns,
	int slavePin,
	RGBLEDBitLayout bitLayout
) :		TimerAction(UPDATE_INTERVAL),
		_bitLayout(bitLayout),
		_rows(rows),
		_columns(columns),
		_screen_data(NULL),
		_curScreenBitFrames(NULL),
		_screenBitFrames(),
		_screenBitFrameToggle(false),
		_scanPass(1),
		_scanRow(0),
		_isDrawingCount(0),
		_spi(slavePin)
{

}

void RGBLEDMatrix::setup() {
	if (_screen_data == NULL) {
		_screen_data = new MutableRGBImage(this->rows(), this->columns());
		
		for (int i = 0; i < 2*MAX_SCAN_PASS_COUNT; i++) {
			_screenBitFrames[i] = new LEDMatrixBits(this->rows(), this->columns()*3);
		}
	
		_curScreenBitFrames = &_screenBitFrames[0];

		if (gSingleton == nullptr) {
			gSingleton = this;
		}
		
		_spi.setup();
	}
}

RGBLEDMatrix::~RGBLEDMatrix() {
	if (_screen_data != NULL) {
		delete _screen_data;
		for (int i = 0; i < 2*MAX_SCAN_PASS_COUNT; i++) {
			delete _screenBitFrames[i];
		}
		_curScreenBitFrames = NULL;
	}
}

size_t RGBLEDMatrix::maxFrameCountForValue(ColorType value) {
#if TWENTY_FOUR_BIT_COLOR
	switch (value) {
		case 0:
			return 0;
			break;
		case 0x0100:
		case 0x0010:
		case 0x0001:
			return 1;
			break;
		case 0x0200:
		case 0x0020:
		case 0x0002:
			return 2;
			break;
		case 0x0300:
		case 0x0030:
		case 0x0003:
			return 3;
			break;
		case 0x0400:
		case 0x0040:
		case 0x0004:
			return 4;
			break;
		case 0x0500:
		case 0x0050:
		case 0x0005:
			return 5;
			break;
		case 0x0600:
		case 0x0060:
		case 0x0006:
			return 6;
			break;
		case 0x0700:
		case 0x0070:
		case 0x0007:
			return 7;
			break;
		case 0x0800:
		case 0x0080:
		case 0x0008:
			return 8;
			break;
		case 0x0900:
		case 0x0090:
		case 0x0009:
			return 9;
			break;
		case 0x0A00:
		case 0x00A0:
		case 0x000A:
			return 10;
			break;
		case 0x0B00:
		case 0x00B0:
		case 0x000B:
			return 11;
			break;
		case 0x0C00:
		case 0x00C0:
		case 0x000C:
			return 12;
			break;
		case 0x0D00:
		case 0x00D0:
		case 0x000D:
			return 13;
			break;
		case 0x0E00:
		case 0x00E0:
		case 0x000E:
			return 14;
			break;
		case 0x0F00:
		case 0x00F0:
		case 0x000F:
			return 15;
			break;
		default:
			return MAX_SCAN_PASS_COUNT;
			break;
	}
#else
	// we expect only on of the 4 bit sets in the value to be on
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
			return MAX_SCAN_PASS_COUNT;
			break;
	}
#endif
}

void RGBLEDMatrix::setRowBitsForFrame(
	int row,
	size_t frame,
	LEDMatrixBits* framePtr,
	const RGBImageBase& image
) {	
	if (!framePtr->isRowMemoized(row)) {
		bool rowNeedsPower = false;
		size_t colBitIdx = 0;
		size_t redBitOffset = 0;
		size_t greenBitOffset = 1;
		size_t blueBitOffset = 2;
		size_t columnBitIdxIncrement = 3;
		if (_bitLayout == RGB_GROUPS) {
			redBitOffset = 0;
			greenBitOffset = this->columns();
			blueBitOffset = 2*this->columns();
			columnBitIdxIncrement = 1;
		}
		for (int col = 0; col < _columns; col++) {
			ColorType rgbValue = image.pixel(row, col);
			
			// a form of Binary Code Modulation is used to control
			// the LED intensity at variou levels.
		
			// red
			ColorType redValue = rgbValue & RED_MASK;
			if (redValue && frame <= RGBLEDMatrix::maxFrameCountForValue(redValue) ) {
				framePtr->setColumnControlBit(row,colBitIdx+redBitOffset,true);
				rowNeedsPower = true;
			}
			
			// green
			ColorType greenValue = rgbValue & GREEN_MASK;
			if (greenValue && frame <= RGBLEDMatrix::maxFrameCountForValue(greenValue) ) {
				framePtr->setColumnControlBit(row,colBitIdx+greenBitOffset,true);
				rowNeedsPower = true;
			}
					
			// blue
			ColorType blueValue = (rgbValue & BLUE_MASK);
			if (blueValue && frame <= RGBLEDMatrix::maxFrameCountForValue(blueValue) ) {
				framePtr->setColumnControlBit(row,colBitIdx+blueBitOffset,true);
				rowNeedsPower = true;
			}
			colBitIdx += columnBitIdxIncrement;
			
		}		
		framePtr->setRowControlBit(row,rowNeedsPower);
	}	
}


void RGBLEDMatrix::shiftOutCurrentRow( void ) {
	this->shiftOutRow( _scanRow, _scanPass );
}


void RGBLEDMatrix::action() {    
	// if this is row 0 for scan pass zero, copy the buffer 
	// to the data space if dirty
	if (!this->isDrawing() ) {
		if (this->image().isDirty()) {
			this->copyScreenDataToBits(this->image());
			this->image().setNotDirty();
		}
	} 
}


void RGBLEDMatrix::copyScreenDataToBits(const RGBImageBase& image) {
	size_t idxOffset = 0;
	if (!_screenBitFrameToggle) {
		idxOffset = MAX_SCAN_PASS_COUNT;
	}

	for (int i = 0; i < MAX_SCAN_PASS_COUNT; i++) {
		_screenBitFrames[i+idxOffset]->reset();		
	}

	for (int row = 0; row < this->rows(); row++) {
		for (int i = 0;  i < MAX_SCAN_PASS_COUNT; i++) {
			this->setRowBitsForFrame(row, i+1, _screenBitFrames[i+idxOffset], image);
		}
	}
	
	noInterrupts(); // disable all interrupts
	_screenBitFrameToggle = !_screenBitFrameToggle;
	_curScreenBitFrames = &_screenBitFrames[0+idxOffset];
	interrupts(); // enable all interrupts
}

void RGBLEDMatrix::shiftOutRow( int row, int scanPass ) {
	_curScreenBitFrames[scanPass-1]->transmitRow(row, _spi);
}

void RGBLEDMatrix::incrementScanRow( void ) {	
	_scanRow++;
	if (_scanRow >= this->rows()) {
		_scanRow = 0;
		_scanPass++;
		if (_scanPass > MAX_SCAN_PASS_COUNT) {
			_scanPass = 1;
		}
	}
}


#if (defined(__arm__) && defined(TEENSYDUINO))
//
// On the Teensy ARM boards, use the TimerThree library to drive scan timing
//
#include <TimerThree.h>

void time3InteruptHandler( void ) {
	Timer3.stop();
	gSingleton->shiftOutCurrentRow();
	// reload the timer
	Timer3.setPeriod(gSingleton->nextTimerInterval());
  	Timer3.start(); 
  	// update scan row. Done outside of interrupt stoppage since execution time can
  	// be inconsistent, which would lead to vary brightness in rows.
  	gSingleton->incrementScanRow();
	
}

void RGBLEDMatrix::startScanning(void) {
	this->setup();
	
	Timer3.initialize(this->nextTimerInterval());
	Timer3.attachInterrupt(time3InteruptHandler);
	Timer3.start();
}

void stopScanning(void) {
	Timer3.stop();
	Timer3.detachInterrupt();
}

unsigned int RGBLEDMatrix::nextTimerInterval(void) const {
	// Calculates the microseconds for each scan
	int mulitplier = _scanPass*1.25;	
	
	return  5*mulitplier;
}

#elif defined(ARDUINO_SAMD_ZERO)||defined(_SAM3XA_)
// no timer code for the Due or Zero yet

#else
//
// On normal Arduino board (Uno, Nano, etc), use the timer interrupts to drive the
// scan timing. 
//

#define BASE_SCAN_TIMER_INTERVALS 12

void RGBLEDMatrix::startScanning(void) {
	this->setup();

	noInterrupts(); // disable all interrupts
	
  	TIMSK2 &= ~(1<<TOIE2); // disable timer overflow interupt

	// SET timer2 to count up mode
	TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
	TCCR2B &= ~(1<<WGM22);

	// set clock to I/O clock
  	ASSR &= ~(1<<AS2);
 
  	// overflow only mode
  	TIMSK2 &= ~(1<<OCIE2A);
  	
  	// configure to fire about every 5 micro-second 
	TCCR2B |= (1<<CS22) ; 
	TCCR2B &= ~(1<<CS20);
	TCCR2B &= ~(1<<CS21);

	// load counter start point and enable the timer
	TCNT2 = this->nextTimerInterval();
	TIMSK2 |= (1<<TOIE2);
	
  	interrupts(); // enable all interrupts
}

void stopScanning(void) {
  	TIMSK2 &= ~(1<<TOIE2); // disable timer overflow interupt
}

unsigned int RGBLEDMatrix::nextTimerInterval(void) const {
	int mulitplier = 1;
#if TWENTY_FOUR_BIT_COLOR
	mulitplier = _scanPass/4+1;
#else
	switch (_scanPass) {
		case 2:
			mulitplier = 3;
			break;
		case 3:
			mulitplier = 8;
			break;
	}
#endif

	return  max(257-mulitplier*BASE_SCAN_TIMER_INTERVALS, 0 );
}


ISR(TIMER2_OVF_vect) {
	noInterrupts(); 
	// shift out next row
	gSingleton->shiftOutCurrentRow();
	// reload the timer
	TCNT2 = gSingleton->nextTimerInterval();
  	interrupts(); 
  	// update scan row. Done outside of interrupt stoppage since execution time can
  	// be inconsistent, which would lead to vary brightness in rows.
  	gSingleton->incrementScanRow();
}
#endif
