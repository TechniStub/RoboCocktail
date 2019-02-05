/*******************************************************************************
 * Projet RoboCocktail
 * Configuration matérielle
 */

#ifndef _CONFIG_H
#define _CONFIG_H

// Brochage des boutons
// A configurer en entrée avec pull-up
// Actifs à l'état bas
#define BTN_1_PIN A0
#define BTN_2_PIN A1
#define BTN_3_PIN A2
#define BTN_4_PIN A3
#define BTN_GO_PIN 8

// Masque des boutons
#define BTN_1 1
#define BTN_2 2
#define BTN_3 4
#define BTN_4 8
#define BTN_GO 16

// Constante indiquant qu'aucun bouton n'est pressé (hormis GO)
#define BTN_NONE 0xFF

// Fin de course et détection verre
#define SW_HOME 2
#define SW_GLASS 3

// Brochage du driver de pas à pas
#define STEPPER_STEP_PIN    5
#define STEPPER_DIR_PIN     4
#define STEPPER_ENABLE_PIN  6

// Broche de pilotage du servomoteur
#define SERVO_PIN   9

// Broche de commande des NeoPixels
#define NEOPIXEL_PIN  7
#define NEOPIXEL_NUM  24

// Brochage des LEDs des boutons
#define BTN_1_LED_PIN 13
#define BTN_2_LED_PIN 12
#define BTN_3_LED_PIN 11
#define BTN_4_LED_PIN 10

// Masque des LEDs
#define BTN_1_LED 1
#define BTN_2_LED 2
#define BTN_3_LED 4
#define BTN_4_LED 8

// Nombre de pas pour réaliser 1 mm
#define STEPPER_STEPS_PER_MM  20

// Vitesse maximale du chariot (en pas/s)
#define STEPPER_MAX_SPEED         4500
// Accélération du chariot (en pas/s²)
#define STEPPER_ACCELERATION  12000

#define STEPPER_HOME_POSITION     2000

// Position de service du servomoteur
#define SERVO_SERVING_POSITION  1500
// Position de repos du servomoteur
#define SERVO_IDLE_POSITION     950
// Temps de déplacement du servomoteur
#define SERVO_DELAY             200

#endif

