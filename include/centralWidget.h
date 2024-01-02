#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "filterSet.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
    cv::CascadeClassifier cascade, eyesCascade,mouthCascade,noseCascade;
    double scale = 1;
    FilterSet glassesSet;
    FilterSet beardSet;
    FilterSet hatSet;
    FilterSet maskSet;
    FilterSet monocleSet;
public:
    CentralWidget(QWidget *parent = nullptr);
private:
    cv::Mat detectAndDraw(cv::Mat& img, cv::CascadeClassifier& cascade, cv::CascadeClassifier& eyesCascade,
     cv::CascadeClassifier& mouthCascade, cv::CascadeClassifier& noseCascade,double scale);
    void readCamera(QLabel *label,cv::VideoCapture capture);
    void chooseEyes(std::vector<cv::Rect> &eyes, cv::Mat& faceROI);

};

#endif // CENTRALWIDGET_H
