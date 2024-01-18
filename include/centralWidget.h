#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "filterSet.h"
#include "faceFilter.h"
#include "fistFilter.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
    cv::CascadeClassifier cascade;
    cv::CascadeClassifier fistCascade;
    cv::CascadeClassifier handCascade;
    cv::CascadeClassifier palmCascade;
    FilterSet glassesSet;
    FilterSet beardSet;
    FilterSet hatSet;
    FilterSet maskSet;
    FilterSet monocleSet;
    FilterSet gloveSet;
    FilterSet puppetSet;
public:
    CentralWidget(QWidget *parent = nullptr);
private:
    cv::Mat detectAndDraw(cv::Mat& img);
    void readCamera(QLabel *label,cv::VideoCapture capture);
    void chooseEyes(std::vector<cv::Rect> &eyes, cv::Mat& faceROI);
    void updateFilterLabel(QLabel *label, FilterSet *filterSet);

};

#endif // CENTRALWIDGET_H
