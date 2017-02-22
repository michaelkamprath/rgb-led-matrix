//     RGB Matrix Project - Glyph
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
#include "Glyph.h"

#define BYTE_BUFFER_SIZE(rows,cols) ((rows*cols/8) + (rows*cols%8 == 0 ? 0 : 1))

// pre-calculate the bit masks to speed up over: 1<<(7-bitIdx%8)
const unsigned char BIT_MASKS[8] = {
		B10000000,
		B01000000,
		B00100000,
		B00010000,
		B00001000,
		B00000100,
		B00000010,
		B00000001
	};

// if byte buffer is passed, glyph will keep that for the data store
// in order to reduce overall memory usage.
Glyph::Glyph( int rows, int columns, unsigned char* data )
	: 	_rows( rows ),
		_columns( columns ),
		_data( data != NULL ? data : new unsigned char[BYTE_BUFFER_SIZE(rows,columns)] ),
		_manageData( data != NULL ? false : true )
{
	if ( NULL == data ) {
		memset(_data, 0, BYTE_BUFFER_SIZE(rows,columns));
	} 
}

Glyph::Glyph( const Glyph& other )
	: 	_rows( other._rows ),
		_columns( other._columns ),
		_data(new unsigned char[BYTE_BUFFER_SIZE(other._rows,other._columns)]),
		_manageData( true )
{
	memcpy(_data, other._data, BYTE_BUFFER_SIZE(_rows,_columns));
}

Glyph::~Glyph() {
	if (_manageData) {
		delete _data;
	}
}
void Glyph::setBit( int row, int column ) {
	int bitIdx = row*this->columns() + column;
	
	_data[bitIdx/8] |= BIT_MASKS[bitIdx%8];
}
void Glyph::clearBit( int row, int column ) {
	int bitIdx = row*this->columns() + column;

	_data[bitIdx/8] &= ~BIT_MASKS[bitIdx%8];
}

bool Glyph::getBit( int row, int column ) const {
	int bitIdx = row*this->columns() + column;
	
	return ( ( _data[bitIdx/8] & BIT_MASKS[bitIdx%8] ) != 0 );
}

