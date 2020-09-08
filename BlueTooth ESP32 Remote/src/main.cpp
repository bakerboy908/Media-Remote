#include <Arduino.h>

#include "BleKeyboard.h"

//Global stuff
BleKeyboard keyboard("Bike Media Remote", "Gondwana", 100);

#define PLAY_PAUSE_BUTTON 35 // RTC_GPIO5
#define NEXT_TRACK_BUTTON 26 //RTC_GPIO7
#define LAST_TRACK_BUTTON 34 //RTC_GPIO4
#define VOLUME_UP_BUTTON 33  //RTC_GPIO8

#define DEBOUNCE_DELAY 200 //milliseconds

void IRAM_ATTR playPauseISR(void);
void IRAM_ATTR nextTrackISR(void);
void IRAM_ATTR lastTrackISR(void);
void IRAM_ATTR volUpISR(void);

void setup()
{
  // start the keyboard
  keyboard.begin();
  //start serial monitor for debugging
  Serial.begin(9600);
  //set pin 35 as an input
  pinMode(PLAY_PAUSE_BUTTON, INPUT);
  pinMode(NEXT_TRACK_BUTTON, INPUT);
  pinMode(LAST_TRACK_BUTTON, INPUT);
  pinMode(VOLUME_UP_BUTTON, INPUT);
  // setup an interupt for pin 35 falling edge as button is pulled high
  attachInterrupt(PLAY_PAUSE_BUTTON, playPauseISR, FALLING);
  attachInterrupt(NEXT_TRACK_BUTTON, nextTrackISR, FALLING);
  attachInterrupt(LAST_TRACK_BUTTON, lastTrackISR, FALLING);
  attachInterrupt(VOLUME_UP_BUTTON, volUpISR, FALLING);
}

void loop()
{
  // Do nothing this program is ISR driven.
}
/**
 * @brief ISR for playing or pausing a track
 * 
 */
void IRAM_ATTR playPauseISR(void)
{
  static long debounceDelay = DEBOUNCE_DELAY;
  static long lastDebounceTime = 0;
  if (keyboard.isConnected())
  {
    if (millis() - lastDebounceTime > debounceDelay)
    {
      keyboard.write(KEY_MEDIA_PLAY_PAUSE);
      Serial.println("PLAY/PAUSE");
      lastDebounceTime = millis();
    }
  }
}
/**
 * @brief ISR to skip a track
 * 
 */
void IRAM_ATTR nextTrackISR(void)
{
  static long debounceDelay = DEBOUNCE_DELAY;
  static long lastDebounceTime = 0;
  if (keyboard.isConnected())
  {
    if (millis() - lastDebounceTime > debounceDelay)
    {
      keyboard.write(KEY_MEDIA_NEXT_TRACK);
      Serial.println("NEXT TRACK");
      lastDebounceTime = millis();
    }
  }
}
/**
 * @brief ISR to go back a track or restart 
 * 
 */
void IRAM_ATTR lastTrackISR(void)
{
  static long debounceDelay = DEBOUNCE_DELAY;
  static long lastDebounceTime = 0;
  if (keyboard.isConnected())
  {
    if (millis() - lastDebounceTime > debounceDelay)
    {
      keyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
      Serial.println("LAST TRACK");
      lastDebounceTime = millis();
    }
  }
}
/**
 * @brief ISR to turn the volume up
 * 
 */
void IRAM_ATTR volUpISR(void)
{
  static long debounceDelay = DEBOUNCE_DELAY;
  static long lastDebounceTime = 0;
  if (keyboard.isConnected())
  {
    if (millis() - lastDebounceTime > debounceDelay)
    {
      keyboard.write(KEY_MEDIA_VOLUME_UP);
      Serial.println("CRANK IT");
      lastDebounceTime = millis();
    }
  }
}