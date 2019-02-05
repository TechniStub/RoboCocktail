#ifndef _MACHINE_H
#define _MACHINE_H

#include <Adafruit_TiCoServo.h>
#include <AccelStepper.h>

class Machine
{
public:
  static bool isHome();
  static bool isGlassPresent();

  static void home();
  static void init();
  static void move(int32_t position_mm);
  
  static void startDispensing();
  static void stopDispensing();

  static uint8_t getButtonMask();
  static bool isGoPressed();
  static uint8_t getButtonIndex();

  static void setLEDMask(uint8_t mask);
  static void setLED(uint8_t index, bool state);
  
  // Servomoteur pour l'appui sur le levier des optiques de bar
  static Adafruit_TiCoServo servo;
  // Moteur pas à pas de déplacement du chariot
  static AccelStepper stepper;
};

#endif
