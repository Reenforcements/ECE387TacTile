#include "piComTestPiCode.h"


/*
int main(){
	int8_t mainErrorOut = 0;
	int8_t *testData = (int8_t*)malloc(sizeof(int8_t) * NUMBER_OF_MOTORS);
	char *filename = (char*)"/dev/i2c-1";

	piI2C *i2cBus = (piI2C*)malloc(sizeof(piI2C));

	mainErrorOut = initPiI2C(filename, i2cBus);

	if(mainErrorOut < 0){
		printf("I2C File and/or Peripheral failed to initialize! :(\n");
	}else{
		printf("I2C File and Peripheral successfully initialized! :D\n");
	}

	printf("====================== Testing Connection ======================\n");
	mainErrorOut = testConnection(i2cBus);

	if(mainErrorOut < 0){
		printf("Test Failed! :(\n");
	}else{
		printf("Test Passed! Device is now ready for use.\n");
	}


	for(int i = 0; i < NUMBER_OF_MOTORS; i++){
		*(testData + i) = i;
	}
	writeToMotors(i2cBus, testData);
}
 */


int8_t initPiI2C(const char *filename, piI2C *newPiI2CBus){
	int8_t *writeArray_r = (int8_t*)malloc(sizeof(int8_t) * MAX_PACKET_SIZE);
	newPiI2CBus->writeArray = writeArray_r;

	newPiI2CBus->i2cFile = open(filename, O_RDWR);
	if((newPiI2CBus->i2cFile) < 0){
		printf("Error opening I2C File\n");
		return -1;
	}

	newPiI2CBus->error = ioctl(newPiI2CBus->i2cFile, I2C_SLAVE, DEVICE_ID);
	if((newPiI2CBus->error) < 0){
		printf("Failed to acquire bus access and/or talk to slave\n");
		return -1;
	}
	return 1;
}

int8_t testConnection(piI2C *i2cBus){
	uint8_t length;
	int8_t testData[1] = {1};

	length = 1;
	i2cBus->error = write(i2cBus->i2cFile, testData, length);
	if((i2cBus->error) != length){
		printf("Write Error! :(\n");
		return -1;
	}

	length = 1;
	i2cBus->error = read(i2cBus->i2cFile, testData, length);
	if((i2cBus->error) != length){
		printf("Read Error! :(\n");
		return -1;
	}

	if(testData[0] == DEVICE_ID){
		return 1;
	}else{
		printf("Received something, however data does not match or is corrupted\n");
		return -1;
	}
	return -1;
}


int8_t writeToMotors(piI2C *i2cBus, int8_t *positionsToWrite){
	return(write(i2cBus->i2cFile, positionsToWrite, NUMBER_OF_MOTORS) ? 0 : -1);
}
