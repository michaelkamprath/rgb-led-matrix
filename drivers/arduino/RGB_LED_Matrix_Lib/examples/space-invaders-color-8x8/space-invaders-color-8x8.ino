#include <Glyph.h>
#include <RGBImage.h>
#include <RGBLEDMatrix.h>
#include <TimerAction.h>
#include <RGBAnimation.h>
#include <RGBAnimationSequence.h>

RGBLEDMatrix leds(8,8);

PROGMEM ColorType const invader1A[64] = {
    TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR, 
    TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
    TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,
    DARK_GREEN_COLOR,DARK_GREEN_COLOR,WHITE_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,WHITE_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,
    DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,
    TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
    TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,
    DARK_GREEN_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR
};

PROGMEM ColorType const invader1B[64] = {
    TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
    TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
    TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,
    DARK_GREEN_COLOR,DARK_GREEN_COLOR,WHITE_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,WHITE_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,
    DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,
    TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
    TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,
    TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,DARK_GREEN_COLOR,TRANSPARENT_COLOR
};


PROGMEM ColorType const invader2A[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,
  RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,
  RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,
  TRANSPARENT_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,RED_COLOR
};

PROGMEM ColorType const invader2B[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,
  RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,
  RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,LIME_COLOR,RED_COLOR,RED_COLOR,
  TRANSPARENT_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,RED_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,RED_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader3A[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,
  ORANGE_COLOR,ORANGE_COLOR,WHITE_COLOR,ORANGE_COLOR,ORANGE_COLOR,WHITE_COLOR,ORANGE_COLOR,ORANGE_COLOR,
  ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,
  ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,
  ORANGE_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader3B[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  ORANGE_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,
  ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,
  ORANGE_COLOR,ORANGE_COLOR,WHITE_COLOR,ORANGE_COLOR,ORANGE_COLOR,WHITE_COLOR,ORANGE_COLOR,ORANGE_COLOR,
  ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,
  TRANSPARENT_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,ORANGE_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader4A[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
};
 
PROGMEM ColorType const invader4B[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
};
 
PROGMEM ColorType const invader4C[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
};
 
PROGMEM ColorType const invader4D[64] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
};


RGBImage a1a(8, 8, invader1A, true);
RGBImage a1b(8, 8, invader1B, true);
RGBImage a2a(8, 8, invader2A, true);
RGBImage a2b(8, 8, invader2B, true);
RGBImage a3a(8, 8, invader3A, true);
RGBImage a3b(8, 8, invader3B, true);
RGBImage a4a(8, 8, invader4A, true);
RGBImage a4b(8, 8, invader4B, true);
RGBImage a4c(8, 8, invader4C, true);
RGBImage a4d(8, 8, invader4D, true);

// first
ImageSequenceAnimation::Frame ani1[2] = {
  {
    &a1a,
    0, 0,
    500
  },
  {
    &a1b,
    0, 0,
    500
  },
};

// second
ImageSequenceAnimation::Frame ani2[2] = {
  {
    &a2a,
    0, 0,
    500
  },
  {
    &a2b,
    0, 0,
    500
  },
};
 
// third
ImageSequenceAnimation::Frame ani3[2] = {
  {
    &a3a,
    0, 0,
    500
  },
  {
    &a3b,
    0, 0,
    500
  }
};

// fourth
ImageSequenceAnimation::Frame ani4[4] = {
  {
    &a4a,
    0, 0,
    250
  },
  {
    &a4b,
    0, 0,
    250
  },
  {
    &a4c,
    0, 0,
    250
  },
  {
    &a4d,
    0, 0,
    250
  }
};

// animation
const int ANIMATION_ITEMS_SIZE = 9;
RGBAnimationSequence::AnimationItem aniItems[ANIMATION_ITEMS_SIZE] {
  {
    new ImageSequenceAnimation( leds, ani1, 2 ),
    4000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_LEFT,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani1, 2 ),
    4000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_DOWN,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani2, 2 ),
    4000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_RIGHT,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani2, 2 ),
    4000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_DOWN,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani3, 2 ),
    4000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_LEFT,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani3, 2 ),
    4000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_DOWN,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani4, 4 ),
    6000,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_UP,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani3, 2 ),
    0,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_UP,
    2
  },
  {
    new ImageSequenceAnimation( leds, ani2, 2 ),
    0,
    2000,
    RGBAnimationSequence::TRANSITION_SLIDE_UP,
    2
  },
  
};

RGBAnimationSequence animation( aniItems, ANIMATION_ITEMS_SIZE);

void setup() {
    leds.startScanning();
}

void loop() {  
  leds.loop();
  animation.loop();
}

