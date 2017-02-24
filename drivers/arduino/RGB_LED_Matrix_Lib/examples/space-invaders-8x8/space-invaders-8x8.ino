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
#include <RGBLEDMatrix.h>
#include <TimerAction.h>
#include <RGBAnimation.h>
#include <RGBAnimationSequence.h>

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

RGBLEDMatrix leds(8,8);
RGBAnimationSequence *animation;
const int ANIMATION_ITEMS_SIZE = 4;

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


  RGBAnimationSequence::AnimationItem* aniItems = new RGBAnimationSequence::AnimationItem[ANIMATION_ITEMS_SIZE];
  GlyphSequenceAnimation::Frame* frames;

  // first
  frames = new GlyphSequenceAnimation::Frame[2];
  frames[0].glyph = a1a;
  frames[0].interval = 500;
  frames[0].foreground = B00001000;
  frames[0].background = BLACK_COLOR;

  frames[1].glyph = a1b;
  frames[1].interval = 500;
  frames[1].foreground = B00001000;
  frames[1].background = BLACK_COLOR;
  
  aniItems[0].animation = new GlyphSequenceAnimation( leds, frames, 2 );
  aniItems[0].appearMillis = 4000;
  aniItems[0].transitionMillis = 2000;
  aniItems[0].transition = RGBAnimationSequence::TRANSITION_SLIDE_LEFT;
  aniItems[0].transitionPad = 3;

  // second
  frames = new GlyphSequenceAnimation::Frame[2];
  frames[0].glyph = a2a;
  frames[0].interval = 500;
  frames[0].foreground = B00100000;
  frames[0].background = BLACK_COLOR;

  frames[1].glyph = a2b;
  frames[1].interval = 500;
  frames[1].foreground = B00100000;
  frames[1].background = BLACK_COLOR;
  
  aniItems[1].animation = new GlyphSequenceAnimation( leds, frames, 2 );
  aniItems[1].appearMillis = 4000;
  aniItems[1].transitionMillis = 2000;
  aniItems[1].transition = RGBAnimationSequence::TRANSITION_SLIDE_RIGHT;
  aniItems[1].transitionPad = 3;

   // third
  frames = new GlyphSequenceAnimation::Frame[2];
  frames[0].glyph = a3a;
  frames[0].interval = 500;
  frames[0].foreground = B00100100;
  frames[0].background = BLACK_COLOR;

  frames[1].glyph = a3b;
  frames[1].interval = 500;
  frames[1].foreground = B00100100;
  frames[1].background = BLACK_COLOR;

  aniItems[2].animation = new GlyphSequenceAnimation( leds, frames, 2 );
  aniItems[2].appearMillis = 4000;
  aniItems[2].transitionMillis = 2000;
  aniItems[2].transition = RGBAnimationSequence::TRANSITION_SLIDE_LEFT;
  aniItems[2].transitionPad = 3;

  // fourth
  frames = new GlyphSequenceAnimation::Frame[4];
  frames[0].glyph = a4a;
  frames[0].interval = 250;
  frames[0].foreground = B00000010;
  frames[0].background = BLACK_COLOR;

  frames[1].glyph = a4b;
  frames[1].interval = 250;
  frames[1].foreground = B00000010;
  frames[1].background = BLACK_COLOR;

  frames[2].glyph = a4c;
  frames[2].interval = 250;
  frames[2].foreground = B00000010;
  frames[2].background = BLACK_COLOR;

  frames[3].glyph = a4d;
  frames[3].interval = 250;
  frames[3].foreground = B00000010;
  frames[3].background = BLACK_COLOR;

  aniItems[3].animation = new GlyphSequenceAnimation( leds, frames, 4 );
  aniItems[3].appearMillis = 6000;
  aniItems[3].transitionMillis = 2000;
  aniItems[3].transition = RGBAnimationSequence::TRANSITION_SLIDE_RIGHT;
  aniItems[3].transitionPad = 3;

  animation = new RGBAnimationSequence(
      aniItems,
      ANIMATION_ITEMS_SIZE
    );

//  Serial.begin(115200);
}


void loop() {  
  // put your main code here, to run repeatedly:
  leds.loop();
  animation->loop();
}

