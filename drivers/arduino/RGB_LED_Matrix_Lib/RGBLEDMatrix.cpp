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

const unsigned long UPDATE_INTERVAL = 300;

RGBLEDMatrix::RGBLEDMatrix( 
	int rows,
	int columns
) :		TimerAction(UPDATE_INTERVAL),
		_rows(rows),
		_columns(columns),
		_screen_data(rows,columns),
		_screen_buf(rows,columns),
		_screenBits(rows,columns*3),
		_spi()
{
	_cycleCount = 0;
	_scanPass = 0;
	_scanRow = rows-1;
	_priorRow = rows-2;
  
  	// sett everything off
  	shiftOutAllOff();
}

void RGBLEDMatrix::shiftOutAllOff() {
	// before scanning the first row, turn off the prior row completely. The prior row
	// would be the bottom row on the matrix. If the switching transistor is slow,
	// it would still be partially on when the first row is turned on causing the LEDs
	// to glow slightly since the electrical path to the transistor transitioning off 
	// shorter (less resistance)

	// shift out any needed pad bits
// 	_spiCache.shiftNLowBits(_spiPadBits);
// 	_spiCache.shiftNLowBits(_columns*3);
// 	_spiCache.shiftNHighBits(_rows);
}

#define MAX_SCAN_PASS_COUNT 8
inline int RGBLEDMatrix::maxScanCountForValue(unsigned char value) {
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
			return 4;
			break;
		case B00110000:
		case B00001100:
		case B00000011:		
		default:
			return MAX_SCAN_PASS_COUNT;
			break;
	}

}

void RGBLEDMatrix::shiftOutCurrentRow() {
	
	if (!_screenBits.isRowMemoized(_scanRow)) {
		bool rowNeedsPower = false;
		size_t colBitIdex = 0;
		for (int col = 0; col < _columns; col++) {
			short rgbValue = _screen_data.pixel(_scanRow, col);

			// a form of Binary Code Modulation is used to control
			// the LED intensity at variou levels.
		
			// red
			short redValue = rgbValue & RED_MASK;
			if (redValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(redValue) ) {
				_screenBits.setColumnControlBit(_scanRow,colBitIdex,true);
				rowNeedsPower = true;
			}
			colBitIdex++;
			
			// green
			short greenValue = rgbValue & GREEN_MASK;
			if (greenValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(greenValue) ) {
				_screenBits.setColumnControlBit(_scanRow,colBitIdex,true);
				rowNeedsPower = true;
			}
			colBitIdex++;
					
			// blue
			short blueValue = (rgbValue & BLUE_MASK);
			if (blueValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(blueValue) ) {
				_screenBits.setColumnControlBit(_scanRow,colBitIdex,true);
				rowNeedsPower = true;
			}
			colBitIdex++;
			
		}
	
		_screenBits.setRowControlBit(_scanRow,rowNeedsPower);
	}
	
	_screenBits.transmitRow(_scanRow,_spi);
}
void RGBLEDMatrix::action() {    
	_priorRow = _scanRow;
	_scanRow++;
	if (_scanRow >= _rows) {
		_scanRow = 0;
		_scanPass++;
		if (_scanPass >= MAX_SCAN_PASS_COUNT) {
			_scanPass = 1;
			_cycleCount++;
		}
		if ( _scanPass == 1 || _scanPass == 2 || _scanPass == 5) {
			_screenBits.reset();
		}
	}

	// if this is row 0 for scan pass zero, copy the buffer 
	// to the data space if dirty
	if (_scanRow == 0 && _scanPass == 1 && !_drawingActive && _screen_buf.isDirty()) {
		_screen_data.copy(_screen_buf);
		_screen_buf.setNotDirty();
		_screenBits.reset();
	}

	this->shiftOutCurrentRow();
}
