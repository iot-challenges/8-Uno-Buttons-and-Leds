/**
 *
 *****************************************************************
 * IOT Challenges - https://instagram.com/iotchallenges          *
 *****************************************************************
 * Evandro Fruhauf                                               *
 *  GitHub - https://github.com/evandrodp                        *
 *  LinkedIn - http://linkedin.com/in/evandrofruhauf             *
 *****************************************************************
 * This code can contain parts from other open-sources projects, *
 * whenever possible it will be quoted.                          *
 *****************************************************************
 *
 * Buttons and Leds
 *
 * Challenge: Make the buttons works with the leds using Deboucing
 *
 * This code uses Bounce2 library.
 *
**/
#include <Arduino.h>
#include <Bounce2.h>

// define how the code will work
const int useDebouncing = true;

// Set LEDs pins
#define LED_RED 4
#define LED_YELLOW 5
#define LED_GREEN 6
#define LED_BLUE 7

// Set BUTTONS pins
#define BUTTON_RED 8
#define BUTTON_YELLOW 9
#define BUTTON_GREEN 10
#define BUTTON_BLUE 11

// Initialise the status vars
int statusRed = LOW;
int statusYellow = LOW;
int statusGreen = LOW;
int statusBlue = LOW;

// Instantiate a Bounce object
Bounce debouncerRed = Bounce();
Bounce debouncerYellow = Bounce();
Bounce debouncerGreen = Bounce();
Bounce debouncerBlue = Bounce();
int debouncems = 15;

void checkButton(int button, int led);
void checkButtonDebouncing(Bounce& debouncer, int led, int& status);
void initialiseDebouncing();
void withoutDebouncing();
void withDebouncing();

void setup()
{
  Serial.begin(9600);
  // initialise LEDs  digital pin as an output.
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // initialise BUTTONS digital pin as input pullup (Ground)
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  if (useDebouncing) {
    // initialise Debounce on the buttons
    initialiseDebouncing();
  }
}

void loop() {
  if (useDebouncing) {
    withDebouncing();
  } else {
    withoutDebouncing();
  }
}

void checkButton(int button, int led) {
  if (digitalRead(button) == LOW) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

void checkButtonDebouncing(Bounce& debouncer, int led, int& status) {
  debouncer.update();
  int value = debouncer.fell();
  if (value == HIGH) {
    if (status == LOW) {
      digitalWrite(led, HIGH);
      status = HIGH;
    } else {
      digitalWrite(led, LOW);
      status = LOW;
    }
  }
}

void initialiseDebouncing() {
  debouncerRed.attach(BUTTON_RED);
  debouncerRed.interval(debouncems);
  debouncerYellow.attach(BUTTON_YELLOW);
  debouncerYellow.interval(debouncems);
  debouncerGreen.attach(BUTTON_GREEN);
  debouncerGreen.interval(debouncems);
  debouncerBlue.attach(BUTTON_BLUE);
  debouncerBlue.interval(debouncems);
}

void withoutDebouncing() {
  checkButton(BUTTON_RED, LED_RED);
  checkButton(BUTTON_YELLOW, LED_YELLOW);
  checkButton(BUTTON_GREEN, LED_GREEN);
  checkButton(BUTTON_BLUE, LED_BLUE);
}

void withDebouncing() {
  checkButtonDebouncing(debouncerRed, LED_RED, statusRed);
  checkButtonDebouncing(debouncerYellow, LED_YELLOW, statusYellow);
  checkButtonDebouncing(debouncerGreen, LED_GREEN, statusGreen);
  checkButtonDebouncing(debouncerBlue, LED_BLUE, statusBlue);
}
