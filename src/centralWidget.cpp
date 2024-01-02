#include "centralWidget.h"
#include <QDir>

using namespace cv;
using namespace std;

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    //get all file names in a given directory
    QDir directory("../../media/img");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg",QDir::Files);
    //create vectors of FaceFilter objects
    for (int i = 0; i < images.size(); ++i) {
        cv::Mat img = cv::imread("../../media/img/" + images[i].toStdString(), cv::IMREAD_UNCHANGED);
        if(images[i].contains("glasses"))
        {
            glassesSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Glasses));
        }
        else if(images[i].contains("beard"))
        {
            beardSet.addFilter(new FaceFilter(img, 80, 255, FaceFilter::Beard));
        }
        else if(images[i].contains("hat"))
        {
            hatSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Hat));
        }
        else if(images[i].contains("mask"))
        {
            maskSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Mask));
        }
        else if(images[i].contains("monocle"))
        {
            monocleSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Monocle));
        }
        else if(images[i].contains("empty"))
        {
            glassesSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Glasses));
            beardSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Beard));
            hatSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Hat));
            maskSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Mask));
            monocleSet.addFilter(new FaceFilter(img, 100, 255, FaceFilter::Monocle));
        }
    }

    QGridLayout *layout = new QGridLayout(this);
    QLabel *cameraLabel = new QLabel(this);
    QLabel *hatLabel = new QLabel(this);
    QLabel *glassesLabel = new QLabel(this);
    QLabel *beardLabel = new QLabel(this);
    QLabel *monocleLabel = new QLabel(this);
    QLabel *maskLabel = new QLabel(this);
    QPushButton *hatButtonUp = new QPushButton("Hat>", this);
    QPushButton *hatButtonDown = new QPushButton("<Hat", this);
    QPushButton *glassesButtonUp = new QPushButton("Glasses>", this);
    QPushButton *glassesButtonDown = new QPushButton("<Glasses", this);
    QPushButton *beardButtonUp = new QPushButton("Beard>", this);
    QPushButton *beardButtonDown = new QPushButton("<Beard", this);
    QPushButton *monocleButtonUp = new QPushButton("Monocle>", this);
    QPushButton *monocleButtonDown = new QPushButton("<Monocle", this);
    QPushButton *maskButtonUp = new QPushButton("Mask>", this);
    QPushButton *maskButtonDown = new QPushButton("<Mask", this);

    layout->addWidget(cameraLabel,0,0,1,5);
    layout->addWidget(hatButtonUp,1,0);
    layout->addWidget(hatButtonDown,3,0);
    layout->addWidget(glassesButtonUp,1,1);
    layout->addWidget(glassesButtonDown,3,1);
    layout->addWidget(beardButtonUp,1,2);
    layout->addWidget(beardButtonDown,3,2);
    layout->addWidget(monocleButtonUp,1,3);
    layout->addWidget(monocleButtonDown,3,3);
    layout->addWidget(maskButtonUp,1,4);
    layout->addWidget(maskButtonDown,3,4);
    layout->addWidget(hatLabel,2,0);
    layout->addWidget(glassesLabel,2,1);
    layout->addWidget(beardLabel,2,2);
    layout->addWidget(monocleLabel,2,3);
    layout->addWidget(maskLabel,2,4);
    

    setLayout(layout);
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
        readCamera(cameraLabel,capture);
    });

    timer->start(50); // Start the timer to update the camera feed

    //set initial filter images
    updateFilterLabel(hatLabel, &hatSet);
    updateFilterLabel(glassesLabel, &glassesSet);
    updateFilterLabel(beardLabel, &beardSet);
    updateFilterLabel(monocleLabel, &monocleSet);
    updateFilterLabel(maskLabel, &maskSet);

    connect(hatButtonUp, &QPushButton::clicked, [=]() {
        hatSet.indexUp();
        updateFilterLabel(hatLabel, &hatSet);
    });

    connect(hatButtonDown, &QPushButton::clicked, [=]() {
        hatSet.indexDown();
        updateFilterLabel(hatLabel, &hatSet);
    });

    connect(glassesButtonUp, &QPushButton::clicked, [=]() {
        glassesSet.indexUp();
        updateFilterLabel(glassesLabel, &glassesSet);
    });

    connect(glassesButtonDown, &QPushButton::clicked, [=]() {
        glassesSet.indexDown();
        updateFilterLabel(glassesLabel, &glassesSet);
    });

    connect(beardButtonUp, &QPushButton::clicked, [=]() {
        beardSet.indexUp();
        updateFilterLabel(beardLabel, &beardSet);
    });

    connect(beardButtonDown, &QPushButton::clicked, [=]() {
        beardSet.indexDown();
        updateFilterLabel(beardLabel, &beardSet);
    });

    connect(monocleButtonUp, &QPushButton::clicked, [=]() {
        monocleSet.indexUp();
        updateFilterLabel(monocleLabel, &monocleSet);
    });

    connect(monocleButtonDown, &QPushButton::clicked, [=]() {
        monocleSet.indexDown();
        updateFilterLabel(monocleLabel, &monocleSet);
    });

    connect(maskButtonUp, &QPushButton::clicked, [=]() {
        maskSet.indexUp();
        updateFilterLabel(maskLabel, &maskSet);
    });

    connect(maskButtonDown, &QPushButton::clicked, [=]() {
        maskSet.indexDown();
        updateFilterLabel(maskLabel, &maskSet);
    });

}

void CentralWidget::updateFilterLabel(QLabel *label, FilterSet *filterSet) {
    Mat img = filterSet->currentFilter()->getImg().clone();
    // Convert the frame to QImage for display
    QImage image(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    image = image.rgbSwapped();
    //set image size 150x200
    image = image.scaled(100,100,Qt::KeepAspectRatio);
    label->setPixmap(QPixmap::fromImage(image));
    label->setScaledContents( true );

}

void CentralWidget::readCamera(QLabel *cameraLabel,cv::VideoCapture capture) {
        cv::Mat frame,img;
        capture >> frame; // Read the next frame from the camera
        img = detectAndDraw(frame, cascade, eyesCascade,mouthCascade,noseCascade, scale);

        // Convert the frame to QImage for display
        QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        image = image.rgbSwapped();

        // Display the image in the label
        cameraLabel->setPixmap(QPixmap::fromImage(image));
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
    cascade.detectMultiScale(smallImg, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(80,80));

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
        maskSet.currentFilter()->apply(img,faces[i]);
        beardSet.currentFilter()->apply(img,faces[i]);      
        glassesSet.currentFilter()->apply(img,faces[i]);
        monocleSet.currentFilter()->apply(img,faces[i]);      
        hatSet.currentFilter()->apply(img,faces[i]);
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