#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <errno.h>

/* Uncomment for an LED Test*/
//#define USE_LED_TEST


#define TIMEOUT 2 //Timeout for debouncer
#define BUTTON_0 0
#define BUTTON_1 1
#define BUTTON_2 3
#define LED_PIN  4

int8_t gpioInit(void);
void zoomInPressed(void);
void zoomOutPressed(void);
void ledButtonPressed(void);
