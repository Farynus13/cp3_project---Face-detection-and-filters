#include "centralWidget.h"
#include <QDir>
#include <QDir>

using namespace cv;
using namespace std;

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    //get all file names in a given directory
    QDir directory("../../media/img");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg",QDir::Files);
    //fill filterCarousel with images
    for (int i = 0; i < images.size(); ++i) {
        cv::Mat img = cv::imread("../../media/img/" + images[i].toStdString(), cv::IMREAD_UNCHANGED);
        if(images[i].contains("glasses"))
        {
            glassesCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Glasses));
        }
        else if(images[i].contains("beard"))
        {
            beardCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Beard));
        }
        else if(images[i].contains("hat"))
        {
            hatCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Hat));
        }
        else if(images[i].contains("mask"))
        {
            maskCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Mask));
        }
        else if(images[i].contains("monocle"))
        {
            monocleCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Monocle));
        }
        else if(images[i].contains("fist"))
        {
            if(images[i].contains("glove"))
            {
                gloveCarousel.addNode(new FistFilter(img, 200, 255, FistFilter::Glove));
            }
            else if(images[i].contains("puppet"))
            {
                puppetCarousel.addNode(new FistFilter(img, 200,255, FistFilter::Puppet));
            }
        }
        else if(images[i].contains("empty"))
        {
            glassesCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty));
            beardCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty));
            hatCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty));
            maskCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty));
            monocleCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty));
            gloveCarousel.addNode(new FistFilter(img, 0, 255, FistFilter::Empty));
            puppetCarousel.addNode(new FistFilter(img, 0, 255, FistFilter::Empty));
        }
    }
    //create layout
    QGridLayout *layout = new QGridLayout(this);
    QLabel *cameraLabel = new QLabel(this);
    QLabel *hatLabel = new QLabel(this);
    QLabel *glassesLabel = new QLabel(this);
    QLabel *beardLabel = new QLabel(this);
    QLabel *monocleLabel = new QLabel(this);
    QLabel *maskLabel = new QLabel(this);
    QLabel *gloveLabel = new QLabel(this);
    QLabel *puppetLabel = new QLabel(this);
    //create buttons
    QPushButton *puppetButtonUp = new QPushButton("Puppet>", this);
    QPushButton *puppetButtonDown = new QPushButton("<Puppet", this);
    QPushButton *gloveButtonUp = new QPushButton("Glove>", this);
    QPushButton *gloveButtonDown = new QPushButton("<Glove", this);
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
    //center all labels 
    cameraLabel->setAlignment(Qt::AlignCenter);
    hatLabel->setAlignment(Qt::AlignCenter);
    glassesLabel->setAlignment(Qt::AlignCenter);
    beardLabel->setAlignment(Qt::AlignCenter);
    monocleLabel->setAlignment(Qt::AlignCenter);
    maskLabel->setAlignment(Qt::AlignCenter);
    gloveLabel->setAlignment(Qt::AlignCenter);
    puppetLabel->setAlignment(Qt::AlignCenter);
    //set layout
    layout->addWidget(cameraLabel,0,0,1,7);
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
    layout->addWidget(gloveButtonUp,1,5);
    layout->addWidget(gloveButtonDown,3,5);
    layout->addWidget(hatLabel,2,0);
    layout->addWidget(glassesLabel,2,1);
    layout->addWidget(beardLabel,2,2);
    layout->addWidget(monocleLabel,2,3);
    layout->addWidget(maskLabel,2,4);
    layout->addWidget(gloveLabel,2,5);
    layout->addWidget(puppetButtonUp,1,6);
    layout->addWidget(puppetButtonDown,3,6);
    layout->addWidget(puppetLabel,2,6);

    setLayout(layout);

    //create camera object
    cv::VideoCapture capture;
    capture.open(0); // Open the default camera

    //load the cascade classifier object
    cascade.load("haarcascade_frontalface_alt.xml");
    fistCascade.load("fist.xml");
    //check if the cascade classifier object is empty
    if (cascade.empty() or fistCascade.empty())
    {
        //print an error message
    std:: cerr << "ERROR: Could not load classifier cascade" << std::endl;
    }

    //create a timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        readCamera(cameraLabel,capture);
    });

    timer->start(50); // Start the timer to update the camera feed

    //set initial filter images
    updateFilterLabel(hatLabel, &hatCarousel);
    updateFilterLabel(glassesLabel, &glassesCarousel);
    updateFilterLabel(beardLabel, &beardCarousel);
    updateFilterLabel(monocleLabel, &monocleCarousel);
    updateFilterLabel(maskLabel, &maskCarousel);
    updateFilterLabel(gloveLabel, &gloveCarousel);
    updateFilterLabel(puppetLabel, &puppetCarousel);

    //connect buttons to functions
    connect(hatButtonUp, &QPushButton::clicked, [=]() {
        hatCarousel.indexUp();
        updateFilterLabel(hatLabel, &hatCarousel);
    });

    connect(hatButtonDown, &QPushButton::clicked, [=]() {
        hatCarousel.indexDown();
        updateFilterLabel(hatLabel, &hatCarousel);
    });

    connect(glassesButtonUp, &QPushButton::clicked, [=]() {
        glassesCarousel.indexUp();
        updateFilterLabel(glassesLabel, &glassesCarousel);
    });

    connect(glassesButtonDown, &QPushButton::clicked, [=]() {
        glassesCarousel.indexDown();
        updateFilterLabel(glassesLabel, &glassesCarousel);
    });

    connect(beardButtonUp, &QPushButton::clicked, [=]() {
        beardCarousel.indexUp();
        updateFilterLabel(beardLabel, &beardCarousel);
    });

    connect(beardButtonDown, &QPushButton::clicked, [=]() {
        beardCarousel.indexDown();
        updateFilterLabel(beardLabel, &beardCarousel);
    });

    connect(monocleButtonUp, &QPushButton::clicked, [=]() {
        monocleCarousel.indexUp();
        updateFilterLabel(monocleLabel, &monocleCarousel);
    });

    connect(monocleButtonDown, &QPushButton::clicked, [=]() {
        monocleCarousel.indexDown();
        updateFilterLabel(monocleLabel, &monocleCarousel);
    });

    connect(maskButtonUp, &QPushButton::clicked, [=]() {
        maskCarousel.indexUp();
        updateFilterLabel(maskLabel, &maskCarousel);
    });

    connect(maskButtonDown, &QPushButton::clicked, [=]() {
        maskCarousel.indexDown();
        updateFilterLabel(maskLabel, &maskCarousel);
    });

    connect(gloveButtonUp, &QPushButton::clicked, [=]() {
        gloveCarousel.indexUp();
        updateFilterLabel(gloveLabel, &gloveCarousel);
    });

    connect(gloveButtonDown, &QPushButton::clicked, [=]() {
        gloveCarousel.indexDown();
        updateFilterLabel(gloveLabel, &gloveCarousel);
    });

    connect(puppetButtonUp, &QPushButton::clicked, [=]() {
        puppetCarousel.indexUp();
        updateFilterLabel(puppetLabel, &puppetCarousel);
    });

    connect(puppetButtonDown, &QPushButton::clicked, [=]() {
        puppetCarousel.indexDown();
        updateFilterLabel(puppetLabel, &puppetCarousel);
    });
}

