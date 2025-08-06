#ifndef SOFTPWM_GENERIC_H
#define SOFTPWM_GENERIC_H

#include <Arduino.h>

#define MAX_CHANNELS 8

class SoftPWM {
  public:
    SoftPWM();
    void begin();
    void attach(uint8_t pin);
    void setPWM(uint8_t pin, uint8_t duty); // 0–255
    void update(); // Llamar en loop()

  private:
    struct Channel {
      uint8_t pin;
      uint8_t duty;
      uint32_t lastChange;
      bool state;
    };

    Channel channels[MAX_CHANNELS];
    uint8_t numChannels;
    uint32_t period_us;  // Periodo PWM completo en µs
};

#endif
