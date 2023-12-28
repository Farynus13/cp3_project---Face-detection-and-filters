#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <Windows.h>

#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QTimer>

using namespace cv;
using namespace std;

Mat detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale);


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMainWindow window;
    QLabel* videoLabel = new QLabel(&window);
    window.setCentralWidget(videoLabel);
    window.show();

    VideoCapture capture(0); // Open the default camera
    if (!capture.isOpened())
    {
        qDebug() << "Failed to open camera!";
        return -1;
    }

    Mat frame, img;
    
    CascadeClassifier cascade, nestedCascade;
    double scale = 1;

    //load the cascade classifier object
    cascade.load("haarcascade_frontalface_alt.xml");

    //check if the cascade classifier object is empty
    if (cascade.empty())
    {
        //print an error message
        cerr << "ERROR: Could not load classifier cascade" << endl;

        //return
        return -1;
    }

    //load the nested cascade classifier object
    nestedCascade.load("haarcascade_eye_tree_eyeglasses.xml");

    //check if the nested cascade classifier object is empty
    if (nestedCascade.empty())
    {
        //print an error message
        cerr << "ERROR: Could not load classifier cascade for nested objects" << endl;

        //return
        return -1;
    }


    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        Mat frame;
        capture >> frame; // Capture frame from camera

        if (!frame.empty())
        {
            //call the detectAndDraw function to detect faces in the current frame
            img = detectAndDraw(frame, cascade, nestedCascade, scale);
            cvtColor(frame, frame, COLOR_BGR2RGB); // Convert color format

            QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
            videoLabel->setPixmap(QPixmap::fromImage(image)); // Display the frame
        }
    });

    timer.start(30); // Update frame every 30 milliseconds

    return app.exec();
}

//write a function that will detect faces and draw moustache on them in the current frame and return combined frame
Mat detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale)
{
    //create a vector of Rect objects
    vector<Rect> faces, faces2;

    //create a Mat object to store the current frame
    Mat gray, smallImg;

    //convert the current frame to grayscale
    cvtColor(img, gray, COLOR_BGR2GRAY);

    //resize the grayscale image
    double fx = 1 / scale;
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);

    //equalize the histogram
    equalizeHist(smallImg, smallImg);

    //detect faces of different sizes using cascade classifier object
    cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    //iterate over the faces and draw a rectangle around them
    for (size_t i = 0; i < faces.size(); i++)
    {
        //draw a rectangle around the detected face
        //rectangle(img, Point(cvRound(faces[i].x * scale), cvRound(faces[i].y * scale)), Point(cvRound((faces[i].x + faces[i].width - 1) * scale), cvRound((faces[i].y + faces[i].height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);

        //create a Mat object to store the region of interest in the grayscale image
        Mat faceROI = smallImg(faces[i]);

        //create a vector of Rect objects
        vector<Rect> nestedObjects;

        //detect eyes in the region of interest
        nestedCascade.detectMultiScale(faceROI, nestedObjects, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        //iterate over the eyes and draw a rectangle around them
        for (size_t j = 0; j < nestedObjects.size(); j++)
        {
            //create a Point object to store the top left corner of the rectangle
            Point center;

            //create an integer variable to store the radius of the rectangle
            int radius;

            //calculate the center and radius of the rectangle
            center.x = cvRound((faces[i].x + nestedObjects[j].x + nestedObjects[j].width * 0.5) * scale);
            center.y = cvRound((faces[i].y + nestedObjects[j].y + nestedObjects[j].height * 0.5) * scale);
            radius = cvRound((nestedObjects[j].width + nestedObjects[j].height) * 0.25 * scale);

            //draw a rectangle around the detected eye
            //circle(img, center, radius, Scalar(0, 255, 0), 3, 8, 0);

        }

        //open moustache image
        Mat moustache = imread("moustache.png", -1);
        
      //clear the background of moustache image
        Mat moustacheMask;

        //resize moustache to fit the face
        resize(moustache, moustache, Size(faces[i].width, faces[i].height/2));

        vector<Mat> moustacheChannels;
        split(moustache, moustacheChannels);
        Mat moustacheMask1 = moustacheChannels[2].clone();
        threshold(moustacheMask1, moustacheMask, 100, 255, THRESH_BINARY_INV);

        //copyto with mask
        Mat moustacheROI = img(Rect(faces[i].x, faces[i].y + faces[i].height*7 / 16, faces[i].width, faces[i].height/2));
        moustache.copyTo(moustacheROI, moustacheMask);

        //open glasses image
        Mat glasses = imread("glasses.png", -1);
      //clear the background of glasses image
        Mat glassesMask;

        //resize glasses to fit the face
        resize(glasses, glasses, Size(faces[i].width, faces[i].height/2));

        vector<Mat> glassesChannels;
        split(glasses, glassesChannels);
        cout<<glassesChannels.size()<<endl;
        Mat glassesMask1 = glassesChannels[0].clone();

        threshold(glassesMask1, glassesMask, 100, 255, THRESH_BINARY_INV);

        //copyto with mask
        Mat glassesROI = img(Rect(faces[i].x, faces[i].y + faces[i].height*1/10, faces[i].width, faces[i].height/2));
        glasses.copyTo(glassesROI, glassesMask);
    }    
    //return the combined frame
    return img;
}
