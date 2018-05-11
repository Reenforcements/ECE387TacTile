#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//#define SERVOMIN 0
#define SERVOMIN  145 // this is the 'minimum' pulse length count (out of 4096) - 0 degrees
#define SERVOMAX  535 // this is the 'maximum' pulse length count (out of 4096) - 180 degrees

uint8_t motorData[25] = {0};

int8_t *bytesIn;
uint8_t numByteIn = 0;
uint8_t arrayIn = 0;

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   Serial.println(" Begin Setup");
   bytesIn = (int8_t*)malloc(sizeof(int8_t) * 25);

   pwm1.begin();
   pwm1.setPWMFreq(60);  // This is the maximum PWM frequency
   pwm2.begin();
   pwm2.setPWMFreq(60);  // This is the maximum PWM frequency
   
   delay(1000);
   Serial.write(255);
  
}

void loop() {
 if(arrayIn == 1){
    loadData();
    arrayIn = 0;
    writeImage();
    
 }


 

}

void serialEvent() {
  while(Serial.available()){
    *(bytesIn + numByteIn) = Serial.read();
     numByteIn++;   
  }
  if(numByteIn == 25){
    numByteIn = 0;
    arrayIn = 1;
    Serial.flush();
  }
}


void loadData(){ 
  
      for(int i =0; i < 25; i++){
          motorData[i] = bytesIn[i]; 
          bytesIn[i] = 0;     
     }
}



void writeImage(){ // sets output to current values 
    int plsLen = 0;
    
     for(int i = 0; i < 25; i++){
          plsLen =  map(motorData[i], 0, 255, SERVOMIN, SERVOMAX);
          if(i > 15){
             
              pwm2.setPWM(i - 16, 0, plsLen );
          }
          else{
              pwm1.setPWM(i,0, plsLen);
          }
       }

}
      
  
