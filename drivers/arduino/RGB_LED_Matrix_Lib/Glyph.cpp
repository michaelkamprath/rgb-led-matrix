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

Glyph::Glyph( int rows, int columns, unsigned char* data )
	: 	_rows( rows ),
		_columns( columns ),
		_data(new unsigned char[BYTE_BUFFER_SIZE(rows,columns)])
{
	if ( NULL == data ) {
		memset(_data, 0, BYTE_BUFFER_SIZE(rows,columns));
	} else {
		// assumed passed data is properly formatted for a 2B bit array
		memcpy(_data, data, BYTE_BUFFER_SIZE(rows,columns));
	}
}

Glyph::Glyph( const Glyph& other )
	: 	_rows( other._rows ),
		_columns( other._columns ),
		_data(new unsigned char[BYTE_BUFFER_SIZE(other._rows,other._columns)])
{
	memcpy(_data, other._data, BYTE_BUFFER_SIZE(_rows,_columns));
}

Glyph::~Glyph() {
	delete _data;
}
void Glyph::setBit( int row, int column ) {
	int bitIdx = row*_columns + column;
	
	_data[bitIdx/8] |= (1U << (7 - bitIdx%8));
}
void Glyph::clearBit( int row, int column ) {
	int bitIdx = row*_columns + column;

	_data[bitIdx/8] &= ~(1U << (7 - bitIdx%8));
}

bool Glyph::getBit( int row, int column ) const {
	int bitIdx = row*_columns + column;
	
	return ( (_data[bitIdx/8] & (1U<<(7 - bitIdx%8))) != 0 );
}

RGBImage* Glyph::getImageWithColor( ColorType foreground, ColorType background ) const {
	RGBImage* img = new RGBImage( _rows, _columns );
	
	for (int y = 0; y < _rows; y++) {
		for (int x = 0; x < _columns; x++) {
			img->pixel(y, x) = this->getBit(y,x) ? foreground : background;
		}
	}
	
	return img;
}

Glyph* Glyph::clipBitArray(
			int desiredRows,
			int desiredColumns,
			int providedRows,
			int providedColumns,
			unsigned char* providedData
		)
{
	if (desiredRows > providedRows || desiredColumns > providedColumns) {
		return NULL;
	}
	Glyph source(providedRows, providedColumns, providedData);
	Glyph* dest = new Glyph(desiredRows, desiredColumns);
	for (int y = 0; y < desiredRows; y++) {
		for (int x = 0; x < desiredColumns; x++) {
			if (source.getBit(y,x)) {
				dest->setBit(y,x);
			}
		}
	}
	
	return dest;
}
