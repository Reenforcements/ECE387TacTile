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
#include <iostream>

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


cv::Mat Decimator::getImage(cv::Mat src) const {
    
    // We need the original dimensions of our source image
    int srcWidth = src.size().width;
    int srcHeight = src.size().height;
    
    // The target size will be to make a square image based
    //  on the height because that's usually smaller than the width.
    int targetSize = floor(_zoomLevel * srcHeight);
    
    cv::Rect zoomRect = cv::Rect( (srcWidth / 2) - (targetSize/2), 
                (srcHeight / 2) - (targetSize/2), 
                targetSize, 
                targetSize);
    //std::cout << zoomRect << std::endl;
    
    // Crop the image so we can down sample it from there.
    // We only need one dimension since its square at this point.
    src = src(zoomRect);
    int zoomedLength = src.size().width;
    
    // Get an image using only the components we want
    // BGR for color images
    cv::Mat extracted;
    switch(_intensityOfInterest) {
        case RED:
            cv::extractChannel(src, extracted, 2);
            break;
        case BLUE:
            cv::extractChannel(src, extracted, 0);
            break; 
        case GREEN:
            cv::extractChannel(src, extracted, 1);
            break;
        case INTENSITY:
            // Do nothing
            extracted = src;
            break;
        default:
            break;
   }
    
    // Should probably factor in the standard deviation somewhere here.
    
    // Find our scale factor based on our zoomed image
    //  and how many pixels long/wide it should be.
    float pixelScaleFactor = static_cast<float>(_gridSize) / static_cast<float>(zoomedLength);
    
    cv::Mat dst;
    cv::resize(extracted, dst, cv::Size(), pixelScaleFactor, pixelScaleFactor, cv::InterpolationFlags::INTER_LANCZOS4);
    return dst;
}

void Decimator::getVisualImage(cv::Mat src, cv::Mat &dest) const {
    
}

cv::Mat Decimator::makeDemoSized(cv::Mat src, cv::Mat dst) const {
    float scaleFactor = static_cast<float>(dst.size().width) / static_cast<float>(src.size().width);
    cv::resize(src, dst, cv::Size(), scaleFactor, scaleFactor, cv::InterpolationFlags::INTER_NEAREST);
    return dst;
}

void Decimator::setZoomLevel(float level) {
    level = (level > 1.0) ? 1.0 : level;
    level = (level <= 0.0001) ? 0.05 : level;
    _zoomLevel = level;
}

void Decimator::setGridSize(unsigned int size) {
    size = (size > 720) ? 720 : size;
    size = (size <= 1) ? 1: size;
    _gridSize = size;
}

void Decimator::setDemoGridSize(unsigned int size) {
    size = (size > 720) ? 720 : size;
    size = (size <= 1) ? 1: size;
    _demoGridSize = size;
}

void Decimator::invert(bool inv) {
    _inverted = inv;
}

void Decimator::setIntensityOfInterest(IntensityOfInterest intensity) {
    _intensityOfInterest = intensity;
}