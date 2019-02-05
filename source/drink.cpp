#include <stdint.h>
#include "animation.h"
#include "config.h"
#include "drink.h"
#include "machine.h"

Drink::Drink(uint16_t position, uint16_t dispenseTime, uint16_t refillTime, bool forceRefill)
{
  m_position = position;
  m_dispenseTime = dispenseTime;
  m_refillTime = refillTime;
  m_forceRefill = forceRefill;
  m_timerVal = 0;
  m_state = Drink::State::Idle;
}

void Drink::dispense()
{
  // Déplace le chariot jusqu'à la position de la boisson courante
  Machine::move(m_position);

  // Vérifie que l'optique a fini de se remplir avant de reservir 
  if (m_state == Drink::State::Refilling)
    while(millis() - m_timerVal < m_dispenseTime + m_refillTime);

  // Démarre le service
  Machine::startDispensing();
  delay(SERVO_DELAY);
  m_state = Drink::State::Dispensing;
  // Initalise le timer
  m_timerVal = millis();
  // Attend l'écoulement du délai de service d'une mesure de l'optique
  while(millis() - m_timerVal < m_dispenseTime)
    Animation::animateRainbowCircle();
  //Animation::setColor(0);
  // Déplace le chariot pour forcer une descente rapide du doseur
  // certains doseurs (surtout le 2cl) ne se remplissent pas correctement si 
  // on redescend trop lentement
  if (m_forceRefill) {
    Machine::stepper.move(-50 * STEPPER_STEPS_PER_MM);
  Machine::stepper.runToPosition();
  }
  
  // Remet le servo en position initiale
  Machine::stopDispensing();
  delay(SERVO_DELAY);
  // Etat courant : l'optique se remplit
  m_state = Drink::State::Refilling;
}
