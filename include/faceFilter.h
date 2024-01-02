#ifndef FACEFILTER_H
#define FACEFILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class FaceFilter {
public:
// Enumerated type for the different filters
    enum FilterType {
        Glasses,
        Beard,
        Hat,
        Mask,
        Monocle,
        Empty
    };

private:
    //threshold values
    int threshMax;
    int threshMin;

    cv::Mat mask; // Mask for the filter
    FilterType type; // Type of filter

protected:
    //image for filter
    cv::Mat img;
    //offsets and factors for filter placement
    double yOffset;
    double yFactor;
    double xOffset;
    double xFactor;
    
public:
    FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type); // Constructor
    void apply(cv::Mat& frame,const cv::Rect &face); // Applies the filter to the frame
    cv::Mat getImg() { return img; } // Returns the filter image
};

#endif  //FACEFILTER_H