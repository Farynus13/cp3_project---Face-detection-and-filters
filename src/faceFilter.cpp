#include "faceFilter.h"

FaceFilter::FaceFilter(cv::Mat img, int threshMin, int threshMax, double yOffset)
    {
        this->img = img;
        this->threshMin = threshMin;
        this->threshMax = threshMax;
        this->yOffset = yOffset;

        threshold(img, mask,threshMin, threshMax, cv::THRESH_BINARY_INV);
    }


void FaceFilter::apply(cv::Mat& frame,const cv::Rect &face)
{

    cv::Mat t_img,t_mask;     
    cv::resize(mask, t_mask, cv::Size(face.width, face.height/2));
    cv::resize(img, t_img, cv::Size(face.width, face.height/2));
    //copyto with mask
    cv::Mat imgROI = frame(cv::Rect(face.x, face.y + face.height*yOffset , face.width, face.height/2));
    t_img.copyTo(imgROI, t_mask);
}