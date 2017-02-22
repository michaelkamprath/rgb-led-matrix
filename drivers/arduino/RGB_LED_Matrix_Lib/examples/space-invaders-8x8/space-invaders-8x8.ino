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

const int SEQUENCE_COUNT = 27;
Screen leds(8,8);
Glyph* imageSequence[SEQUENCE_COUNT];
ColorType imageColors[SEQUENCE_COUNT];
unsigned long imageTime[SEQUENCE_COUNT];
unsigned long counter = 0;
int sequenceIdx = 0;

void setup() {
  Glyph* a1a = new Glyph(8,8,invader1A);
  Glyph* a1b = new Glyph(8,8,invader1B);
  Glyph* a2a = new Glyph(8,8,invader2A);
  Glyph* a2b = new Glyph(8,8,invader2B);
  Glyph* a3a = new Glyph(8,8,invader3A);
  Glyph* a3b = new Glyph(8,8,invader3B);
  Glyph* a4a = new Glyph(8,8,invader4A);
  Glyph* a4b = new Glyph(8,8,invader4B);
  Glyph* a4c = new Glyph(8,8,invader4C);
  Glyph* a4d = new Glyph(8,8,invader4D);
 
  memset(&imageColors[0], B00001000, 5);
  memset(&imageColors[5], B00100000, 5);
  memset(&imageColors[10], B00100100, 5);
  memset(&imageColors[15], B00000010, 12);

  for (int i = 0; i < 15; i++ ) {
    imageTime[i] = 2000;
  }
  for (int i = 15; i < SEQUENCE_COUNT; i++ ) {
    imageTime[i] = 1000;
  }
  
  imageSequence[0] = a1a;
  imageSequence[1] = a1b;
  imageSequence[2] = a1a;
  imageSequence[3] = a1b;
  imageSequence[4] = a1a;
  imageSequence[5] = a2a;
  imageSequence[6] = a2b;
  imageSequence[7] = a2a;
  imageSequence[8] = a2b;
  imageSequence[9] = a2a;
  imageSequence[10] = a3a;
  imageSequence[11] = a3b;
  imageSequence[12] = a3a;
  imageSequence[13] = a3b;
  imageSequence[14] = a3a;
  imageSequence[15] = a4a;
  imageSequence[16] = a4b;
  imageSequence[17] = a4c;
  imageSequence[18] = a4d;
  imageSequence[19] = a4a;
  imageSequence[20] = a4b;
  imageSequence[21] = a4c;
  imageSequence[22] = a4d;
  imageSequence[23] = a4a;
  imageSequence[24] = a4b;
  imageSequence[25] = a4c;
  imageSequence[26] = a4d;
}


void loop() {  
  // put your main code here, to run repeatedly:
  leds.loop();
  counter++;
  if (counter%imageTime[sequenceIdx] == 0) {
    sequenceIdx++;
    if (sequenceIdx >= SEQUENCE_COUNT) {
      sequenceIdx = 0;
    }

    leds.startDrawing();
    leds.drawGlyph( *imageSequence[sequenceIdx], 0,0, imageColors[sequenceIdx], BLACK_COLOR );
    leds.stopDrawing();
    
    counter = 0;
  }
}

