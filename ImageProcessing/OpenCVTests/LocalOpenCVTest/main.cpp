/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: imaustyn
 *
 * Created on April 25, 2018, 7:16 PM
 */

#include <iostream>
#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
/*
 * 
 */
int main(int argc, char** argv) {
    
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be de-initialized automatically in VideoCapture destructor
    return 0;
}

