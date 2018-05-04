#include <Wire.h>

#define DEVICE_ID 4
#define MAX_PACKET_SIZE 32 //Wire Library sends and receives max 32 bytes

typedef struct{
  uint8_t numReceiviedFromPi; 
  int8_t *dataReceivedFromPi;
} i2cToPi;

extern i2cToPi *pi;

void onReceive_f();
void onRequest_f();
void initWire();
void initI2CToPi(i2cToPi *pi_r);
void writeToSerialMonitor(i2cToPi *pi_r);

