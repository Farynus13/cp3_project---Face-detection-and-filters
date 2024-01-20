#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "updateLabelInterface.h"
#include <QLabel>
class BaseFilter: public UpdateLabelInterface{
public:
protected:
    // Threshold values
    int threshMax;
    int threshMin;

    // Image for filter
    cv::Mat img;
    // Offsets and factors for filter placement
    double yOffset;
    double yFactor;
    double xOffset;
    double xFactor;
    // Name of the filter
    std::string name;

public:
    BaseFilter(cv::Mat img, int threshMin, int threshMax, std::string name): 
        img(img.clone()), threshMin(threshMin), threshMax(threshMax), name(name) {} // Constructor
    void apply(cv::Mat& frame, const cv::Rect& roi); // Applies the filter to the frame
    virtual cv::Rect getFilterROI(const cv::Rect& filterROI) = 0; // Returns the filter ROI
    virtual bool isFilterEmpty() = 0; // Returns true if the filter is empty
    virtual bool isOutOfFrame(const cv::Mat& frame, const cv::Rect& roi) = 0; // Returns true if the filter is out of frame
    cv::Mat getImg() { return img; } // Returns the filter image
    void update(QLabel *label) override; // Updates the label with the filter image
    std::string getName() const { return name; } // Returns the name of the filter
    virtual ~BaseFilter() = default;

};

#endif  // IMAGEFILTER_H
