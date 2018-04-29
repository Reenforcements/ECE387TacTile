/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Decimator.cpp
 * Author: imaustyn
 * 
 * Created on April 27, 2018, 8:51 PM
 */

#include "Decimator.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <cmath>

Decimator::Decimator(): _inverted(false), 
                        _gridSize(5), 
                        _demoGridSize(20), 
                        _zoomLevel(1.0),
                        _intensityOfInterest(INTENSITY) 
{
    
}

Decimator::Decimator(const Decimator& orig): _inverted(orig._inverted), 
                                            _gridSize(orig._gridSize), 
                                            _demoGridSize(orig._demoGridSize), 
                                            _zoomLevel(orig._zoomLevel),
                                            _intensityOfInterest(orig._intensityOfInterest) 
{
    
}

Decimator::~Decimator() {
    
}


void Decimator::getImage(cv::Mat src, const cv::Mat &dest) const {
    
    int srcWidth = src.size().width;
    int srcHeight = src.size().height;
    
    // The target size will be to make a square image based
    //  on the height because that's usually smaller than the width.
    float targetSize = floor(_zoomLevel * srcHeight);
    
    cv::Rect zoomRect = cv::Rect( (srcWidth / 2) - (targetSize/2), 
                (srcHeight / 2) - (targetSize/2), 
                targetSize, 
                targetSize);
    
    // Crop the image so we can down sample it from there.
    src = src(zoomRect);
    int zoomedWidth = src.size().width;
    int zoomedHeight = src.size().height;
    
    //resize(src, dst, Size(), factor, factor, InterpolationFlags::INTER_LANCZOS4);
}

void Decimator::getVisualImage(cv::Mat src, cv::Mat &dest) const {
    
}

void Decimator::setZoomLevel(float level) {
    _zoomLevel = level;
}

void Decimator::setGridSize(unsigned int size) {
    _gridSize = size;
}

void Decimator::setDemoGridSize(unsigned int size) {
    _demoGridSize = size;
}

void Decimator::invert(bool inv) {
    _inverted = inv;
}

void Decimator::setIntensityOfInterest(IntensityOfInterest intensity) {
    _intensityOfInterest = intensity;
}