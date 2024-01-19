#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "carousel.h"
#include "faceFilter.h"
#include "fistFilter.h"
#include "filterSet.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
    cv::CascadeClassifier cascade;
    cv::CascadeClassifier fistCascade;
    Carousel<BaseFilter> glassesCarousel;
    Carousel<BaseFilter> beardCarousel;
    Carousel<BaseFilter> hatCarousel;
    Carousel<BaseFilter> maskCarousel;
    Carousel<BaseFilter> monocleCarousel;
    Carousel<BaseFilter> gloveCarousel;
    Carousel<BaseFilter> puppetCarousel;
    Carousel<FilterSet> filterSetCarousel;
public:
    CentralWidget(QWidget *parent = nullptr);
private:
    cv::Mat detectAndDraw(cv::Mat& img);
    void readCamera(QLabel *label,cv::VideoCapture capture);
};

#endif // CENTRALWIDGET_H
