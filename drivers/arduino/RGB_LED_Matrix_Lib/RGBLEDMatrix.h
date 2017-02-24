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

class RGBLEDMatrix : public TimerAction {
private:
  int _latchPin;
  int _clockPin;
  int _dataPin;
  int _rows;
  int _columns;
  RGBImage _screen_data;
  RGBImage _screen_buf;

  int _scanPass;
  int _scanRow;
  int _priorRow;
  boolean _drawingActive;
  
  volatile uint8_t *_sclkPort;
  volatile uint8_t *_mosiPort;
  uint8_t _sclkMask;
  uint8_t _mosiMask;
  
  static int maxScanCountForValue(unsigned char value);
  
  void shiftOutAllOff();
  void shiftOutCurrentRow();
  // fast writing of a bit to the shift register by directly manipulating pin state
  void shiftOutBit( uint8_t bitValue );
  
  // safe writing of a bit to the shift register by using standard arduino calls
  void writeOutBit( uint8_t bitValue );
protected:
  virtual void action();
public:
  

	RGBLEDMatrix( int rows,
		  int columns,
		  int latchPin = 5,
		  int clockPin = 6,
		  int dataPin  = 7
		);

	RGBImage& image(void)				{ return _screen_buf; }
	const RGBImage& image(void) const	{ return _screen_buf; }
	  
  
	void startDrawing(void)   			{ _drawingActive = true; }
	void stopDrawing(void)    			{ _drawingActive = false; }

	int rows() const          			{ return _rows; }
	int columns() const       			{ return _columns; }
  
};

#endif //__SCREEN_H__
