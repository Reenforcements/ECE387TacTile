#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int8_t i2cFile;
int8_t *error;
int8_t *motorPositionArray;
const uint8_t deviceID = 0x04;
const uint8_t maxPacketLength = 32;
const uint8_t numberOfMotors = 25;

int8_t testConnection(int8_t i2cFileTest);
int8_t writeToMotors(int8_t i2cFile, int8_t *positionsToWrite);

typedef struct{
	uint8_t length;
	int8_t *data;
} dataPacket;


int main(){
	error = (int8_t*)malloc(sizeof(int8_t));
	motorPositionArray = (int8_t*)malloc(sizeof(int8_t)*numberOfMotors);

	char *filename = (char*)"/dev/i2c-1";

	i2cFile = open(filename, O_RDWR);
	if(i2cFile < 0){
		printf("Error opening I2C File\n");
		return -1;
	}

	*error = testConnection(i2cFile);

	for(int i = 0; i < numberOfMotors; i++){
		*(motorPositionArray + i) = i;
	}

	writeToMotors(i2cFile, motorPositionArray);


}

int8_t testConnection(int8_t i2cFileTest){
	uint8_t length;
	int8_t testData[2] = {0, 0};

	*error = ioctl(i2cFileTest, I2C_SLAVE, deviceID);
	if(*error < 0){
		printf("Failed to acquire bus access and/or talk to slave\n");
		return -1;
	}

	testData[0] = 0x01;
	length = 1;

	//---- Write Bytes ----
	*error = write(i2cFileTest, testData, length);
	if(*error != length){
		printf("Write Error! :(\n");
		return -1;
	}

	//---- Read Bytes ----
	length = 1;
	*error = read(i2cFileTest, testData, length);
	if(*error != length){
		printf("Read Error! :(\n");
		return -1;
	}

	if(testData[0] == deviceID){
		printf("Device Successfully Connected! :D\n");
	}else{
		printf("Received something, however data does not match or is corrupted");
		return -1;
	}

	return 0;
}

int8_t writeToMotors(int8_t i2cFile, int8_t *positionsToWrite){
	return write(i2cFile, positionsToWrite, numberOfMotors);
};


dataPacket formatDataPacket(int8_t *dataToSend, uint8_t packetLength){
	dataPacket ret;

	if(packetLength > maxPacketLength){
		packetLength = maxPacketLength;
	}

	ret.length = packetLength;
	ret.data = (int8_t*)malloc(sizeof(int8_t) * packetLength);

	for(int i = 0; i < packetLength; i++){
		*(ret.data + i) = *(dataToSend + i);
	}

	return ret;
}
