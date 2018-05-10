#include "wiringPiSerial.h"



int8_t initSerialFile(char *filename, int8_t *fd, int16_t baudRate){
	wiringPiSetup();
	*fd = serialOpen(filename, baudRate);
	 return *fd;
}


void writeArray(int8_t *arrayToWrite){
	for(int i = 0; i < 25; i++){
		serialPutchar(serialFile, *(arrayToWrite + i));
	}
}
