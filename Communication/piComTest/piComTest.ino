#include <Wire.h>
//uint8_t write_n = 1;
const uint8_t deviceID = 0x04;
uint8_t *dataReceived;
uint8_t numReceived = 0;
uint8_t maxReceived = 32; //Wire Library sends and receives max 32 bytes


void setup() {
  dataReceived = (byte*)malloc(sizeof(byte)*maxReceived);
  Wire.begin(deviceID);
  Serial.begin(9600);
  Wire.onRequest(writeToPi);
  Wire.onReceive(receiveFromPi);
}

void loop() {
  delay(200);
  while(numReceived > 0){
    writeToSerialMonitor(); 
    numReceived -= 1;
  }
}

void receiveFromPi(int numBytes){
  //write_n = 1;
  numBytes = Wire.available();
  uint8_t currentByte = 0x0;
  if(numBytes > maxReceived){
    numBytes = maxReceived;    
  }
  numReceived = numBytes;
  for(int i = 0; i < numBytes; i++){
    *(dataReceived + i) = Wire.read();     
  }
}

void writeToPi(){
  uint8_t address = *dataReceived;
  if(address == 0x01){
    Wire.write(deviceID);  
  }
}

void writeToSerialMonitor(){
  Serial.println((int)*(dataReceived + (numReceived - 1)));
}


