#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <Adafruit_NeoPixel.h>

class Animation
{
  public:
  static void init();
  
  static void animateRainbow();
  static void animateRainbowCircle();
  static void animateColorCircle(uint32_t color);
  
  static void setColor(uint32_t color);
  static uint32_t colorFromHue(uint8_t hue);

  static Adafruit_NeoPixel strip;
};

#endif

