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

#ifndef __RGBLEDMATRIX_H__
#define __RGBLEDMATRIX_H__
#include "TimerAction.h"
#include "RGBImage.h"
#include "LEDMatrixBits.h"
#include "SPIConnection.h"

class RGBLEDMatrix : public TimerAction {
private:
	int _rows;
	int _columns;
	RGBImage _screen_data;
	RGBImage _screen_buf;
	LEDMatrixBits _screenBits;
	
	int _cycleCount;
	int _scanPass;
	int _scanRow;
	int _priorRow;
	boolean _drawingActive;

	SPIConnection	_spi;
	
	static int maxScanCountForValue(unsigned char value);

	void shiftOutAllOff();
	void shiftOutCurrentRow();
protected:
	virtual void action();
public:
  

	RGBLEDMatrix(
			int rows,
			int columns
		);

	RGBImage& image(void)				{ return _screen_buf; }
	const RGBImage& image(void) const	{ return _screen_buf; }
  

	void startDrawing(void)   			{ _drawingActive = true; }
	void stopDrawing(void)    			{ _drawingActive = false; }

	int rows() const          			{ return _rows; }
	int columns() const       			{ return _columns; }

};

#endif //__SCREEN_H__
