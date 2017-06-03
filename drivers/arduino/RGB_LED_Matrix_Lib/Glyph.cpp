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
#include <avr/pgmspace.h>
#include "Glyph.h"


// pre-calculate the bit masks to speed up over 1<<(7-bitIdx%8)
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
Glyph::Glyph(
	int rows,
	int columns,
	const unsigned char* data,
	bool isFromProgramSpace
)
	: 	_rows( rows ),
		_columns( columns ),
		_bits( new bool[rows*columns] ),
		_manageMemory(true)
{
	// storing as a bool array for speed reasons
	if ( data != NULL ) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < columns; x++ ) {
				int bitIdx = y*columns + x;
				unsigned char dataByte = 0;
				if (isFromProgramSpace) {
					dataByte = pgm_read_word_near(data + bitIdx/8);
				} else {
					dataByte = data[bitIdx/8];
				}
				
				_bits[bitIdx] = ( ( dataByte & BIT_MASKS[bitIdx%8] ) != 0 );
			}
		}
	}
}

Glyph::Glyph( int rows, int columns, bool* data )
	: 	_rows( rows ),
		_columns( columns ),
		_bits( data ),
		_manageMemory(false)
{
	// assume the passed boolean array is of the right form. 
}

Glyph::Glyph( const Glyph& other )
	: 	_rows( other._rows ),
		_columns( other._columns ),
		_bits( new bool[(other._rows*other._columns)] )
{
	memcpy(_bits, other._bits, (other._rows*other._columns)*sizeof(bool));
}

Glyph::~Glyph() {
	delete _bits;
}
void Glyph::setBit( int row, int column ) {
	int bitIdx = row*this->columns() + column;
	
	_bits[bitIdx] = true;
}
void Glyph::clearBit( int row, int column ) {
	int bitIdx = row*this->columns() + column;

	_bits[bitIdx] = false;
}

bool Glyph::getBit( int row, int column ) const {
	int bitIdx = row*this->columns() + column;
	
	return _bits[bitIdx];
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