void CentralWidget::updateFilterLabel(QLabel *label, Carousel<BaseFilter> *filterCarousel) {
    //Get the current filter image
    Mat img = filterCarousel->currentNode()->getImg().clone();
    // Convert the frame to QImage for display
    QImage image(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    image = image.rgbSwapped();
    //set image size 150x150
    image = image.scaled(150,150,Qt::KeepAspectRatio);
    // Display the image in the label
    label->setPixmap(QPixmap::fromImage(image));
}

void CentralWidget::readCamera(QLabel *cameraLabel,cv::VideoCapture capture) {
        //create a Mat object to store the current frame
        cv::Mat frame,img;
        capture >> frame; // Read the next frame from the camera

        //detect faces and draw filters on them
        img = detectAndDraw(frame);

        // Convert the frame to QImage for display
        QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        image = image.rgbSwapped();

        // Display the image in the label
        cameraLabel->setPixmap(QPixmap::fromImage(image));
    }

Mat CentralWidget::detectAndDraw(Mat& img)
{
    //create a vector of faces
    //create a vector of faces
    vector<Rect> faces;
    vector<Rect> fists;
    //create a Mat object to store the current frame
    Mat gray;

    //convert the current frame to grayscale
    cvtColor(img, gray, COLOR_BGR2GRAY);

    //equalize the histogram
    equalizeHist(gray, gray);

    //detect faces of different sizes using cascade classifier object
    cascade.detectMultiScale(gray, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(80,80));
    fistCascade.detectMultiScale(gray, fists, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(80,80));
    try
    {
        for (size_t i = 0; i < fists.size(); i++)
        {
            //draw a rectangle around the detected fist
            rectangle(img, Point(cvRound(fists[i].x), cvRound(fists[i].y)), Point(cvRound((fists[i].x + fists[i].width - 1)), cvRound((fists[i].y + fists[i].height - 1))), Scalar(0, 255, 0), 3, 8, 0);
            gloveCarousel.currentNode()->apply(img,fists[i]);
            puppetCarousel.currentNode()->apply(img,fists[i]);
        }
        //iterate over the faces and draw filters around them
        for (size_t i = 0; i < faces.size(); i++)
        {
            //draw a rectangle around the detected face
            //rectangle(img, Point(cvRound(faces[i].x), cvRound(faces[i].y)), Point(cvRound((faces[i].x + faces[i].width - 1)), cvRound((faces[i].y + faces[i].height - 1))), Scalar(255, 0, 0), 3, 8, 0);

            //apply filters
            maskCarousel.currentNode()->apply(img,faces[i]);
            beardCarousel.currentNode()->apply(img,faces[i]);      
            glassesCarousel.currentNode()->apply(img,faces[i]);
            monocleCarousel.currentNode()->apply(img,faces[i]);      
            hatCarousel.currentNode()->apply(img,faces[i]);
        }    
    } //exception for trying to merge with empty Mat
    catch (cv::Exception& e)
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }
    //return the combined frame
    return img;
}