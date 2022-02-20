#ifndef MOTOR_H

#define MOTOR_H

#include "Arduino.h"

class Motor {
 public:
  Motor(byte _fwPin, byte _bwPin, byte _minPWM, byte _maxPWM)
      : forwardPin(_fwPin),
        backwardPin(_bwPin),
        minPWM(_minPWM),
        maxPWM(_maxPWM) {
    pinMode(this->forwardPin, OUTPUT);
    pinMode(this->backwardPin, OUTPUT);
    this->stop();
  }

  void setSpeed(int _speed) {
    if (_speed == 0) {
      Serial.println("STOP");
      stop();
    } else if (_speed > 0) {
      speed = this->mapSpeed(_speed);
      Serial.print("Setting speed to ");
      Serial.println(speed);
      this->forward(speed);
    }
  }

  void forward(byte _speed) {
    analogWrite(forwardPin, _speed);
    digitalWrite(backwardPin, LOW);
  }

  void stop() {
    digitalWrite(forwardPin, LOW);
    digitalWrite(backwardPin, LOW);
  }

 private:
  const byte forwardPin;
  const byte backwardPin;
  const uint8_t minPWM;
  const uint8_t maxPWM;
  uint8_t speed = 0;

  uint8_t mapSpeed(int _speed) { return map(_speed, 0, 100, minPWM, maxPWM); }
};

#endif
