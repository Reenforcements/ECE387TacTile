#include "gpioPi.h"

int8_t prevState = 1;
int8_t curState = 0;

#ifdef USE_LED
	int8_t ledState = 0;
#endif


void buttonPressed(void);

int main(){
	wiringPiSetup();
	pinMode(0, INPUT);
	pinMode(1, OUTPUT);
	pullUpDnControl(0, PUD_UP);

	if(wiringPiISR(0, INT_EDGE_FALLING , &buttonPressed) < 0){
		fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
		return -1;
	}else{
		printf("%s\n", "ISR was setup correctly! :D");
	}

	#ifdef USE_LED
		while(1){
			printf("%d\n", ledState);
			delay(1000);
		}
	#endif
}


void buttonPressed(){

	//Debouncer
	for(uint8_t i = 0; i < timeout; i++){
		curState = digitalRead(0);
		if(curState != prevState){
			continue;
		}else{
			return;
		}
		return;
	}

	 //Call to whatever Zoom function

	#ifdef USE_LED
		ledState = !ledState;
		digitalWrite(1, ledState);
	#endif

	return;
}

