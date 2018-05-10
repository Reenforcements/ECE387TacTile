
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwmD1 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwmD2 = Adafruit_PWMServoDriver(0x41);

unsigned int SERVOMIN = 160; // this is the 'minimum' pulse length count (out of 4096)
unsigned int SERVOMAX = 512; // this is the 'maximum' pulse length count (out of 4096)

const unsigned char CLOCK_PIN = 2;
const unsigned char DATA_PIN = 4;

volatile uint8_t motorData[25];
volatile bool readyForMore = true;
volatile uint8_t copiedData[25] = {
    128,   128,  128,  128,  128,
    128,   128,  128,  128,  128,
    128,   128,  128,  128,  128,
    128,   128,  128,  128,  128,
    128,   128,  128,  128,  128,
};

volatile byte currentMotorIndex = 0;
volatile byte currentByte = 0;
volatile byte currentBit = 7;
volatile unsigned long lastTime = millis();
void shiftRegisterInterrupt() {

    if (millis() - lastTime > 50) {
        currentBit = 7;
        currentMotorIndex = 0;
    }
    lastTime = millis();

    currentByte += (digitalRead(DATA_PIN) == HIGH ? 1 : 0) << currentBit;

    if (currentBit == 0) {
        currentBit = 7;

        newCurrentByte(currentByte);

        currentByte = 0;
    } else {
        currentBit--;
    }
}

void newCurrentByte(byte b) {
    motorData[currentMotorIndex] = b;

    currentMotorIndex++;
    if (currentMotorIndex >= 25) {
        currentMotorIndex = 0;
        newMotorData();
    }
}
void newMotorData() {
    Serial.println("==================");
    Serial.println(millis());
    Serial.println("==================");

    for (byte x = 0; x < 5; x++) {
        for (byte y = 0; y < 5; y++) {
            byte current = motorData[x * 5 + y];


            Serial.print(current);
            if (current < 100) {
                Serial.print(" ");
            }
            if (current < 10) {
                Serial.print(" ");
            }
            // Always at least one digit
            Serial.print(" ");
        }
        Serial.println("");
    }
    if (readyForMore) {
        for (int i = 0; i < 25; i++) {
            copiedData[i] = motorData[i];
        }
        readyForMore = false;
    }
}

void setup() {
    // put your setup code here, to run once:
    pinMode(CLOCK_PIN, INPUT);
    pinMode(DATA_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), shiftRegisterInterrupt, RISING);

    pwmD1.begin();
    pwmD2.begin();

    pwmD1.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    pwmD2.setPWMFreq(60);

    Serial.begin(57600);
    Serial.println("Started.");
}

void loop() {
    //    for (uint16_t g = SERVOMIN; g < SERVOMAX; g++) {
    //        pwm.setPWM(0, 0, g);
    //    }
    //    for (uint16_t g = SERVOMAX; g > SERVOMIN; g--) {
    //        pwm.setPWM(0, 0, g);
    //    }
    if (readyForMore == false) {
        for (byte x = 0; x < 5; x++) {
            for (byte y = 0; y < 5; y++) {
                byte servoNum = x * 5 + y;
                unsigned int currentValue = copiedData[servoNum] + 245;
                currentValue = min(SERVOMAX, currentValue);
                currentValue = max(SERVOMIN, currentValue);
                //Serial.println(currentValue);
                if (servoNum < 16) {
                    pwmD1.setPWM(servoNum, 0, currentValue);
                    
                } else {
                    pwmD2.setPWM(servoNum - 16, 0, currentValue);
                }

            }
        }
        readyForMore = true;
    }

}
