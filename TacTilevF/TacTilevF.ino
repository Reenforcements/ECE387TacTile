#define I2C_TIMEOUT 1000

//#define I2C_PULLUP 1
#define SDA_PORT PORTD
#define SDA_PIN 7 // = A4
#define SCL_PORT PORTD
#define SCL_PIN 6 // = A5

#include "Driver.h"

SoftServoDriver pwm1 = SoftServoDriver(0x40);
//SoftServoDriver pwm2 = SoftServoDriver(0x41);
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  535 // this is the 'maximum' pulse length count (out of 4096)
uint8_t curVal[5][5] = {0};
uint8_t temp[25] = {0};
void setup(){ 

  Serial.begin(9600);
  pwm1.begin();
  pwm1.setPWMFreq(60);
//  pwm2.begin();
  //pwm2.setPWMFreq(60);
  delay(1000);
//Wire.onReceive(&oRec_f);
  
}

void loop() {
    // INTERUPT FOR INCOMING DATA REQUIRED
   // updateFrame();
   // writeImage();

   pwm1.setPWM(1,0, 150);
    
}

//void oRec_f(){
//    initI2CToPi(); 
//     getPiData(temp);
//}
void updateFrame(){
//   initI2CToPi(); 
//     getPiData(temp);
   
    for(int c = 0; c < 5; c++ ){
         for(int r = 0; r <5; r ++){
               curVal[r][c] = temp[r +(5*c)];
               Serial.print("curVal: ");
               Serial.print(r);  
               Serial.print(" ");
               Serial.print(c); 
               Serial.println(" ");
               Serial.print(temp[r + (5*c)]);
               Serial.println(" ");
            }
            
           // writeToSerialMonitor();           
        } 
}
/*
void writeImage(){ // sets output to current values 
//    pwm1 = Adafruit_PWMServoDriver(0x40);
//    pwm2 = Adafruit_PWMServoDriver(0x41);
//    pwm1.begin();
//    pwm1.setPWMFreq(60);
//    pwm2.begin();
//    pwm2.setPWMFreq(60);

    //pwm1.setPWM(1, 0, SERVOMIN);  
    for(int c = 0; c < 5; c++ ){
        for(int r = 0; r <5; r ++){
             double plsLen = map(curVal[c][r], 0, 255, SERVOMIN, SERVOMAX);
             if((r *5) > 15){
                 pwm2.setPWM((5*r) + c - 16, 0, plsLen);
             }
             else{
                pwm1.setPWM((5*r) + c, 0, plsLen);
             }
            
        }  
    }   

}
*/

