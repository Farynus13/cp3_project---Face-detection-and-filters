#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <qgridlayout.h>
#include "mainWindow.h"
#include "centralWidget.h"

using namespace cv;
using namespace std;



int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    return app.exec();
}


