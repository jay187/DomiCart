#include <Arduino.h>

#include "Motor.h"
#include "RFIDReader.h"
#include "Steering.h"
#include "pins.h"

#define MOTOR_MIN_PWM 75
#define MOTOR_MAX_PWM 100

// RFID Reader
RFIDReader rfidreader(RFID_CS_PIN, RFID_PD_PIN);

// Motor
Motor motor(MOTOR_IN1, MOTOR_IN2, MOTOR_MIN_PWM, MOTOR_MAX_PWM);

// Steering
Steering steering(SERVO_PIN);

void setup() {
  // Open Serial
  Serial.begin(115200);

  // setup rfid reader
  rfidreader.setup();
}

void loop() {
  rfidreader.loop();
  // setMotorSpeed(0);
  if (Serial.available() > 0) {
    int pos = Serial.parseInt();
    Serial.print("Position ");
    Serial.println(pos);
    // motor.setSpeed(speed);
    steering.steer(pos);
  }
  // put your main code here, to run repeatedly:
}
