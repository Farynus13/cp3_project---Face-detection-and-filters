#include "faceFilter.h"

<<<<<<< HEAD
FaceFilter::FaceFilter(cv::Mat img, int threshMin, int threshMax, std::string type, std::string name):
    BaseFilter(img, threshMin, threshMax, name)
=======
FaceFilter::FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type, std::string name):
    BaseFilter(img, threshMin, threshMax, name), type(type)
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
{
    //set the offsets and factors according to the filter type
    //values where obtained by trial and error
    if(type == "glasses")
    {
        yOffset = 1.0 / 10.0;
        yFactor = 1.0 / 2.0;
        xOffset = 0;
        xFactor = 1;
    } else if(type == "beard")
    {
        yOffset = 7 / 16.0;
        yFactor = 1.0 / 2.0;
        xOffset = 0;
        xFactor = 1;
    } else if(type == "hat")
    {
        yOffset = -0.85;
        yFactor = 1;
        xOffset = -0.1;
        xFactor = 1.2;
    } else if(type == "mask")
    {
        yOffset = -0.25;
        yFactor = 1.5;
        xOffset = -0.75;
        xFactor = 2.5;
    } else if(type == "monocle")
    {
        yOffset = 2.2 / 10.0;
        yFactor = 1.0 / 2.0;
        xOffset = 0;
        xFactor = 1.0 / 2.0;
    } else {
        yOffset = 1.0;
        yFactor = 1.0 / 2.0;
        xOffset = 0;
        xFactor = 1;
    }    
}

cv::Rect FaceFilter::getFilterROI(const cv::Rect& roi)
{
    return  cv::Rect(roi.x + roi.width*xOffset, roi.y + roi.height*yOffset,
                        roi.width*xFactor, roi.height*yFactor);
}

bool FaceFilter::isOutOfFrame(const cv::Mat& frame, const cv::Rect& roi)
{
    return roi.y + roi.height*yOffset < 0 || roi.x + roi.width*xOffset < 0 ||
        roi.y + roi.height*(yOffset + yFactor) > frame.rows || roi.x + roi.width*(xFactor + xOffset) > frame.cols;
}
