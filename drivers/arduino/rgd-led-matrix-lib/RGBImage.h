#ifndef __RGBIMAGE_H__
#define __RGBIMAGE_H__

typedef unsigned char ColorType;

const ColorType WHITE_COLOR = 0x3F;
const ColorType GRAY_COLOR = 0x2A;
const ColorType DARK_GRAY_COLOR = 0x15;
const ColorType BLACK_COLOR = 0;
const ColorType RED_COLOR = 0x30;
const ColorType GREEN_COLOR = 0x0C;
const ColorType BLUE_COLOR = 0x03;
const ColorType YELLOW_COLOR = 0x3C;
const ColorType AQUA_COLOR = 0x0F;
const ColorType MAGENTA_COLOR = 0x33;
const ColorType PINK_COLOR = 0x26;
const ColorType ORANGE_COLOR = 0x38;
const ColorType CORAL_COLOR = 0x39;
const ColorType TURQUOISE_COLOR = 0x1E;
const ColorType VIOLET_COLOR = 0x27;
const ColorType LIME_COLOR = 0x2D;
const ColorType SLATE_BLUE_COLOR = 0x16;

const static unsigned char RED_MASK = 0x30;
const static unsigned char RED_BIT_SHIFT = 4;

const static unsigned char GREEN_MASK = 0x0C;
const static unsigned char GREEN_BIT_SHIFT = 2;

const static unsigned char BLUE_MASK = 0x03;
const static unsigned char BLUE_BIT_SHIFT = 0;

class RGBImage {
private:
  int _rows;
  int _columns;
  ColorType* _data;

public:
  RGBImage(int rows, int columns);

  void copy(const RGBImage& other);
  
  ColorType& pixel( int row, int column );
  const ColorType& pixel( int row, int column ) const;
  void placeImageAt( const RGBImage& image, int row, int column );
  void paintColor( ColorType color ); 
};

#endif //__RGBIMAGE_H__
