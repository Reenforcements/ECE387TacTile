#include "piComTest.h"
i2cToPi *pi;

void setup() {
  Serial.begin(9600);
  initI2CToPi();
}

void loop() {
  delay(2000);
}

void initWire(){
   Wire.begin(DEVICE_ID);
   Wire.onRequest(onRequest_f);
   Wire.onReceive(onReceive_f);
}

void initI2CToPi(){
  pi = (i2cToPi*)malloc(sizeof(i2cToPi));
  pi->dataReceivedFromPi = (int8_t*)malloc(sizeof(int8_t)*MAX_PACKET_SIZE);
  initWire();
}

void onReceive_f(int numBytes){
  if(numBytes > MAX_PACKET_SIZE ){
    numBytes = MAX_PACKET_SIZE ;    
  }
  pi->numReceiviedFromPi = numBytes;
  for(int i = 0; i < numBytes; i++){
    *((pi->dataReceivedFromPi) + i) = Wire.read();     
  }
}

void onRequest_f(){
  uint8_t address = *(pi->dataReceivedFromPi);
  if(address == 0x01){
    Wire.write(DEVICE_ID);  
  }
}

void writeToSerialMonitor(){
  for(int i = 0; i < (pi->numReceiviedFromPi); i++){
    Serial.println(*(pi->dataReceivedFromPi + i)); 
  }
}

void getPiData(int8_t *workingArray){
  for(int i = 0; i < (pi->numReceiviedFromPi); i++){
    *(workingArray + i) = *(pi->dataReceivedFromPi + i);  
  }
}
