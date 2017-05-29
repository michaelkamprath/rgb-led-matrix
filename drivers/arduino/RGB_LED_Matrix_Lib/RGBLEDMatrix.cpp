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

const unsigned long UPDATE_INTERVAL = 350;

RGBLEDMatrix::RGBLEDMatrix( 
	int rows,
	int columns,
	int latchPin
) :		TimerAction(UPDATE_INTERVAL),
		_latchPin(latchPin),
		_rows(rows),
		_columns(columns),
		_screen_data(rows,columns),
		_screen_buf(rows,columns),
		_spiCache(SPICACHESIZE(rows,columns)),
		_spiPadBits(SPICACHEPADBITS(rows,columns))
{
	_scanPass = 1;
	_scanRow = 0;
	_priorRow = rows-1;
	pinMode(latchPin, OUTPUT);
	digitalWrite(_latchPin, LOW);	
  
  	// sett everything off
  	shiftOutAllOff();
	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);	
}

void RGBLEDMatrix::shiftOutAllOff() {
	// before scanning the first row, turn off the prior row completely. The prior row
	// would be the bottom row on the matrix. If the switching transistor is slow,
	// it would still be partially on when the first row is turned on causing the LEDs
	// to glow slightly since the electrical path to the transistor transitioning off 
	// shorter (less resistance)

	// shift out any needed pad bits
	_spiCache.shiftNLowBits(_spiPadBits);
	_spiCache.shiftNLowBits(_columns*3);
	_spiCache.shiftNHighBits(_rows);
}

#define MAX_SCAN_PASS_COUNT 6
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
			return 3;
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
	
	// shift out any needed pad bits
	_spiCache.shiftNLowBits(_spiPadBits);
	
	bool rowNeedsPower = false;
	for (int col = 0; col < _columns; col++) {
		short rgbValue = _screen_data.pixel(_scanRow, col);

		// a form of Binary Code Modulation is used to control
		// the LED intensity at variou levels.
		
		// red
		short redValue = rgbValue & RED_MASK;
		if (redValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(redValue) ) {
			_spiCache.shiftOutBit(LOW);
			rowNeedsPower = true;
		}
		else {
			_spiCache.shiftOutBit(HIGH);
		}

		// green
		short greenValue = rgbValue & GREEN_MASK;
		if (greenValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(greenValue) ) {
			_spiCache.shiftOutBit(LOW);
			rowNeedsPower = true;
		}
		else {
			_spiCache.shiftOutBit(HIGH);
		}

		// blue
		short blueValue = (rgbValue & BLUE_MASK);
		if (blueValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(blueValue) ) {
			_spiCache.shiftOutBit(LOW);
			rowNeedsPower = true;
		}
		else {
			_spiCache.shiftOutBit(HIGH);
		}
	}
	
	// now write out the row bits
	if (rowNeedsPower) {
		// this code design is for speed. It reduces the if-checks
		// within a loop
		_spiCache.shiftNHighBits((_rows - 1) - _scanRow);
		_spiCache.shiftOutBit(LOW);
		_spiCache.shiftNHighBits(_scanRow);
	} else {
		_spiCache.shiftNHighBits(_rows);		
	}
}
void RGBLEDMatrix::action() {    


	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);
	
	_priorRow = _scanRow;
	_scanRow++;
	if (_scanRow >= _rows) {
		_scanRow = 0;
		_scanPass++;
		if (_scanPass >= MAX_SCAN_PASS_COUNT) {
			_scanPass = 1;
		}
	}

	// if this is row 0 for scan pass zero, copy the buffer 
	// to the data space if dirty
	if (_scanRow == 0 && _scanPass == 1 && !_drawingActive) {
		_screen_data.copy(_screen_buf);
	}

	this->shiftOutCurrentRow();
}
