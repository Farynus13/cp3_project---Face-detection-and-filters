#include "baseFilter.h"

void BaseFilter::apply(cv::Mat& frame,const cv::Rect &roi)
{    
    //check if the filter is an empty filter
    //check if the filter is out of bounds
    if(isFilterEmpty() || isOutOfFrame(frame, roi))
    {
            return;
    }
    else {
        cv::Mat gray, mask, smallImg;

        //resize the mask and img to fit the face
        cv::resize(img, smallImg, cv::Size(roi.width*xFactor, roi.height*yFactor));

        //copy the filter to the frame at the right position
        cv::Mat imgROI = frame(getFilterROI(roi));

        //create mask
        cv::Mat bg, mask_inv, fg, dst;
        cv::cvtColor(smallImg, gray, cv::COLOR_RGB2GRAY);
        threshold(gray, mask,threshMin, threshMax, cv::THRESH_BINARY);
        cv::bitwise_or(imgROI, imgROI, bg, mask);
        cv::bitwise_not(mask, mask_inv);
        cv::bitwise_and(smallImg, smallImg, fg, mask_inv);
        //combine the mask and the image
        cv::add(bg, fg, dst);
        //copy the image to the frame
        dst.copyTo(imgROI);
   }
}