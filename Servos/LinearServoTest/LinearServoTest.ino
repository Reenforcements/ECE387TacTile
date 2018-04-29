#include <Servo.h>
Servo myservo;
void setup() {
    // put your setup code here, to run once:
    myservo.attach(3);
    pinMode(A0, INPUT);
}


void loop() {
    // put your main code here, to run repeatedly:
    byte deg = byte(  (float(analogRead(A0)) / 1024.0) * 180.0  );
    myservo.write(deg);
}
