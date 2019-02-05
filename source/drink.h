#ifndef _DRINK_H
#define _DRINK_H

class Drink {
public:
  Drink(uint16_t position, uint16_t dispenseTime, uint16_t refillTime, bool forceRefill = true);
  // Sert la boisson
  void dispense();
private:
  // Paramètres du doseur: ne devraient pas changer en cours d'exécution
  uint16_t m_position;      // Position sur le rail, en mm (donner pt origine)
  uint16_t m_refillTime;    // Temps de remplissage, en ms
  uint16_t m_dispenseTime;  // Temps de service, en ms
  bool     m_forceRefill;   // Décalage du chariot pour forcer le remplissage de l'optique
  // Variables de fonctionnement du doseur
  uint32_t m_timerVal;      // Instant de début de service en ms (fonction millis())
  enum State {
    Idle,
    Dispensing,
    Refilling
  } m_state;
};

#endif
