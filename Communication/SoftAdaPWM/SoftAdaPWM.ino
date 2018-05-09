// Simple sketch to read out one register of an I2C device
#define I2C_TIMEOUT 1000

//#define I2C_PULLUP 1
#define SDA_PORT PORTD
#define SDA_PIN 7 // = A4
#define SCL_PORT PORTD
#define SCL_PIN 6 // = A5

#include "Driver.h"

SoftServoDriver pwm = SoftServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  535 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

void setup() {
    Serial.begin(57600);
    Serial.println("8 channel Servo test!");


    pwm.begin();

    pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    delay(1000);
}

void loop() {
    // Drive each servo one at a time
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        for (byte g = 0; g < 15; g++) {
            pwm.setPWM(servonum, 0, pulselen);
        }
        //delay(500);
    }

    delay(500);
    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        for (byte g = 0; g < 15; g++) {
            pwm.setPWM(servonum, 0, pulselen);
        }
        //delay(500);
    }

}
