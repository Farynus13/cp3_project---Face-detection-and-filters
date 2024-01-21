#include "fistFilter.h"

<<<<<<< HEAD
FistFilter::FistFilter(cv::Mat img, int threshMin, int threshMax, std::string type, std::string name): 
    BaseFilter(img, threshMin, threshMax, name)
=======
FistFilter::FistFilter(cv::Mat img, int threshMin, int threshMax, FilterType type, std::string name): 
    BaseFilter(img, threshMin, threshMax, name), type(type)
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
{
    //set the offsets and factors according to the filter type
    //values where obtained by trial and error
    if(type == "puppet")
    {
        xFactor = 2.0;
        yFactor = 2.0;
        xOffset = 0.0;
        yOffset = 0.0;
    } else if(type == "glove")
    {
        xFactor = 2;
        yFactor = 2;
        xOffset = 0;
        yOffset = 0;
    } else {
        xFactor = 1.0;
        yFactor = 1.0;
        xOffset = 0.0;
        yOffset = 0.0;
    }
}

cv::Rect FistFilter::getFilterROI(const cv::Rect& roi)
{
    return  cv::Rect(roi.x + xOffset + roi.width*(1-xFactor)/2, roi.y + yOffset + roi.height*(1-yFactor)/2,
                                roi.width*xFactor, roi.height*yFactor);
}

bool FistFilter::isOutOfFrame(const cv::Mat& frame, const cv::Rect& roi)
{
    return roi.x + xOffset + roi.width*(1-xFactor)/2 < 0 || 
            roi.y + yOffset + roi.height*(1-yFactor)/2 < 0 ||
            roi.y + yOffset + roi.height*(1-yFactor)/2 + roi.height*yFactor > frame.rows || 
            roi.x + xOffset + roi.width*(1-xFactor)/2 + roi.width*xFactor > frame.cols;
}
