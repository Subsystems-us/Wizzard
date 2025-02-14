// Wizzard Version 1.0

#include <Adafruit_NeoPixel.h>
#include "notes.h"

#define NEO_PIN 10  //Led output pin
#define NUMPIXELS 9
#define LED_OFF 0
#define LED_RED 1
#define LED_GREEN 2
#define BUZZ_PIN 8
#define NUM_GAMES 4
#define NO_KEY 12  // Returned value if no key pressed
#define SELECT_KEY A3
#define ENTER_KEY A2

Adafruit_NeoPixel array = Adafruit_NeoPixel(9, NEO_PIN, NEO_GRB + NEO_KHZ800);

const uint8_t but[11] = { 7, 6, 5, 4, 3, 2, 1, 0, 18, SELECT_KEY, ENTER_KEY };
const uint32_t colorL[] = { array.Color(0, 0, 0), array.Color(255, 0, 0), array.Color(0, 255, 0) };  //[OFF, RED, GREEN]
uint8_t leds[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool soundON = true;
uint16_t note[] = { NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };  // frequency array for notes B3 to C5

void setup() {
  setupButtons();             // Set pins as inputs with pullups
  pinMode(BUZZ_PIN, OUTPUT);  // Pin as output for the buzzer
  array.begin();
  array.setBrightness(20);
  array.clear();
  array.show();
  randomSeed(analogRead(0));  // Randomize
}

void loop() {
  // Will run on reset. Choose which game to play
  uint8_t keyIn = NO_KEY;
  ledsOut();
  keyIn = waitForKey();

  // Game or sound control has been selected
  // To add a custom game, increment the NUMGAMES define and add a case to call your subroutine
  switch (keyIn) {
    case 0:  // Lights Out
      lightsOut();
      break;
    case 1:  // Repeat
      repeatGame();
      break;
    case 2:  // Music Composer
      composerGame();
      break;
    case 3:  //Random Lights
      ticTacToe1();
      break;
    case 4:
      ticTacToe2();
      break;
    case 5:
      randomLights();
      break;
    case SELECT_KEY:
      soundON = !soundON;
      break;
  }
  ledClear();
}

void setupButtons() {
  // Set all the button pins as inputs with pullups
  for (int i = 0; i < 11; i++) pinMode(but[i], INPUT_PULLUP);
}

// Output the current value of the led array to the leds
void ledsOut() {
  for (int i = 0; i < NUMPIXELS; i++) array.setPixelColor(i, colorL[leds[i]]);
  array.show();
}

uint8_t getKey() {
  // Scans the keys and returns NO_KEY if none
  for (int i = 0; i < 11; i++) {
    if (!digitalRead(but[i])) {
      uint8_t curKey;  // Keep track of the previous value to restore it
      // For 0-8, light led, make sound
      if (i < 9) {
        curKey = leds[i];
        lightLed(i, LED_GREEN);
        if (soundON) tone(BUZZ_PIN, note[i], 100);
      }
      delay(100);
      while (!digitalRead(but[i])) {};
      if (i < 9) leds[i] = curKey;  // Restore original value.

      // Handle special keys
      if (i == 9) i = SELECT_KEY;
      if (i == 10) i = ENTER_KEY;
      ledsOut();
      return i;
    }
  }
  return NO_KEY;
}

// Return the key number only after a key is pressed
uint8_t waitForKey() {
  uint8_t keyIn = NO_KEY;
  while (keyIn == NO_KEY) keyIn = getKey();
  // delay(150);  // Debounce

  return keyIn;
}

// Return the key number only after pressed and only 0-8
uint8_t waitForNumKey() {
  uint8_t keyIn = NO_KEY;
  while (keyIn > 8) keyIn = getKey();
  // delay(150);  // Debounce
  return keyIn;
}

// Light the leds in a fun pattern
void ledChase(uint8_t colorLeds) {
  for (int j = 0; j < 10; j++) {  //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < array.numPixels(); i = i + 3) {
        array.setPixelColor(i + q, colorL[colorLeds]);
      }
      array.show();

      delay(50);

      for (uint16_t i = 0; i < array.numPixels(); i = i + 3) {
        array.setPixelColor(i + q, 0);  //turn every third pixel off
      }
    }
  }
}

// Clear all leds
void ledClear() {
  for (int i = 0; i < NUMPIXELS; i++) leds[i] = 0;
}

// Light a particular led a particular color
void lightLed(uint8_t ledNum, uint8_t ledColor) {
  leds[ledNum] = ledColor;
  ledsOut();
}

// Play a fun end sound.
void funSound() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 9; j++) {
      tone(BUZZ_PIN, note[j], 50);
      delay(50);
    }
  }
}