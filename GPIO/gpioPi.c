#include "gpioPi.h"

int8_t prevStateButton0;  //Used in debouncer 0
int8_t curStateButton0;  //Used in debouncer 0
int8_t prevStateButton1;  //Used in debouncer 1
int8_t curStateButton1;  //Used in debouncer 1
int8_t prevStateButton2;  //Used in debouncer 2
int8_t curStateButton2;  //Used in debouncer 2
int8_t ledLighting;

#ifdef USE_LED_TEST
	int8_t ledState = 0;
#endif



int main(){
	prevStateButton0 = 1;
	curStateButton0 = 0;
	prevStateButton1 = 1;
	curStateButton1 = 0;
	prevStateButton2 = 1;
	curStateButton2 = 0;
	ledLighting = 0;

	gpioInit();


	#ifdef USE_LED_TEST
		while(1){
			printf("%d\n", ledState);
			delay(1000);
		}
	#endif

	while(1){
		printf("%s %d\n", "LED state: ", ledLighting);

		delay(3000);
	}
}


int8_t gpioInit(){

	//wiringPi default setup
	wiringPiSetup();

	//Enable input on wiringPi 0 (BCM 17), wiringPi 1 (BCM 18), wiringPi 3 (BCM 22)
	pinMode(BUTTON_0, INPUT);
	pullUpDnControl(BUTTON_0, PUD_UP);
	pinMode(BUTTON_1, INPUT);
	pullUpDnControl(BUTTON_1, PUD_UP);
	pinMode(BUTTON_2, INPUT);
	pullUpDnControl(BUTTON_2, PUD_UP);

	//Set output on wiringPi 4 (BCM 23)
	pinMode(LED_PIN, OUTPUT);

	/* Calls the wiringPiISR (interrupt service Register) to set what gets called and when
	*  In this case the function zoomInPressed gets called when a falling edge interrupt is detected on button 0
	*/
	if(wiringPiISR(BUTTON_0, INT_EDGE_FALLING , &zoomInPressed) < 0){
		fprintf(stderr, "Unable to setup ISR 1: %s\n", strerror(errno));
		return -1;
	}else{
		printf("%s\n", "ISR 1 was setup correctly! :D");
	}

	/*
	*  In this case the function zoomOutPressed gets called when a falling edge interrupt is detected on button 1
	*/
	if(wiringPiISR(BUTTON_1, INT_EDGE_FALLING , &zoomOutPressed) < 0){
		fprintf(stderr, "Unable to setup ISR 2: %s\n", strerror(errno));
		return -1;
	}else{
		printf("%s\n", "ISR 2 was setup correctly! :D");
	}
	/*
	*  In this case the function ledButtonPressed gets called when a falling edge interrupt is detected on button 2
	*/
	if(wiringPiISR(BUTTON_2, INT_EDGE_FALLING , &ledButtonPressed) < 0){
		fprintf(stderr, "Unable to setup ISR 3: %s\n", strerror(errno));
		return -1;
	}else{
		printf("%s\n", "ISR 3 was setup correctly! :D");
	}

	return 0;
}


void zoomInPressed(){

	//Debouncer 0
	for(uint8_t i = 0; i < TIMEOUT; i++){
		curStateButton0 = digitalRead(BUTTON_0);
		if(curStateButton0 != prevStateButton0){
			continue;
		}else{
			return;
		}
	}

	 //Call whatever Zoom in function here

	#ifdef USE_LED_TEST
		ledState = !ledState;
		digitalWrite(1, ledState);
	#endif

	return;
}

void zoomOutPressed(){

	//Debouncer 1
	for(uint8_t j = 0; j < TIMEOUT; j++){
		curStateButton1 = digitalRead(BUTTON_1);
		if(curStateButton1 != prevStateButton1){
			continue;
		}else{
			return;
		}
	}

	 //Call whatever Zoom out function here

	return;
}

void ledButtonPressed(){

	//Debouncer 2
	for(uint8_t k = 0; k < TIMEOUT; k++){
		curStateButton2 = digitalRead(BUTTON_2);
		if(curStateButton2 != prevStateButton2){
			continue;
		}else{
			return;
		}
	}

	//Toggle the LED lighting state
	ledLighting = !ledLighting;

	//Write the new state to the LED PIN
	digitalWrite(LED_PIN, ledLighting);

	return;
}
