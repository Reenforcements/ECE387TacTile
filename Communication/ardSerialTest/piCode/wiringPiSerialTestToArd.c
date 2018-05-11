#include "wiringPiSerial.h"

uint8_t testArray[25] = {
	    5,   5,   250, 5,   5,
	    5,   250, 250, 250, 5,
	    250, 250, 250, 250, 250,
	    5,   250, 250, 250, 5,
	    5,   5,   250, 5,   5,
};

int8_t *serialFile;

int main(){
	gpioInit();

	if(initSerialFile("/dev/ttyACM0", serialFile, 9600) < 0){
		printf("%s \n", "Error Initializing Serial File:(!");
	}else{
	    printf("%s \n", "Serial file successfully initialized :D!");

	}


	while(1){
		w
	}

}
