


#ifndef __LEDMATRIXBITTS_H__
#define __LEDMATRIXBITTS_H__
// Represents bits of each row of a LED matrix controlled by 74HC595 shift registers.
// The MSB is column 0 and LSB is row 0. New column+row control bits for each row starts
// on a byte boundary.
// If any padding is needed, that must be accounted for by user, typically via extra columns.
//


#include <Arduino.h>
#include "SPIConnection.h"

class LEDMatrixBits {
private:
	size_t _dataByteCount;
	unsigned char *_data;
	size_t _columns;
	size_t _rows;
	size_t _controlBitBytesPerRow;
	
	bool* _rowMemoized;
	
	void setNBitsTo( size_t startBit, size_t numBits, unsigned char highOrLow );
public:

	LEDMatrixBits(
			size_t rows,
			size_t columns
		);
		
	virtual ~LEDMatrixBits();

	void reset(void);
	
	int rows(void) const		{ return _rows; }
	int columns(void) const		{ return _columns; }
	
	void setAllOff(void);
	void setColumnControlBit( size_t row, size_t column, bool isOn );
	void setRowControlBit( size_t row, bool isOn );
	
	bool isRowMemoized(int row) const;
	
	void transmitRow(int row, SPIConnection& conn) const;
	
	// debug
	void streamFrameToSerial(void);
};

#endif // __LEDMATRIXBITTS_H__
