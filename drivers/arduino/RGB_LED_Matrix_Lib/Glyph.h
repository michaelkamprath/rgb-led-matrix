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

#ifndef __GLYPH_H__
#define __GLYPH_H__

#include "RGBImage.h"

/***
 * Glyph
 *
 * A Glyph is N x M array of bits that indicates pixels in an image devoid of color.
 * Glyphs are generally used to represent the image of letters in a font, but can be
 * used for any pixel image.
 *
 */

class Glyph {
private:
	
	int _rows;
	int _columns;
	bool* _bits;
	bool _manageMemory;
		
public:

	Glyph( int rows, int columns, unsigned char* data = NULL );
	Glyph( int rows, int columns, bool* data );
	Glyph( const Glyph& other );
	virtual ~Glyph();
	
	int rows(void) const		{ return _rows; }
	int columns(void) const		{ return _columns; }

	void setBit( int row, int column );
	void clearBit( int row, int column );
	bool getBit( int row, int column ) const;
	
	RGBImage* getImageWithColor(
			ColorType foreground,
			ColorType background = TRANSPARENT_COLOR
		) const;
};
 




#endif
