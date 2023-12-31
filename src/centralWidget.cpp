#include "centralWidget.h"
#include "faceFilter.h"

using namespace cv;
using namespace std;

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    //load the images
    Mat moustacheImg = imread("moustache.png", -1);
    Mat glassesImg = imread("glasses.png", -1);
    Mat fedoraImg = imread("fedora.png", -1);

    //create a vector of FaceFilter objects
    filters.push_back(new FaceFilter(moustacheImg, 80, 255, FaceFilter::Mouth));
    filters.push_back(new FaceFilter(glassesImg, 80, 255, FaceFilter::Eyes));
    filters.push_back(new FaceFilter(fedoraImg, 80, 255, FaceFilter::Hat));

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(this);
    QPushButton *button = new QPushButton("Capture", this);

    layout->addWidget(label);
    layout->addWidget(button);

    cv::VideoCapture capture;
    capture.open(0); // Open the default camera

    //load the cascade classifier object
    cascade.load("haarcascade_frontalface_alt.xml");
    eyesCascade.load("haarcascade_eye_tree_eyeglasses.xml");
    mouthCascade.load("haarcascade_mcs_mouth.xml");
    noseCascade.load("haarcascade_mcs_nose.xml");
    //check if the cascade classifier object is empty
    if (cascade.empty() || eyesCascade.empty() || mouthCascade.empty() || noseCascade.empty())
    {
        //print an error message
    std:: cerr << "ERROR: Could not load classifier cascade" << std::endl;
    }

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        readCamera(label,capture);
    });
    connect(button, &QPushButton::clicked, [=]() {
        timer->stop();
        //capture.release();
        cv::destroyAllWindows();
        this->close();
    });

    timer->start(100); // Start the timer to update the camera feed
}

void CentralWidget::readCamera(QLabel *label,cv::VideoCapture capture) {
        cv::Mat frame,img;
        capture >> frame; // Read the next frame from the camera
        img = detectAndDraw(frame, cascade, eyesCascade,mouthCascade,noseCascade, scale);

        // Convert the frame to QImage for display
        QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        image = image.rgbSwapped();

        // Display the image in the label
        label->setPixmap(QPixmap::fromImage(image));
    }

//write a function that will detect faces and draw moustache on them in the current frame and return combined frame
Mat CentralWidget::detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& eyesCascade,
     CascadeClassifier& mouthCascade, CascadeClassifier& noseCascade,double scale)
{
    //create a vector of Rect objects
    vector<Rect> faces;

    //create a Mat object to store the current frame
    Mat gray, smallImg;

    //convert the current frame to grayscale
    cvtColor(img, gray, COLOR_BGR2GRAY);

    //resize the grayscale image
    double fx = 1 / scale;
    cv::resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT);

    //equalize the histogram
    equalizeHist(smallImg, smallImg);

    //detect faces of different sizes using cascade classifier object
    cascade.detectMultiScale(smallImg, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(50,50));

    //iterate over the faces and draw a rectangle around them
    for (size_t i = 0; i < faces.size(); i++)
    {
        //draw a rectangle around the detected face
        //rectangle(img, Point(cvRound(faces[i].x * scale), cvRound(faces[i].y * scale)), Point(cvRound((faces[i].x + faces[i].width - 1) * scale), cvRound((faces[i].y + faces[i].height - 1) * scale)), Scalar(255, 0, 0), 3, 8, 0);

        // //create a Mat object to store the region of interest in the grayscale image
        // Mat faceROI = smallImg(faces[i]);

        // //create a vector of Rect objects
        // vector<Rect> eyes,mouths,noses;

        // //detect eyes in the region of interest
        // eyesCascade.detectMultiScale(faceROI, eyes, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(20, 20));
        // chooseEyes(eyes,faceROI);
        
        // //iterate over the eyes and draw a rectangle around them
        // for (size_t j = 0; j < eyes.size(); j++)
        // {
        //     //create a Point object to store the top left corner of the rectangle
        //     Point center;

        //     //create an integer variable to store the radius of the rectangle
        //     int radius;

        //     //calculate the center and radius of the rectangle
        //     center.x = cvRound((faces[i].x + eyes[j].x + eyes[j].width * 0.5) * scale);
        //     center.y = cvRound((faces[i].y + eyes[j].y + eyes[j].height * 0.5) * scale);
        //     radius = cvRound((eyes[j].width + eyes[j].height) * 0.25 * scale);

        //     //draw a circle around the detected eye
        //     cv::circle(img, center, radius, Scalar(0, 255, 0), 3, 8, 0);

        // }
        for (size_t j = 0; j < filters.size(); j++)
        {
                (*filters[j]).apply(img, faces[i]);
        }
    }    
    //return the combined frame
    return img;
}

void CentralWidget::chooseEyes(vector<Rect> &eyes, Mat& faceROI) {
    // Sort the detected eyes by their y-coordinate (vertical position)
    std::sort(eyes.begin(), eyes.end(), [](const Rect& a, const Rect& b) {
        return a.y < b.y;
    });

    // If more than two eyes were detected, keep only the two that are most similar in size
    if (eyes.size() > 2)
    {
        // Calculate the average height of the detected eyes
        double avgHeight = 0.0;
        for (const Rect& eye : eyes)
        {
            avgHeight += eye.height;
        }
        avgHeight /= eyes.size();

        // Keep only the eyes that are closest to the average height
        eyes.erase(std::remove_if(eyes.begin(), eyes.end(), [avgHeight](const Rect& eye) {
            return std::abs(eye.height - avgHeight) > avgHeight * 0.01;  // Adjust the threshold as needed
        }), eyes.end());

        // If more than two eyes are still detected, keep only the two that are closest to the center
        if (eyes.size() > 2)
        {
            std::nth_element(eyes.begin(), eyes.begin() + 2, eyes.end(), [faceROI](const Rect& a, const Rect& b) {
                double centerA = a.x + a.width / 2.0;
                double centerB = b.x + b.width / 2.0;
                double faceCenter = faceROI.cols / 2.0;
                return std::abs(centerA - faceCenter) < std::abs(centerB - faceCenter);
            });
            eyes.resize(2);
        }
    }
}