#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <stdio.h>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened()) // check if we succeeded
        return -1;
    
    Mat src;
    namedWindow("circles",WINDOW_NORMAL);
    resizeWindow("circles", 700, 700);
    
    float factor = 0.1;//0.00694;
    std::cout << "Factor :" << factor << std::endl;
    std::cout << cap.get(CV_CAP_PROP_FORMAT) << std::endl;
    
    float capWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    float capHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    
    while (true) {
        // Check if image is loaded fine
        cap >> src;
        
        Mat dst;
        Mat dst2;
        
        float zoomLevel = 0.08;
        
        float sideLength = capHeight * zoomLevel;
        Rect zoomRect = Rect( (capWidth / 2) - (sideLength/2), 
                (capHeight / 2) - (sideLength/2), 
                sideLength, 
                sideLength);
        std::cout << "Zoom rect: " << zoomRect << std::endl;
        src = src(Rect( (capWidth / 2) - (sideLength/2), 
                (capHeight / 2) - (sideLength/2), 
                sideLength, 
                sideLength));
        
        resize(src, dst, Size(), factor, factor, InterpolationFlags::INTER_LANCZOS4);
        // Get average BRG
        
        Scalar avgColors = mean(dst);
        if(avgColors[0] > avgColors[1] && avgColors[0] > avgColors[2]) {
            std::cout << "Blue" << std::endl;
        }
        if(avgColors[1] > avgColors[0] && avgColors[1] > avgColors[2]) {
            std::cout << "Green" << std::endl;
        }
        if(avgColors[2] > avgColors[1] && avgColors[2] > avgColors[0]) {
            std::cout << "Red" << std::endl;
        }
        
        std::cout << "Mean: " << mean(dst) << std::endl;
        resize(dst, dst2, Size(), 1/(factor * zoomLevel), 1/(factor * zoomLevel), InterpolationFlags::INTER_NEAREST);
        
        imshow("circles", dst2);
        if(waitKey(20) >= 0) break;
        //std::cout << "zop" << std::endl;
    }
    return 0;
}