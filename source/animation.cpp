#include "animation.h"
#include "config.h"

Adafruit_NeoPixel Animation::strip = Adafruit_NeoPixel(NEOPIXEL_NUM, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void Animation::init()
{
  strip.begin();
  strip.setBrightness(20);
  strip.show();
}

void Animation::setColor(uint32_t color)
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
    strip.setPixelColor(i, color);
    
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Animation::colorFromHue(uint8_t hue) {
  hue = 255 - hue;
  if(hue < 85) {
    return strip.Color(255 - hue * 3, 0, hue * 3);
  }
  if(hue < 170) {
    hue -= 85;
    return strip.Color(0, hue * 3, 255 - hue * 3);
  }
  hue -= 170;
  return strip.Color(hue * 3, 255 - hue * 3, 0);
}

void Animation::animateRainbow()
{
  static uint8_t ctr = 0;
  static uint32_t lastTimeMillis = millis();
  if (millis() - lastTimeMillis > 10)
  {
    lastTimeMillis = millis();
    ctr += 1;
    setColor(colorFromHue(ctr));
  }
}

void Animation::animateRainbowCircle()
{
  static uint8_t ctr = 0;
  static uint32_t lastTimeMillis = millis();
  if (millis() - lastTimeMillis > 10)
  {
    lastTimeMillis = millis();
    ctr += 2;
    for (uint8_t i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, colorFromHue(((i * 256 / strip.numPixels()) + ctr) & 255));
    }
    strip.show();
  }
}

