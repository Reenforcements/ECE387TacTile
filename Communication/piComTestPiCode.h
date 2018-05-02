#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DEVICE_ID 4
#define MAX_PACKET_SIZE 32
#define NUMBER_OF_MOTORS 25


typedef struct{
	int8_t i2cFile;
	int8_t error;
	int8_t *writeArray;
} piI2C;



int8_t initPiI2C(char *filename, piI2C *newPiI2CBus);
int8_t testConnection(piI2C *i2cBus);
int8_t writeToMotors(piI2C *i2cBus, int8_t *positionsToWrite);
