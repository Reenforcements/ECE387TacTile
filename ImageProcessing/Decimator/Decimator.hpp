/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Decimator.hpp
 * Author: imaustyn
 *
 * Created on April 27, 2018, 8:51 PM
 */

#ifndef DECIMATOR_HPP
#define DECIMATOR_HPP

#include <opencv2/opencv.hpp>

class Decimator {
public:
    Decimator();
    Decimator(const Decimator& orig);
    virtual ~Decimator();
    
    // Retrieve the image used to move the pins
    void getImage(cv::Mat src, cv::Mat &dest) const;
    // Retrieve the image used for the grid
    void getVisualImage(cv::Mat src, cv::Mat &dest) const;
    
    // Sets how small of a portion of the captured frame we're using
    // 0 - Use the maximum resolution
    // 1 - Zoom in so far that we're only left with the grid size.
    void setZoomLevel(float level);
        
    // Set the size of the grid of "tactile"
    void setGridSize(unsigned int size);
    // Set the dimensions of the visual grid of pixels that show
    /// what the tactile would be doing if there were that many.
    void setDemoGridSize(unsigned int size);
    
    // Invert the chosen color intensity.
    void invert(bool inv);
    
    enum IntensityOfInterest {
        INTENSITY,
        RED,
        GREEN,
        BLUE
    };
    // Set which intensity of interest to use when determining tactile heights
    void setIntensityOfInterest(IntensityOfInterest intensity);
    
private:
    bool _inverted;
    float _zoomLevel;
    unsigned int _gridSize;
    unsigned int _demoGridSize;
    IntensityOfInterest _intensityOfInterest;
    
};

#endif /* DECIMATOR_HPP */

