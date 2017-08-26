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
	MutableRGBImage _screen_data;
	
	LEDMatrixBits **_curScreenBitFrames;
	LEDMatrixBits *_screenBitFrames[6];
	bool _screenBitFrameToggle;
	
	int _scanPass;
	int _scanRow;
	int _isDrawingCount;

	SPIConnection	_spi;
	
	void shiftOutRow( int row, int scanPass );
	void setRowBitsForFrame(
			int row,
			size_t frame,
			LEDMatrixBits* framePtr,
			const RGBImageBase& image
		);
	void copyScreenDataToBits(const RGBImageBase& image);
	size_t maxFrameCountForValue(unsigned char value);
protected:
	virtual void action();
public:
  

	RGBLEDMatrix(
			int rows,
			int columns
		);

	MutableRGBImage& image(void)				{ return _screen_data; }
	const MutableRGBImage& image(void) const	{ return _screen_data; }
  

	void startDrawing(void)   			{ _isDrawingCount++; }
	void stopDrawing(void)    			{ _isDrawingCount--; if (_isDrawingCount < 0) { _isDrawingCount = 0; }}
	bool isDrawing(void) const			{ return (_isDrawingCount > 0); }
	
	int rows() const          			{ return _rows; }
	int columns() const       			{ return _columns; }

	void startScanning(void);
	void stopScanning(void);

	void shiftOutCurrentRow(void);
	unsigned int nextTimerInterval(void) const;
	void incrementScanRow( void );
};

#endif //__SCREEN_H__
