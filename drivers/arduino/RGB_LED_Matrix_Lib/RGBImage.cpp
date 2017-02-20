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
#include <Arduino.h>
#include <string.h>
#include "RGBImage.h"

RGBImage::RGBImage(int rows, int columns)
:	_rows(rows),
	_columns(columns),
	_data(new ColorType[rows*columns])
{
	this->paintColor(BLACK_COLOR);
}

RGBImage::RGBImage(const RGBImage& other)
:	_rows(other._rows),
	_columns(other._columns),
	_data(new ColorType[other._rows*other._columns])
{
	this->copy(other);
}

RGBImage::~RGBImage() {
	delete _data;
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
		for (int colCounter = 0; colCounter < imageColumns; colCounter++) {
			ColorType color = image.pixel(yO,imageX+colCounter);
			if (color != TRANSPARENT_COLOR) {
				this->pixel(yT,thisX+colCounter) = color;
			}
		}
	}
}

void RGBImage::paintColor( ColorType color ) {
	memset(_data,color,_rows*_columns);
}

void RGBImage::drawLine( 
		int startRow,
		int startColumn,
		int stopRow,
		int stopColumn,
		ColorType color
	)
{
	if ( stopColumn != startColumn ) {
		float delta_col = stopColumn - startColumn;
		float delta_row = stopRow - startRow;
		
		if (abs(delta_col) > abs(delta_row)) {
			for (int col = startColumn; 
				delta_col < 0 ? col >= stopColumn : col <= stopColumn; 
				delta_col < 0 ? col-- : col++ ) 
			{
				int row = round(startRow + delta_row*(col - startColumn)/delta_col);
				this->pixel(row,col) = color;
			}
		}
		else {
			for (int row = startRow; 
				delta_row < 0 ? row >= stopRow : row <= stopRow; 
				delta_row < 0 ? row-- : row++ ) 
			{
				int col = round(startColumn + delta_col*(row - startRow)/delta_row);
				this->pixel(row,col) = color;
			}
		
		}
	}
	else {
		float delta_row = stopRow - startRow;

		for ( int row = startRow; 
			  delta_row < 0 ? row >= stopRow : row <= stopRow; 
			  delta_row < 0 ? row-- : row++ ) 
		{
			this->pixel(row,startColumn) = color;
		}	
	}
}	

void RGBImage::drawRectangle( 
  		int tlRow,
  		int tlColumn,
  		int brRow,
  		int brColumn,
  		ColorType color,
  		bool fill
  	)
{
	if ( tlRow > brRow || tlColumn > brColumn ) {
		return;
	}
	
	for (int row = tlRow; row <= brRow; row++ ) {
		if ( fill || row == tlRow || row == brRow ) {
			memset(&this->pixel(row,tlColumn),color,brColumn-tlColumn+1);
		}
		else {
			this->pixel(row,tlColumn) = color;
			this->pixel(row,brColumn) = color;
		}
	}
}
