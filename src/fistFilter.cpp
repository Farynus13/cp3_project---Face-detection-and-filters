#include "fistFilter.h"

FistFilter::FistFilter(cv::Mat img, int threshMin, int threshMax, FilterType type, std::string name): 
    BaseFilter(img, threshMin, threshMax, name), type(type)
{
    //set the offsets and factors
    switch(type)
    {
        case Puppet:
            xFactor = 2.0;
            yFactor = 2.0;
            xOffset = 0.0;
            yOffset = 0.0;
            break;
        case Glove:
            xFactor = 2;
            yFactor = 2;
            xOffset = 0;
            yOffset = 0;
            break;
        case Big:
            xFactor = 1.5;
            yFactor = 1.5;
            xOffset = 0.2;
            yOffset = 0.2;
            break;
        case Normall:
            xFactor = 1.0;
            yFactor = 1.0;
            xOffset = 0.0;
            yOffset = 0.0;
            break;
        case Small:
            xFactor = 0.5;
            yFactor = 0.5;
            xOffset = 0.0;
            yOffset = 0.0;
            break;
        case Empty:
            xFactor = 1.0;
            yFactor = 1.0;
            xOffset = 0.0;
            yOffset = 0.0;
            break;
        default:
            xFactor = 1.0;
            yFactor = 1.0;
            xOffset = 0.0;
            yOffset = 0.0;
            break;
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
