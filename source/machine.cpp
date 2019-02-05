#include "machine.h"
#include "config.h"
  
Adafruit_TiCoServo Machine::servo;
AccelStepper Machine::stepper(AccelStepper::DRIVER, STEPPER_STEP_PIN, STEPPER_DIR_PIN);

void Machine::init()
{
  // Initialisation du servomoteur
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(SERVO_IDLE_POSITION);

  // Broche d'activation du driver de pas à pas (logique inversée !)
  stepper.setEnablePin(STEPPER_ENABLE_PIN);
  stepper.setPinsInverted(false,false,true);
  stepper.disableOutputs();

  // Limites de déplacement
  stepper.setMaxSpeed(STEPPER_MAX_SPEED);
  stepper.setAcceleration(STEPPER_ACCELERATION);

  // Sorties
  pinMode(BTN_1_LED_PIN, OUTPUT);
  pinMode(BTN_2_LED_PIN, OUTPUT);
  pinMode(BTN_3_LED_PIN, OUTPUT);
  pinMode(BTN_4_LED_PIN, OUTPUT);

  // Entrées
  pinMode(BTN_GO_PIN, INPUT_PULLUP);
  pinMode(BTN_1_PIN, INPUT_PULLUP);
  pinMode(BTN_2_PIN, INPUT_PULLUP);
  pinMode(BTN_3_PIN, INPUT_PULLUP);
  pinMode(BTN_4_PIN, INPUT_PULLUP);

  // Homing
  pinMode(SW_HOME, INPUT);
  pinMode(SW_GLASS, INPUT);
}

bool Machine::isHome()
{
  return !digitalRead(SW_HOME);
}

void Machine::home()
{
  while (!isHome())
  {
    stepper.enableOutputs();
    stepper.move(-100);
    stepper.run();
  }

  stepper.setCurrentPosition(0);
  stepper.disableOutputs();
}

void Machine::move(int32_t position_mm)
{
  stepper.enableOutputs();
  stepper.runToNewPosition(STEPPER_STEPS_PER_MM * position_mm);
}


void Machine::startDispensing()
{
  servo.writeMicroseconds(SERVO_SERVING_POSITION);
}

void Machine::stopDispensing()
{
  servo.writeMicroseconds(SERVO_IDLE_POSITION);
}

uint8_t Machine::getButtonMask()
{
  return (!digitalRead(BTN_1_PIN) << 0) |
         (!digitalRead(BTN_2_PIN) << 1) |
         (!digitalRead(BTN_3_PIN) << 2) |
         (!digitalRead(BTN_4_PIN) << 3) |
         (!digitalRead(BTN_GO_PIN) << 4);
}

bool Machine::isGoPressed()
{
  return !digitalRead(BTN_GO_PIN);
}

uint8_t Machine::getButtonIndex()
{
  uint8_t value = getButtonMask() & 0xF;
  uint8_t i;
  for (i=0; i<4; i++)
  {
    if (value & (1 << i))
    {
      return i;
    }
  }
  return 0xFF;
}

void Machine::setLEDMask(uint8_t mask)
{
  for (uint8_t i=0; i<4; i++)
  {
    digitalWrite(BTN_1_LED_PIN - i, mask & (1 << i));
  }
}

void Machine::setLED(uint8_t index, bool state)
{
  if (index > 3) return;
  digitalWrite(BTN_1_LED_PIN - index, state);
}
  
