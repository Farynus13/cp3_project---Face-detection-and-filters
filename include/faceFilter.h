#ifndef FACEFILTER_H
#define FACEFILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "baseFilter.h"
#include <string>

class FaceFilter: public BaseFilter{
private:
    
    std::string type; // Type of filter
    
public:
    FaceFilter(cv::Mat img, int threshMin, int threshMax, std::string type, std::string name); // Constructor
    cv::Rect getFilterROI(const cv::Rect& filterROI) override;// Returns the filter ROI
    bool isFilterEmpty() override { return type == "empty"; } // Returns true if the filter is empty;
    bool isOutOfFrame(const cv::Mat& frame, const cv::Rect& roi) override; // Returns true if the filter is out of frame
};
#endif  //FACEFILTER_H