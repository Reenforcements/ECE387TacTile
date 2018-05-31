/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: imaustyn
 *
 * Created on April 27, 2018, 8:51 PM
 */


#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <unistd.h>
#include "Decimator.hpp"

extern "C" {
#include "Communication/wiringPiSerial.h"
#include "GPIO/gpioPi.h"
}

using namespace std;
using namespace cv;

float zoomLevel = 1.0;
Decimator::IntensityOfInterest intensityOfInterest = Decimator::INTENSITY;

uint8_t testStar[25] 
        = {
    5,   5,   250, 5,   5,
    5,   250, 250, 250, 5,
    250, 250, 250, 250, 250,
    5,   250, 250, 250, 5,
    5,   5,   250, 5,   5,
};

int8_t *serialFile;

unsigned int waiter = 0;
int main(int argc, char** argv) {
    
    // Init GPIO
    gpioInit();
    
    if(initSerialFile("/dev/ttyACM0", serialFile, 9600) < 0){
    	printf("%s \n", "Error Initializing Serial File:(!");
    }else{
    	printf("%s \n", "Serial file successfully initialized :D!");

    }
    
    Decimator decimator;
    decimator.setGridSize(5);
    unsigned int demoSize = 5;
    decimator.setDemoGridSize(demoSize);
    
    VideoCapture cap(0);
    if(cap.isOpened() == false) {
        std::cout << "Couldn't open camera." << std::endl;
        runtime_error("Couldn't open camera!");
        return 0;
    }
    
    // Display the output
    namedWindow("decimatorTest");
        
    while(true) {
        
        Mat input;
        cap >> input;
        
        int key = waitKey(10);
        switch(key) {
            case '-':
                zoomLevel += 0.05;
                zoomLevel = (zoomLevel > 1.0) ? 1.0 : zoomLevel;
                decimator.setZoomLevel(zoomLevel);
                break;
            case '+':
                zoomLevel -= 0.05;
                zoomLevel = (zoomLevel <= 0.0001) ? 0.05 : zoomLevel;
                decimator.setZoomLevel(zoomLevel);
                break;
            case '[':
                demoSize = (demoSize <= 2) ? 2 : demoSize;
                demoSize--;
                decimator.setDemoGridSize(demoSize);
                break;
            case ']':
                demoSize = (demoSize >= 720) ? 720 : demoSize;
                demoSize++;
                decimator.setDemoGridSize(demoSize);
                break;
            case 'r':
                intensityOfInterest = Decimator::RED;
                break;
            case 'g':
                intensityOfInterest = Decimator::GREEN;
                break;
            case 'b':
                intensityOfInterest = Decimator::BLUE;
                break;
            case 'i':
                intensityOfInterest = Decimator::INTENSITY;
                break;
            
            case 'k':
            case 'q':
                goto exit;
                
            default:
                break;
        }
        
        decimator.setIntensityOfInterest(intensityOfInterest);
        decimator.setZoomLevel(zoomLevel);
        
        /*
        std::cout 
                << "Demo size: " 
                << demoSize 
                << " Zoom: "
                << zoomLevel
                << std::endl;
        */
        // Get the image result to send to the Arduino
        Mat result = decimator.getServoImage(input.clone());
        
        waiter++;
        if(waiter > 10) {
            waiter = 0;
            if(result.isContinuous()) {
                // Write the data to the Arduino
                assert(result.total() * result.elemSize() == 25);
                std::cout << "(" << time(0) << ") Writing " << ( result.total() * result.elemSize() ) << " bytes." << std::endl;
                
                
                
                for (unsigned char x = 0; x < 5; x++) {
                    for (unsigned char y = 0; y < 5; y++) {
                        unsigned int current = (unsigned int) result.data[x*5 + y];
                        std::cout << current;
                        if(current < 100) {
                            std::cout << " ";
                        }
                        if(current < 10) {
                            std::cout << " ";
                        }
                        // Always at least one digit
                        std::cout << " ";
                    }
                    std::cout << std::endl;
                }
                
                writeArray(result.data);
                
//                int8_t error = writeToMotors(&connection, reinterpret_cast<int8_t*>(result.data));
//                if(error == -1) {
//                    std::cout << "Error writing to Arduino!" << std::endl;
//                }
            } else {
                std::cout << "Error, result not continuous!" << std::endl;
            }
        }
        
        
        input = decimator.getDemoImage(input);
        imshow("decimatorTest", input);
    }
    exit:
                
                
        return 0;
}

void zoomInPressed(void) {
    // Not a great way to debounce but we're short on time.
    bool state1 = digitalRead(BUTTON_0);
    usleep(10000);
    bool state2 = digitalRead(BUTTON_0);
    if(!state1 && !state2) {
        std::cout << "Zoom in pressed!" << std::endl;
        zoomLevel -= 0.05;
        zoomLevel = (zoomLevel <= 0.0001) ? 0.05 : zoomLevel;
    }
}
void zoomOutPressed(void) {
    bool state1 = digitalRead(BUTTON_1);
    usleep(10000);
    bool state2 = digitalRead(BUTTON_1);
    if(!state1 && !state2) {
        std::cout << "Zoom out pressed!" << std::endl;
        zoomLevel += 0.05;
        zoomLevel = (zoomLevel > 1.0) ? 1.0 : zoomLevel;
    }
    
}
void ledButtonPressed(void) {
    
}
