#include "faceFilter.h"

FaceFilter::FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type): 
    BaseFilter(img, threshMin, threshMax), type(type)
{
    //set the offsets and factors
    switch(type)
    {
        case(Glasses):
            yOffset = 1.0 / 10.0;
            yFactor = 1.0 / 2.0;
            xOffset = 0;
            xFactor = 1;
            break;
        case(Beard):
            yOffset = 7 / 16.0;
            yFactor = 1.0 / 2.0;
            xOffset = 0;
            xFactor = 1;
            break;
        case(Hat):
            yOffset = -0.85;
            yFactor = 1;
            xOffset = -0.1;
            xFactor = 1.2;
            break;
        case(Mask):
            yOffset = -0.2;
            yFactor = 1.0;
            xOffset = 0;
            xFactor = 1;

            break;
        case(Monocle):
            yOffset = 2.2 / 10.0;
            yFactor = 1.0 / 2.0;
            xOffset = 0;
            xFactor = 1.0 / 2.0;
            break;
        default:
            yOffset = 1.0;
            yFactor = 1.0 / 2.0;
            xOffset = 0;
            xFactor = 1;
            break;
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
