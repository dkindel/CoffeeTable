#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN 13


LCDKeypad lcd;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

  

void setup()
{
  
  Serial.begin(9600); //used currently for debugging

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(5));
  
  menu_setup();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  handle_main_menu();
}




