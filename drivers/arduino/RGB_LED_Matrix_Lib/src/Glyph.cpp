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
#if defined ( ESP8266 )
  #include <pgmspace.h>
#else
  #include <avr/pgmspace.h>
#endif
#include "Glyph.h"
#include "RGBLEDMatrixUtils.h"

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

/***************************************
 *
 * GlyphBase
 *
 */
#pragma mark GlyphBase

GlyphBase::GlyphBase( 
	int rows,
	int columns
)
	:	_rows( rows ),
		_columns( columns )
{
}
GlyphBase::GlyphBase( const GlyphBase& other )
	:	_rows( other.rows() ),
		_columns( other.columns() )
{
}
GlyphBase::~GlyphBase()
{
}

bool GlyphBase::getBit( int row, int column ) const {
	int bitIdx = row*this->columns() + column;	
	if (this->isProgMem()) {
		return pgm_read_byte_near( this->bits() + bitIdx );
	} else {
		return this->bits()[bitIdx];
	}
}

MutableRGBImage* GlyphBase::getImageWithColor( ColorType foreground, ColorType background ) const {
	MutableRGBImage* img = new MutableRGBImage( this->rows(), this->columns() );
	
	if (this->isProgMem()) {
		// creating a PROGMEM version of the loops for speed: don't have to check if PROGRMEM
		// with every loop in getBits()
		for (int y = 0; y < this->rows(); y++) {
			for (int x = 0; x < this->columns(); x++) {
				int bitIdx = y*this->columns() + x;
				img->pixel(y, x) = (bool)pgm_read_byte_near( this->bits() + bitIdx ) ? foreground : background;
			}
		}	
	} else {
		for (int y = 0; y < this->rows(); y++) {
			for (int x = 0; x < this->columns(); x++) {
				img->pixel(y, x) = this->getBit(y,x) ? foreground : background;
			}
		}
	}
	return img;
}

bool* GlyphBase::generateBitBoolArray( 
	int rows,
	int columns,
	const unsigned char* data,
	bool isFromProgramSpace
) {
	bool* boolArray = new bool[rows*columns];
	
	if ( data != NULL ) {
		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < columns; x++ ) {
				int bitIdx = y*columns + x;
				unsigned char dataByte = 0;
				if (isFromProgramSpace) {
					dataByte = pgm_read_byte_near(data + bitIdx/8);
				} else {
					dataByte = data[bitIdx/8];
				}
				
				boolArray[bitIdx] = ( ( dataByte & BIT_MASKS[bitIdx%8] ) != 0 );
			}
		}
	} else {
		// zero out array
		memset(boolArray, 0, rows*columns);
	}
	
	return boolArray;
}

void GlyphBase::streamFrameToSerial(void) {
	for (int row = 0; row < this->rows(); row++) {
		Serial.print(F("     "));
		for (int i = 0; i < this->columns(); i++) {
			if (this->getBit(row, i)) {
			   Serial.print('1');
			}
			else {
			   Serial.print('0');
			}
		}
		Serial.print(F("\n"));
	}
}


/***************************************
 *
 * MutableGlyph
 *
 */
#pragma mark MutableGlyph

MutableGlyph::MutableGlyph(
	int rows,
	int columns,
	const unsigned char* data,
	bool isFromProgramSpace
)
	:	GlyphBase( rows, columns ),
		_bits(GlyphBase::generateBitBoolArray(rows, columns, data, isFromProgramSpace)),
		_dirty(false)
{
}

MutableGlyph::MutableGlyph( const GlyphBase& other )
	: 	GlyphBase(other),
		_bits( (bool*)memcpy_smart( 
					new bool[(other.rows()*other.columns())],
					other.bits(),
					(other.rows()*other.columns())*sizeof(bool),
					other.isProgMem() )
				)
{
}

MutableGlyph::~MutableGlyph() {
	delete _bits;
}

void MutableGlyph::eraseAll() {
	memset(_bits, 0, this->rows()*this->columns());
}

void MutableGlyph::setBit( int row, int column ) {
	int bitIdx = row*this->columns() + column;
	
	_bits[bitIdx] = true;
	_dirty = true;
}
void MutableGlyph::clearBit( int row, int column ) {
	int bitIdx = row*this->columns() + column;

	_bits[bitIdx] = false;
	_dirty = true;
}

/***************************************
 *
 * Glyph
 *
 */
#pragma mark Glyph

// if byte buffer is passed, glyph will keep that for the data store
// in order to reduce overall memory usage.

Glyph::Glyph(
	int rows,
	int columns,
	const unsigned char* data,
	bool isFromProgramSpace
)
	: 	GlyphBase( rows, columns ),
		_bits(GlyphBase::generateBitBoolArray(rows, columns, data, isFromProgramSpace)),
		_isProgMem(false),
		_manageMem(true)
{
}

Glyph::Glyph( 
	int rows,
	int columns,
	const bool* data,
	bool isFromProgramSpace
)	
	: 	GlyphBase( rows, columns ),
		_bits( data ),
		_isProgMem(isFromProgramSpace),
		_manageMem(false)
{
}


Glyph::Glyph( const GlyphBase& other )
	:	GlyphBase(other.rows(), other.columns()),
		_bits(  other.isProgMem() ? 
					other.bits() :
					(bool*)memcpy(
						new bool[(other.rows()*other.columns())],
						other.bits(),
						(other.rows()*other.columns())*sizeof(bool) )
			),		
		_isProgMem(other.isProgMem()),
		_manageMem(true)
{
}

Glyph::~Glyph() {
	if (_manageMem) {
		delete _bits;
	}
}
