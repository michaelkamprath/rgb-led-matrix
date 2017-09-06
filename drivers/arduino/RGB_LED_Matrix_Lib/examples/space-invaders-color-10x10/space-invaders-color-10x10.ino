#include <Glyph.h>
#include <RGBImage.h>
#include <RGBLEDMatrix.h>
#include <TimerAction.h>
#include <RGBAnimation.h>
#include <RGBAnimationSequence.h>

RGBLEDMatrix leds(10,10);

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

PROGMEM ColorType const invader4A[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};
 
PROGMEM ColorType const invader4B[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};
 
PROGMEM ColorType const invader4C[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};
 
PROGMEM ColorType const invader4D[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader4E[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,CORAL_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader4F[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader4G[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};

PROGMEM ColorType const invader4H[72] = {
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,YELLOW_COLOR,BLUE_COLOR,BLUE_COLOR,YELLOW_COLOR,
  TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,BLUE_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,
  TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR,TRANSPARENT_COLOR
};


RGBImage a1a(8, 8, invader1A, true);
RGBImage a1b(8, 8, invader1B, true);
RGBImage a2a(8, 8, invader2A, true);
RGBImage a2b(8, 8, invader2B, true);
RGBImage a3a(8, 8, invader3A, true);
RGBImage a3b(8, 8, invader3B, true);
RGBImage a4a(9, 8, invader4A, true);
RGBImage a4b(9, 8, invader4B, true);
RGBImage a4c(9, 8, invader4C, true);
RGBImage a4d(9, 8, invader4D, true);
RGBImage a4e(9, 8, invader4E, true);
RGBImage a4f(9, 8, invader4F, true);
RGBImage a4g(9, 8, invader4G, true);
RGBImage a4h(9, 8, invader4H, true);

// first
ImageSequenceAnimation::Frame ani1[2] = {
  {
    &a1a,
    1, 1,
    500
  },
  {
    &a1b,
    1, 1,
    500
  },
};

// second
ImageSequenceAnimation::Frame ani2[2] = {
  {
    &a2a,
    1, 1,
    500
  },
  {
    &a2b,
    1, 1,
    500
  },
};
 
// third
ImageSequenceAnimation::Frame ani3[2] = {
  {
    &a3a,
    1, 1,
    500
  },
  {
    &a3b,
    1, 1,
    500
  }
};

// fourth
ImageSequenceAnimation::Frame ani4[8] = {
  {
    &a4a,
    1, 1,
    250
  },
  {
    &a4b,
    1, 1,
    250
  },
  {
    &a4c,
    1, 1,
    250
  },
  {
    &a4d,
    1, 1,
    250
  },
  {
    &a4e,
    1, 1,
    250
  },
  {
    &a4f,
    1, 1,
    250
  },
  {
    &a4g,
    1, 1,
    250
  },
  {
    &a4h,
    1, 1,
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
    new ImageSequenceAnimation( leds, ani4, 8 ),
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

