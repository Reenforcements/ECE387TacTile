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
#include <algorithm>
#include "Decimator.hpp"


using namespace std;
using namespace cv;

/*
 * 
 */
int main(int argc, char** argv) {

    // Display the output
    namedWindow("decimatorTest", WINDOW_NORMAL);
    
    Decimator decimator;
    VideoCapture cap(0);
    if(cap.isOpened() == false) {
        runtime_error("Couldn't open camera!");
        return 0;
    }
    float zoomLevel = 1.0;
    unsigned int demoSize = 15;
    
    while(true) {
        
        Mat input;
        cap >> input;
        
        imshow("decimatorTest", input);
        
        int key = waitKey(10);
        switch(key) {
            case '+':
                zoomLevel += 0.05;
                zoomLevel = (zoomLevel > 1.0) ? 1.0 : zoomLevel;
                break;
            case '-':
                zoomLevel -= 0.05;
                zoomLevel = (zoomLevel < 0.0) ? 0.0 : zoomLevel;
                break;
            case '[':
                demoSize = (demoSize == 1) ? 1 : demoSize;
                demoSize--;
                break;
            case ']':
                demoSize = (demoSize >= 720) ? 720 : demoSize;
                demoSize++;
                break;
            
            case 'k':
            case 'q':
                goto exit;
                
            default:
                break;
        }
        
        
    }
    exit:
    
    return 0;
}

