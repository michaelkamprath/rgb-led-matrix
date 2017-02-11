#ifndef __SCREEN_H__
#define __SCREEN_H__
#include "TimerAction.h"
#include "RGBImage.h"

class Screen : public TimerAction {
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
  boolean _drawingActive;
  
  void shiftOutBit( uint8_t bitValue );

protected:
  virtual void action();
public:
  

  Screen( int rows,
          int columns,
          int latchPin = 5,
          int clockPin = 6,
          int dataPin  = 7
        );

  byte& pixel( int row, int column ) {
    return _screen_buf.pixel(row,column);
  }
  void placeImageAt( const RGBImage& image, int row, int column ) {
    _screen_buf.placeImageAt(image, row, column);
  }
  void paintColor( byte color ) {
    _screen_buf.paintColor(color);
  }
  
  void startDrawing(void)   { _drawingActive = true; }
  void stopDrawing(void)    { _drawingActive = false; }
  
  int rows()                { return _rows; }
  int columns()             { return _columns; }
  
};

#endif //__SCREEN_H__
