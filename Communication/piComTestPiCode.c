#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int i2cFile;
int8_t *error;
const uint8_t deviceID = 0x04;
const uint8_t maxPacketLength = 32;

int8_t testConnection(int i2cFileTest);

typedef struct{
	uint8_t length;
	int8_t *data;
} dataPacket;


int main(){
	error = (int8_t*)malloc(sizeof(int8_t));

	char *filename = (char*)"/dev/i2c-1";

	i2cFile = open(filename, O_RDWR);
	if(i2cFile < 0){
		printf("Error opening I2C File\n");
		return -1;
	}

	*error = testConnection(i2cFile);
	if(*error == 0){
		return 0;
	}else{
		return -1;
	}

}

int8_t testConnection(int i2cFileTest){
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
