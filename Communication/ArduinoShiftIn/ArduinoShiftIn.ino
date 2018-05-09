
const unsigned char CLOCK_PIN = 2;
const unsigned char DATA_PIN = 4;

volatile uint8_t motorData[25];
volatile byte currentMotorIndex = 0;

volatile byte currentByte = 0;
volatile byte currentBit = 7;
volatile unsigned long lastTime = millis();
void shiftRegisterInterrupt() {

    if (millis() - lastTime > 100) {
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
    Serial.println("==================");
    Serial.println("==================");
    for (byte x = 0; x < 5; x++) {
        for (byte y = 0; y < 5; y++) {
            byte current = motorData[x + y*5];
            Serial.print(current);
            if(current < 100) {
                Serial.print(" ");
            }
            if(current < 10) {
                Serial.print(" ");
            }
            // Always at least one digit
            Serial.print(" ");
        }
        Serial.println("");
    }
}

void setup() {
    // put your setup code here, to run once:
    pinMode(CLOCK_PIN, INPUT);
    pinMode(DATA_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), shiftRegisterInterrupt, RISING);

    Serial.begin(57600);
    Serial.println("Started.");
}

void loop() {
    // put your main code here, to run repeatedly:

}
