#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <vector>
#include <string>
#include <QWidget>
#include <QVBoxLayout>
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
#include <QDir>

class CentralWidget : public QWidget
{
    Q_OBJECT
    QGridLayout* layout;
    QLabel* cameraLabel;
    std::vector<std::string> filterNames;
    //opencv variables
    cv::CascadeClassifier cascade;
    cv::CascadeClassifier fistCascade;
    cv::VideoCapture capture;
    
    //map of Carousel<BaseFilter>
    std::map<std::string,Carousel<BaseFilter>*> filterCarouselMap;
    Carousel<FilterSet>* filterSetCarousel;
public:
    CentralWidget(QWidget *parent = nullptr); //constructor with logic for buttons and whole program
private:
    cv::Mat detectAndDraw(cv::Mat& img); //detects faces and fists and draws filters
    void readCamera(QLabel *label); //reads camera and displays it on label
    void loadFilters(); //loads filters from filters folder
    void createLayout(); //creates the layout of the central widget
    void createSets();
};

#endif // CENTRALWIDGET_H
