#define SDA_PORT PORTD
#define SDA_PIN 6 // = D6
#define SCL_PORT PORTD
#define SCL_PIN 7 // = D7

#include <SoftI2CMaster.h>
#include "PWMServoDriverSoftI2C.h"




Adafruit_PWMServoDriver::Adafruit_PWMServoDriver(uint8_t addr) {
  _i2caddr = addr;

}

void Adafruit_PWMServoDriver::setPWMFreq(float freq) {
  freq *= 0.9;  // Correct for overshoot in the frequency setting (see issue #11).
  float prescaleval = 25000000;
  prescaleval /= 4096;
  prescaleval /= freq;
  prescaleval -= 1;

  uint8_t prescale = floor(prescaleval + 0.5);

  
  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode&0x7F) | 0x10; // sleep
  write8(PCA9685_MODE1, newmode); // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  write8(PCA9685_MODE1, oldmode | 0xa0);  //  This sets the MODE1 register to turn on auto increment.

}

void Adafruit_PWMServoDriver::setPin(uint8_t num, uint16_t val, bool invert)
{
  // Clamp value between 0 and 4095 inclusive.
  val = min(val, (uint16_t)4095);
  if (invert) {
    if (val == 0) {
      // Special value for signal fully on.
      setPWM(num, 4096, 0);
    }
    else if (val == 4095) {
      // Special value for signal fully off.
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, 4095-val);
    }
  }
  else {
    if (val == 4095) {
      // Special value for signal fully on.
      setPWM(num, 4096, 0);
    }
    else if (val == 0) {
      // Special value for signal fully off.
      setPWM(num, 0, 4096);
    }
    else {
      setPWM(num, 0, val);
    }
  }
}


void Adafruit_PWMServoDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  uint8_t I2C_8BitAddr = (_i2caddr << 1) | I2C_WRITE;
  i2c_start(I2C_8BitAddr);
  i2c_write(LED0_ON_L+4*num);
  i2c_write(on);
  i2c_write(on>>8);
  i2c_write(off);
  i2c_write(off>>8);
  i2c_stop();
}


void Adafruit_PWMServoDriver::init_PWMDriverI2C(void) {
  i2c_init();
}

void Adafruit_PWMServoDriver::reset(void) {
  write8(PCA9685_MODE1, 0x80);
  delay(10);
}

uint8_t Adafruit_PWMServoDriver::read8(uint8_t addr) {
  uint8_t ret = 0;
  uint8_t I2C_8BitAddr = (_i2caddr << 1) | I2C_WRITE;
  i2c_start(I2C_8BitAddr);
  i2c_write(addr);
  
  I2C_8BitAddr = (_i2caddr << 1) | I2C_READ;
  ret = i2c_read(true);
  i2c_stop();
  return ret;
}

void Adafruit_PWMServoDriver::write8(uint8_t addr, uint8_t data) {
  uint8_t I2C_8BitAddr = (_i2caddr << 1) | I2C_WRITE;
  i2c_start(I2C_8BitAddr);
  i2c_write(addr);
  i2c_write(data);
  i2c_stop();
}
