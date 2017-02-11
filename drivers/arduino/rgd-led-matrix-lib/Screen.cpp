#include <Arduino.h>
#include "Screen.h"

Screen::Screen( 
	int rows,
	int columns,
	int latchPin,
	int clockPin,
	int dataPin
) :		TimerAction(400),
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
	// that may "leak" some power into the last turned off row by still be partially on
	// when the new row turn on.
	for (int i = _rows - 1; i >= 0; i-- ) {
		shiftOutBit(HIGH);
	}
	for (int col = _columns - 1; col >= 0; col--) {
		shiftOutBit(HIGH);  // red
		shiftOutBit(HIGH);  // green
		shiftOutBit(HIGH);  // blue
	}
	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);

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

	for (int col = _columns - 1; col >= 0; col--) {
		short rgbValue = _screen_data.pixel(_scanRow,col);

		// blue
		short blueValue = (rgbValue & BLUE_MASK)>>BLUE_BIT_SHIFT;
		if (blueValue && _scanPass <= blueValue*blueValue ) {
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

		// red
		short redValue = (rgbValue & RED_MASK)>>RED_BIT_SHIFT;
		if (redValue && _scanPass <= redValue*redValue ) {
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
