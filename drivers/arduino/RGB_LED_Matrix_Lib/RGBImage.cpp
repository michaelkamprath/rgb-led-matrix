//     RGB Matrix Project - RGBImage
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
#include <string.h>
#include "RGBImage.h"

RGBImage::RGBImage(int rows, int columns)
:	_rows(rows),
	_columns(columns),
	_data(new ColorType[rows*columns])
{
	this->paintColor(BLACK_COLOR);
}

void RGBImage::copy(const RGBImage& other) {
	// only copy if same dimensions
	if (other._rows == _rows && other._columns == _columns) {
		memcpy(_data, other._data, _rows*_columns);
	}
}

ColorType& RGBImage::pixel( int row, int column ) { 
	return _data[row*_columns + column];
}
const ColorType& RGBImage::pixel( int row, int column ) const {
	return _data[row*_columns + column];
}


void RGBImage::placeImageAt( const RGBImage& image, int row, int column ) {
	if (	row >= _rows
			|| column >= _columns
			|| (image._columns + column <= 0 )
			|| (image._rows + row <= 0) 
		) {
		return;
	}

	int imageX = 0;
	int thisX = column;
	if (column < 0) {
		imageX = -column;
		thisX = 0;
	}
	
	int imageColumns = image._columns - imageX;
	int thisColumns = column <= 0 ? this->_columns : this->_columns - column;
	if (imageColumns > thisColumns) {
		imageColumns = thisColumns;
	}

	int imageY = 0;
	int startRow = row;
	if (row < 0) {
		imageY = -row;
		startRow = 0;
	}

	for ( int yT = startRow, yO = imageY; (yT < this->_rows) && (yO < image._rows); yT++, yO++ ) {     
		memcpy(&this->pixel(yT,thisX), &image.pixel(yO,imageX), imageColumns);
	}
}

void RGBImage::paintColor( ColorType color ) {
	memset(_data,color,_rows*_columns);
}
