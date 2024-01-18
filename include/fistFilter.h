#ifndef FISTFILTER_H
#define FISTFILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "baseFilter.h"

class FistFilter: public BaseFilter{
public:
    // Enumerated type for the different filters
    enum FilterType {
        Glove,
        Puppet,
        Big,
        Normall,
        Small,
        Empty
    };

private:
    FilterType type; // Type of filter

public:
    FistFilter(cv::Mat img, int threshMin, int threshMax, FilterType type); // Constructor
    cv::Rect getFilterROI(const cv::Rect& filterROI) override;// Returns the filter ROI
    bool isFilterEmpty() override { return type == Empty; } // Returns true if the filter is empty
    bool isOutOfFrame(const cv::Mat& frame, const cv::Rect& roi) override; // Returns true if the filter is out of frame
};

#endif  //FISTFILTER_H
