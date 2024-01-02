#include "faceFilter.h"

FaceFilter::FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type)
{
    //set the values
    this->img = img.clone();
    this->yOffset = yOffset;
    this->type = type;
    this->threshMin = threshMin;
    this->threshMax = threshMax;

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

    //create mask
    threshold(img, mask,threshMin, threshMax, cv::THRESH_BINARY_INV);
}


void FaceFilter::apply(cv::Mat& frame,const cv::Rect &face)
{    
    //check if the filter is an empty filter
   if(type == Empty)
   {
         return;
   }
   else {
        cv::Mat _img,_mask;     
        //create a copy of the mask and img to work on
        _img = img.clone();
        _mask = mask.clone();

        //resize the mask and img to fit the face
        cv::resize(_mask, _mask, cv::Size(face.width*xFactor, face.height*yFactor));
        cv::resize(_img, _img, cv::Size(face.width*xFactor, face.height*yFactor));

        int yDiff = 0;
        int xDiff = 0;

        //check if the filter is out of bounds
        if(face.y + face.height*yOffset < 0)
        {
            //cut the filter to fit the frame in y direction
            yDiff = -(face.y + face.height*yOffset);
        }

        if(face.x + face.width*xOffset < 0)
        {
            //cut the filter to fit the frame in x direction
            xDiff = -(face.x + face.width*xOffset);
        }

        //cut the mask  and img to fit the frame
        _mask = _mask(cv::Rect(0,yDiff,face.width*xFactor,face.height*yFactor-yDiff));
        _img = _img(cv::Rect(0,yDiff,face.width*xFactor,face.height*yFactor-yDiff));

        //copy the filter to the frame at the right position
        cv::Mat imgROI = frame(cv::Rect(face.x + face.width*xOffset+xDiff, face.y + face.height*yOffset+yDiff,
                                face.width*xFactor-xDiff, face.height*yFactor-yDiff));
        _img.copyTo(imgROI, _mask);
   }
}