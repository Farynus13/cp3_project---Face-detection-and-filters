#ifndef FACEFILTER_H
#define FACEFILTER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class FaceFilter {
public:
    enum FilterType {
        Glasses,
        Beard,
        Hat,
        Mask,
        Monocle
    };

private:
    int threshMax;
    int threshMin;
    cv::Mat mask;
    FilterType type;

protected:
    cv::Mat img;
    double yOffset;
    double yFactor;
    double xOffset;
    double xFactor;
    
public:
    FaceFilter(cv::Mat img, int threshMin, int threshMax, FilterType type);
    void apply(cv::Mat& frame,const cv::Rect &face);
    cv::Mat getImg() { return img; }
};

#endif  //FACEFILTER_H