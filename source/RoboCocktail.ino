#include <AccelStepper.h>
#include <Adafruit_TiCoServo.h>
#include "animation.h"
#include "config.h"
#include "machine.h"
#include "drink.h"

enum Drinks {
  LiqueurRose = 0,
  Vodka,
  TraitVodka,
  NeoCitron,
  SiropBubbleGum,
  Cremant,
  Tonic,
  JusPomme,
  NectarPeche,
  JusMangue,
  SevenUp,
  __END__ = 255
};

Drink drinks[] = {
  Drink(1000,2000,2000),// Liqueur de rose (2cl)
  Drink(900,3000,3000), // Vodka (3cl)
  Drink(900,600,1000, false), // Trait de vodka
  Drink(800,2000,2000), // Néo citron (2cl)
  Drink(700,6000,12000), // Sirop de bubble gum (2cl)
  Drink(600,5000,5000), // Crémant (5cl)
  Drink(500,5000,5000), // Tonic (5cl)
  Drink(400,5000,5000), // Jus de pomme (5cl)
  Drink(300,3000,4000), // Nectar de pêche (3cl)
  Drink(200,3000,4000), // Jus de mangue (3cl) 
  Drink(100,5000,5000), // Seven Up (5cl)
};

uint8_t recipe0[] = { LiqueurRose, Vodka, Tonic, Tonic, __END__ };
uint8_t recipe1[] = { TraitVodka, NeoCitron, NeoCitron, Cremant, Cremant, __END__ };
uint8_t recipe2[] = { NectarPeche, NectarPeche, NectarPeche, JusMangue, JusMangue, JusMangue, SevenUp, SevenUp, __END__ };
uint8_t recipe3[] = { SiropBubbleGum, JusPomme, JusPomme, SevenUp, SevenUp, __END__ };

uint8_t* recipes[4] = { recipe0, recipe1, recipe2, recipe3 };

enum RoboCocktailState {
  IDLE,
  DISPENSING,
  DEBUG
};

RoboCocktailState state = IDLE;
uint8_t selectedRecipe = BTN_NONE;

void setup() {
  Animation::init();
  Animation::setColor(Animation::strip.Color(255,255,0));
  Machine::init();
  if (Machine::isGoPressed())
    state = DEBUG;
  Machine::home();
}

void setStateIdle()
{
  selectedRecipe = BTN_NONE;
  Machine::setLEDMask(0);
  Machine::home();
  state = IDLE;
}

void setStateDispensing()
{
  state = DISPENSING;
  Animation::setColor(0);
}

uint8_t ctr;
uint32_t lastTimeMillis = millis();

void loop() {
  switch (state)
  {
    case IDLE:
    {
      // Attend l'appui sur un des boutons de sélection
      uint8_t buttonIndex = Machine::getButtonIndex();
      if (buttonIndex != BTN_NONE)
      {
        selectedRecipe = buttonIndex;
        Machine::setLEDMask(0);
        Machine::setLED(selectedRecipe, true);
      }
      // Si une recette a été choisie et qu'on appuie sur le bouton start,
      // passer en mode service de la recette sélectionnée
      else if (Machine::isGoPressed() && selectedRecipe != BTN_NONE)
      {
        setStateDispensing();
      }
      // Animation des LED
      Animation::animateRainbow();
      break;
    }
    case DISPENSING:
    {
      Machine::home();
      uint8_t i_drink = 0;
      // Tant qu'on n'a pas atteint le caractère __END__ de la recette
      while(recipes[selectedRecipe][i_drink] != __END__)
      {
        // Demande le service de la boisson pointée par l'index courant
        drinks[recipes[selectedRecipe][i_drink++]].dispense();
      }
      // Une fois fini, retourne à la position d'origine
      Machine::move(0);
      // Retour à l'état d'attente
      setStateIdle();
      break;
    }
    case DEBUG:
    {
      switch(Machine::getButtonIndex())
      {
        case 0: 
          Machine::stepper.enableOutputs(); 
          Machine::stepper.move(STEPPER_STEPS_PER_MM * 100); 
          Machine::stepper.runToPosition();
          Machine::stepper.disableOutputs(); 
          break;
        case 1: 
          Machine::stepper.enableOutputs(); 
          
          Machine::stepper.move(STEPPER_STEPS_PER_MM * -100); 
          Machine::stepper.runToPosition();
          Machine::stepper.disableOutputs(); 
          break;
          break;
        case 2: 
          Machine::startDispensing();
          break;
        case 3:
         Machine::stopDispensing();
          break;
        default:
          if (Machine::isGoPressed())
            Machine::home();
          break;
          }
      break;
    }
  }
  
  // put your main code here, to run repeatedly:
    
   // digitalWrite(8, digitalRead(A5));

 // Machine::home();
  
 /* digitalWrite(8, LOW);
  if (digitalRead(A4) == LOW)
  {
    
    digitalWrite(8, HIGH);
    Vodka.dispense();
    Vodka.dispense();
    Gin.dispense();  
  }*/
}
