#ifndef FACEFILTER_H
#define FACEFILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class FaceFilter {
public:
    enum FilterType {
        Eyes,
        Mouth,
        Hat,
        Nose
    };

private:

    int threshMax;
    int threshMin;
    FilterType type;

protected:
    cv::Mat img;
    cv::Mat mask;
    double yOffset;
    
public:
    FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type);
    void apply(cv::Mat& frame,const cv::Rect &face);

};

#endif  //FACEFILTER_H