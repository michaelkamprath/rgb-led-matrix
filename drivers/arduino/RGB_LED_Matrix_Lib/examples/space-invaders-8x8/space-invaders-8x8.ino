/***
 * Space Invaders Animation Sequence
 * 
 * Cyclces through the classic images of attacking aliens.
 * 
 * This animations was heavily inspired by: 
 *     https://learn.adafruit.com/trinket-slash-gemma-space-invader-pendant/animation
 * 
 */


#include <Glyph.h>
#include <RGBImage.h>
#include <Screen.h>
#include <TimerAction.h>

unsigned char heartBits[8] = {
    B01000100,
    B11101110,
    B11111110,
    B11000110,
    B01101100,
    B00111000,
    B00010000,
    B00000000
  };

unsigned char invader1A[8] = {
    B00011000, 
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B10100101
  };

unsigned char invader1B[8] = {
    B00011000,
    B00111100,
    B01111110,
    B11011011,
    B11111111,
    B00100100,
    B01011010,
    B01000010
  };


unsigned char invader2A[8] = {
  B00000000,
  B00111100,
  B01111110,
  B11011011,
  B11011011,
  B01111110,
  B00100100,
  B11000011
  };

unsigned char invader2B[8] = {
  B00111100,
  B01111110,
  B11011011,
  B11011011,
  B01111110,
  B00100100,
  B00100100,
  B00100100,
  };

unsigned char invader3A[8] = {
  B00100100,
  B00100100,
  B01111110,
  B11011011,
  B11111111,
  B11111111,
  B10100101,
  B00100100,
};

unsigned char invader3B[8] = {
  B00100100,
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010,
};

unsigned char invader4A[8] = {
  B00111100,
  B01111110,
  B00110011,
  B01111110,
  B00111100,
  B00000000,
  B00001000,
  B00000000,
};
 
unsigned char invader4B[8] = {
  B00111100,
  B01111110,
  B10011001,
  B01111110,
  B00111100,
  B00000000,
  B00001000,
  B00001000,
};
 
unsigned char invader4C[8] = {
  B00111100,
  B01111110,
  B11001100,
  B01111110,
  B00111100,
  B00000000,
  B00000000,
  B00001000
};
 
unsigned char invader4D[8] = {
  B00111100,
  B01111110,
  B01100110,
  B01111110,
  B00111100,
  B00000000,
  B00000000,
  B00000000,
};

const int SEQUENCE_COUNT = 42;
Screen leds(8,8);
RGBImage* imageSequence[SEQUENCE_COUNT];
unsigned long counter = 0;
int sequenceIdx = 0;

void setup() {
  Glyph a1a(8,8,invader1A);
  Glyph a1b(8,8,invader1B);
  Glyph a2a(8,8,invader2A);
  Glyph a2b(8,8,invader2B);
  Glyph a3a(8,8,invader3A);
  Glyph a3b(8,8,invader3B);
  Glyph a4a(8,8,invader4A);
  Glyph a4b(8,8,invader4B);
  Glyph a4c(8,8,invader4C);
  Glyph a4d(8,8,invader4D);
 
  RGBImage* img1a = a1a.getImageWithColor( B00001000, TRANSPARENT_COLOR );
  RGBImage* img1b = a1b.getImageWithColor( B00001000, TRANSPARENT_COLOR );
  RGBImage* img2a = a2a.getImageWithColor( B00100000, TRANSPARENT_COLOR );
  RGBImage* img2b = a2b.getImageWithColor( B00100000, TRANSPARENT_COLOR );
  RGBImage* img3a = a3a.getImageWithColor( B00100100, TRANSPARENT_COLOR );
  RGBImage* img3b = a3b.getImageWithColor( B00100100, TRANSPARENT_COLOR );
  RGBImage* img4a = a4a.getImageWithColor( B00000010, TRANSPARENT_COLOR );
  RGBImage* img4b = a4b.getImageWithColor( B00000010, TRANSPARENT_COLOR );
  RGBImage* img4c = a4c.getImageWithColor( B00000010, TRANSPARENT_COLOR );
  RGBImage* img4d = a4d.getImageWithColor( B00000010, TRANSPARENT_COLOR );

  imageSequence[0] = img1a;
  imageSequence[1] = img1a;
  imageSequence[2] = img1b;
  imageSequence[3] = img1b;
  imageSequence[4] = img1a;
  imageSequence[5] = img1a;
  imageSequence[6] = img1b;
  imageSequence[7] = img1b;
  imageSequence[8] = img1a;
  imageSequence[9] = img1a;
  imageSequence[10] = img2a;
  imageSequence[11] = img2a;
  imageSequence[12] = img2b;
  imageSequence[13] = img2b;
  imageSequence[14] = img2a;
  imageSequence[15] = img2a;
  imageSequence[16] = img2b;
  imageSequence[17] = img2b;
  imageSequence[18] = img2a;
  imageSequence[19] = img2a;
  imageSequence[20] = img3a;
  imageSequence[21] = img3a;
  imageSequence[22] = img3b;
  imageSequence[23] = img3b;
  imageSequence[24] = img3a;
  imageSequence[25] = img3a;
  imageSequence[26] = img3b;
  imageSequence[27] = img3b;
  imageSequence[28] = img3a;
  imageSequence[29] = img3a;
  imageSequence[30] = img4a;
  imageSequence[31] = img4b;
  imageSequence[32] = img4c;
  imageSequence[33] = img4d;
  imageSequence[34] = img4a;
  imageSequence[35] = img4b;
  imageSequence[36] = img4c;
  imageSequence[37] = img4d;
  imageSequence[38] = img4a;
  imageSequence[39] = img4b;
  imageSequence[40] = img4c;
  imageSequence[41] = img4d;
 
  leds.paintColor(BLACK_COLOR);
  leds.placeImageAt( *img1a, 0, 0 );
}

void loop() {
  // put your main code here, to run repeatedly:
  leds.loop();
  counter++;
  if (counter%750 == 0) {
    sequenceIdx++;
    if (sequenceIdx >= SEQUENCE_COUNT) {
      sequenceIdx = 0;
    }

    leds.paintColor(BLACK_COLOR);
    leds.placeImageAt(*imageSequence[sequenceIdx], 0, 0);

    counter = 0;
  }
}
