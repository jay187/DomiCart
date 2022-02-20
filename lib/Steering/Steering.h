#ifndef STEERING_H

#define STEERING_H

#include "Servo.h"

class Steering {
 public:
  Steering(byte pin) {
    this->setupServo(pin);
    this->setLock();
  }
  Steering(byte pin, int lock) : lock(lock) {
    this->setupServo(pin);
    this->setLock();
  }

  void steer(int _pos) {
    int pos = map(_pos, 0, 1024, this->min, this->max);
    this->servo.write(pos);
  }

 private:
  Servo servo;
  int lock = 30;
  int min;
  int max;

  void setupServo(byte pin) {
    this->servo.attach(pin);
    this->servo.write(90);
  }

  void setLock() {
    this->min = 90 - this->lock;
    this->max = 90 + this->lock;
  }
};

#endif
