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

const unsigned long UPDATE_INTERVAL = 400;

RGBLEDMatrix::RGBLEDMatrix( 
	int rows,
	int columns,
	int latchPin,
	int clockPin,
	int dataPin
) :		TimerAction(UPDATE_INTERVAL),
		_latchPin(latchPin),
		_clockPin(clockPin),
		_dataPin(dataPin),
		_rows(rows),
		_columns(columns),
		_screen_data(rows,columns),
		_screen_buf(rows,columns)
{
	_scanPass = 1;
	_scanRow = 0;
	_priorRow = rows-1;
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);

	_sclkPort = portOutputRegister(digitalPinToPort(clockPin));
	_mosiPort = portOutputRegister(digitalPinToPort(dataPin));
	_sclkMask = digitalPinToBitMask(clockPin);
	_mosiMask = digitalPinToBitMask(dataPin);
  
  	// sett everything off
	uint8_t oldSREG = SREG;
	cli();

	this->shiftOutAllOff();
	
	SREG = oldSREG;
	sei();
	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);	

}

void RGBLEDMatrix::shiftOutBit( uint8_t bitValue ) {
  	// fast writing of a bit to the shift register by directly manipulating pin state
	*_sclkPort &= ~_sclkMask;		// clock LOW
	if ( bitValue == HIGH ) {
		*_mosiPort |= _mosiMask;	// data HIGH
	} else {
		*_mosiPort &= ~_mosiMask;	// DATA LOW
	}
	*_sclkPort |= _sclkMask;		// clock HIGH
}

void RGBLEDMatrix::writeOutBit( uint8_t bitValue ) {
  	// safe writing of a bit to the shift register by using standard arduino calls
  	// to use this version, change the code in action()
	digitalWrite(_clockPin, LOW);
	digitalWrite(_dataPin, bitValue);
	digitalWrite(_clockPin, HIGH);
}

#define MAX_SCAN_PASS_COUNT 6
int RGBLEDMatrix::maxScanCountForValue(unsigned char value) {
	switch (value) {
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 3;
			break;
		case 3:
		default:
			return MAX_SCAN_PASS_COUNT;
			break;
	}

}

void RGBLEDMatrix::shiftOutAllOff() {
	// before scanning the first row, turn off the prior row completely. The prior row
	// would be the bottom row on the matrix. If the switching transistor is slow,
	// it would still be partially on when the first row is turned on causing the LEDs
	// to glow slightly since the electrical path to the transistor transitioning off 
	// shorter (less resistance)
	
	for (int i = 0; i < _columns; i++) {
		shiftOutBit(HIGH); // red
		shiftOutBit(HIGH); // green
		shiftOutBit(HIGH); // blue
	}
	for (int i = _rows - 1; i >= 0; i-- ) {
		shiftOutBit(HIGH);
	}
}
void RGBLEDMatrix::shiftOutCurrentRow() {
	
		
	bool rowNeedsPower = false;
	for (int col = 0; col < _columns; col++) {
		short rgbValue = _screen_data.pixel(_scanRow,col);

		// a form of Binary Code Modulation is used to control
		// the LED intensity at variou levels.
		
		// red
		short redValue = (rgbValue & RED_MASK)>>RED_BIT_SHIFT;
		if (redValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(redValue) ) {
			shiftOutBit(LOW);
			rowNeedsPower = true;
		}
		else {
			shiftOutBit(HIGH);
		}

		// green
		short greenValue = (rgbValue & GREEN_MASK)>>GREEN_BIT_SHIFT;
		if (greenValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(greenValue) ) {
			shiftOutBit(LOW);
			rowNeedsPower = true;
		}
		else {
			shiftOutBit(HIGH);
		}

		// blue
		short blueValue = (rgbValue & BLUE_MASK)>>BLUE_BIT_SHIFT;
		if (blueValue && _scanPass <= RGBLEDMatrix::maxScanCountForValue(blueValue) ) {
			shiftOutBit(LOW);
			rowNeedsPower = true;
		}
		else {
			shiftOutBit(HIGH);
		}
	}
		// now write out the row bits
	for (int i = _rows - 1; i >= 0; i-- ) {
		if (i == _scanRow && rowNeedsPower ) {
			// shift out row bit
			shiftOutBit(LOW);
		}
		else {
			shiftOutBit(HIGH);
		}
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


	uint8_t oldSREG = SREG;
	cli();

	this->shiftOutCurrentRow();

	SREG = oldSREG;
	sei();
}
