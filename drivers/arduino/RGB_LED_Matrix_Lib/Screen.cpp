//     RGB Matrix Project - Screen
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
#include "Screen.h"

Screen::Screen( 
	int rows,
	int columns,
	int latchPin,
	int clockPin,
	int dataPin
) :		TimerAction(100),
		_latchPin(latchPin),
		_clockPin(clockPin),
		_dataPin(dataPin),
		_rows(rows),
		_columns(columns),
		_screen_data(rows,columns),
		_screen_buf(rows,columns)
{
	_scanPass = 1;
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
}

void Screen::shiftOutBit( uint8_t bitValue ) {
	digitalWrite(_clockPin, LOW);
	digitalWrite(_dataPin, bitValue);
	digitalWrite(_clockPin, HIGH);
}

void Screen::action() {    
	digitalWrite(_latchPin, LOW);

	// if this is row 0 for scan pass zero, copy the buffer 
	// to the data space if dirty
	if (_scanRow == 0 && _scanPass == 1 && !_drawingActive) {
		_screen_data.copy(_screen_buf);
	}
	// first, turn everything off to account for slow switching transistors on the rows 
	// and slow 74HC595 that may "leak" some power into the last turned off row by still 
	// be partially on when the new row turn on.
	
    for (int i = 0; i < _columns; i++) {
        shiftOutBit(HIGH); // red
        shiftOutBit(HIGH); // green
        shiftOutBit(HIGH); // blue
    }
	for (int i = _rows - 1; i >= 0; i-- ) {
		shiftOutBit(HIGH);
	}
	
	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);


	for (int col = 0; col < _columns; col++) {
		short rgbValue = _screen_data.pixel(_scanRow,col);

		// a form of Binary Code Modulation is used to control
		// the LED intensity at variou levels.
		
		// red
		short redValue = (rgbValue & RED_MASK)>>RED_BIT_SHIFT;
		if (redValue && _scanPass <= redValue*redValue ) {
			shiftOutBit(LOW);
		}
		else {
			shiftOutBit(HIGH);
		}

		// green
		short greenValue = (rgbValue & GREEN_MASK)>>GREEN_BIT_SHIFT;
		if (greenValue && _scanPass <= greenValue*greenValue ) {
			shiftOutBit(LOW);
		}
		else {
			shiftOutBit(HIGH);
		}

		// blue
		short blueValue = (rgbValue & BLUE_MASK)>>BLUE_BIT_SHIFT;
		if (blueValue && _scanPass <= blueValue*blueValue ) {
			shiftOutBit(LOW);
		}
		else {
			shiftOutBit(HIGH);
		}
	}
	
		// now write out the row bits
	for (int i = _rows - 1; i >= 0; i-- ) {
		if (i == _scanRow) {
			// shift out row bit
			shiftOutBit(LOW);
		}
		else {
			shiftOutBit(HIGH);
		}
	}

	digitalWrite(_latchPin, HIGH);

	_scanRow++;
	if (_scanRow >= _rows) {
		_scanRow = 0;
		_scanPass++;
		if (_scanPass >= 9) {
			_scanPass = 1;
		}
	}
}
