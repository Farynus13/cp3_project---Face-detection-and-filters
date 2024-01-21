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
<<<<<<< HEAD
#include <QDir>
=======
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61

class CentralWidget : public QWidget
{
    Q_OBJECT
    QGridLayout* layout;
    QLabel* cameraLabel;
    std::vector<std::string> filterNames;
    //opencv variables
    cv::CascadeClassifier cascade;
    cv::CascadeClassifier fistCascade;
<<<<<<< HEAD
    cv::VideoCapture capture;
    
    //map of Carousel<BaseFilter>
    std::map<std::string,Carousel<BaseFilter>*> filterCarouselMap;
    Carousel<FilterSet>* filterSetCarousel;
=======
    Carousel<BaseFilter> glassesCarousel;
    Carousel<BaseFilter> beardCarousel;
    Carousel<BaseFilter> hatCarousel;
    Carousel<BaseFilter> maskCarousel;
    Carousel<BaseFilter> monocleCarousel;
    Carousel<BaseFilter> gloveCarousel;
    Carousel<BaseFilter> puppetCarousel;
    Carousel<FilterSet> filterSetCarousel;
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
public:
    CentralWidget(QWidget *parent = nullptr); //constructor with logic for buttons and whole program
private:
<<<<<<< HEAD
    cv::Mat detectAndDraw(cv::Mat& img); //detects faces and fists and draws filters
    void readCamera(); //reads camera and displays it on label
    void loadFilters(); //loads filters from filters folder
    void createLayout(); //creates the layout of the central widget
    void createSets();
=======
    cv::Mat detectAndDraw(cv::Mat& img);
    void readCamera(QLabel *label,cv::VideoCapture capture);
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
};

#endif // CENTRALWIDGET_H
