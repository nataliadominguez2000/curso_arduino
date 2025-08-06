#include "SoftPWM_Generic.h"

SoftPWM::SoftPWM() {
  numChannels = 0;
  period_us = 2000; // ~500Hz
}

void SoftPWM::begin() {
  for (uint8_t i = 0; i < MAX_CHANNELS; i++) {
    channels[i].pin = 255;
    channels[i].duty = 0;
    channels[i].lastChange = 0;
    channels[i].state = false;
  }
}

void SoftPWM::attach(uint8_t pin) {
  if (numChannels >= MAX_CHANNELS) return;

  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);

  channels[numChannels].pin = pin;
  channels[numChannels].duty = 0;
  channels[numChannels].lastChange = micros();
  channels[numChannels].state = false;

  numChannels++;
}

void SoftPWM::setPWM(uint8_t pin, uint8_t duty) {
  for (uint8_t i = 0; i < numChannels; i++) {
    if (channels[i].pin == pin) {
      channels[i].duty = duty;
      return;
    }
  }
}

void SoftPWM::update() {
  uint32_t now = micros();

  for (uint8_t i = 0; i < numChannels; i++) {
    Channel& ch = channels[i];

    uint32_t highTime = ((uint32_t)ch.duty * period_us) / 255;
    uint32_t lowTime = period_us - highTime;

    if (ch.state) {
      // Currently HIGH
      if (now - ch.lastChange >= highTime) {
        digitalWrite(ch.pin, LOW);
        ch.lastChange = now;
        ch.state = false;
      }
    } else {
      // Currently LOW
      if (now - ch.lastChange >= lowTime) {
        if (ch.duty > 0) {
          digitalWrite(ch.pin, HIGH);
        }
        ch.lastChange = now;
        ch.state = true;
      }
    }
  }
}
