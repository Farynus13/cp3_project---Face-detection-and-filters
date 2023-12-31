#include "faceFilter.h"

FaceFilter::FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type)
    {
        this->img = img;
        this->threshMin = threshMin;
        this->threshMax = threshMax;
        this->yOffset = yOffset;
        this->type = type;

        switch(type)
        {
            case(Eyes):
                yOffset = 1.0 / 10.0;
                break;
            case(Mouth):
                yOffset = 7.5 / 16.0;
                break;
            case(Hat):
                yOffset = -0.5;
                break;
            case(Nose):
                yOffset = 3 / 8.0;
                break;
            default:
                yOffset = 1.0;
                break;
        }
        threshold(img, mask,threshMin, threshMax, cv::THRESH_BINARY_INV);
    }


void FaceFilter::apply(cv::Mat& frame,const cv::Rect &face)
{    
    cv::Mat _img,_mask;     
    //copy img to _img and mask to _mask
    _img = img.clone();
    _mask = mask.clone();

    cv::resize(_mask, _mask, cv::Size(face.width, face.height/2));
    cv::resize(_img, _img, cv::Size(face.width, face.height/2));
    int diff = 0;
    //check if the filter is out of bounds
    if(type == Hat)
    {
        if(face.y + face.height*yOffset < 0)
        {
            //cut the filter to fit the frame
            diff = -(face.y + face.height*yOffset);
            //cut the mask  and img to fit the frame
            _mask = _mask(cv::Rect(0,diff,face.width,face.height/2-diff));
            _img = _img(cv::Rect(0,diff,face.width,face.height/2-diff));
        }
    }

    //copyto with mask
    cv::Mat imgROI = frame(cv::Rect(face.x, face.y + face.height*yOffset+diff , face.width, face.height/2-diff));
    _img.copyTo(imgROI, _mask);
}