#include <wiringSerial.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>

/*** Defines ***/
#define NUM_OF_MOTORS 25

/*** Prototypes ***/

void writeArray(int8_t *fp, int8_t *arrayToWrite);
int8_t initSerialFile(char *filename, int8_t *fp, int16_t baudRate);
