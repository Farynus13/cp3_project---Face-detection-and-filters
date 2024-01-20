#include "centralWidget.h"

using namespace cv;
using namespace std;

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    //initialize filter names
    filterNames = {"hat","glasses","beard","monocle","mask","glove","puppet"};

    //create layout
    createLayout();
    
    //load filters
    loadFilters();

    //create filter sets
    createSets();

    capture.open(0); // Open the default camera

    //load the cascade classifier objects
    cascade.load("haarcascade_frontalface_alt.xml");
    fistCascade.load("hand.xml");
    //check if the cascade classifier object is empty
    if (cascade.empty() || fistCascade.empty())
    {
        std:: cerr << "ERROR: Could not load classifier cascade" << std::endl;
    }

    //create a timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        readCamera(cameraLabel);
    });

    //set initial filter set to 1
    filterSetCarousel->updateLabel();
    
    timer->start(50); // Start the timer to update the camera feed
}
void CentralWidget::readCamera(QLabel *cameraLabel) {
        //create a Mat object to store the current frame
        cv::Mat frame,img;
        capture >> frame; // Read the next frame from the camera

        //detect faces/fists and draw filters on them
        img = detectAndDraw(frame);

        // Convert the frame to QImage for display
        QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        image = image.rgbSwapped();

        // Display the image in the label
        cameraLabel->setPixmap(QPixmap::fromImage(image));
    }

Mat CentralWidget::detectAndDraw(Mat& img)
{
    //create a vector of faces and fists
    vector<Rect> faces;
    vector<Rect> fists;
    
    //convert the current frame to grayscale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    //equalize the histogram
    equalizeHist(gray, gray);

    //detect faces and fists of different sizes using cascade classifier object
    cascade.detectMultiScale(gray, faces, 1.1, 5, 0 | CASCADE_SCALE_IMAGE, Size(80,80));
    fistCascade.detectMultiScale(gray, fists, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(80,80));
    try
    {
        //iterate over the fists and draw filters around them
        for (size_t i = 0; i < fists.size(); i++)
        {
            //draw a rectangle around the detected fist
            rectangle(img, Point(cvRound(fists[i].x), cvRound(fists[i].y)), Point(cvRound((fists[i].x + fists[i].width - 1)), cvRound((fists[i].y + fists[i].height - 1))), Scalar(0, 255, 0), 3, 8, 0);
            //apply filters
            filterCarouselMap["glove"]->currentNode()->apply(img,fists[i]);
            filterCarouselMap["puppet"]->currentNode()->apply(img,fists[i]);
        }
        
        //iterate over the faces and draw filters around them
        for (size_t i = 0; i < faces.size(); i++)
        {
            //draw a rectangle around the detected face
            rectangle(img, Point(cvRound(faces[i].x), cvRound(faces[i].y)), Point(cvRound((faces[i].x + faces[i].width - 1)), cvRound((faces[i].y + faces[i].height - 1))), Scalar(255, 0, 0), 3, 8, 0);

            //apply filters
            filterCarouselMap["mask"]->currentNode()->apply(img,faces[i]);
            filterCarouselMap["hat"]->currentNode()->apply(img,faces[i]);
            filterCarouselMap["glasses"]->currentNode()->apply(img,faces[i]);
            filterCarouselMap["beard"]->currentNode()->apply(img,faces[i]);
            filterCarouselMap["monocle"]->currentNode()->apply(img,faces[i]);

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

void CentralWidget::loadFilters() 
{
    //get all file names in a given directory
    QDir directory("../../media/img");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg",QDir::Files);
    //fill filterCarousel with images
    for (int i = 0; i < images.size(); ++i) {
        //read the image
        cv::Mat img = cv::imread("../../media/img/" + images[i].toStdString(), cv::IMREAD_UNCHANGED);
        if(images[i].contains("empty"))
        {
            std::string name = "empty";
            std::string category = name;
            int tr_down = 0;
            for(auto& filterCarousel : filterCarouselMap)
            {
                //add empty filter to all filterCarousels
                filterCarousel.second->addNode(new FaceFilter(img, tr_down, 255, category,name));
            }
        }
        else
        {
            std::string category = images[i].toStdString().substr(2,images[i].toStdString().size()-6);
            std::string name = images[i].toStdString().substr(0,2);
            if(filterCarouselMap.count(category) > 0)
            {
                //add filter to the corresponding filterCarousel
                int tr_down;
                if(category == "puppet" || category == "glove")
                {
                    tr_down = 200;
                    filterCarouselMap[category]->addNode(new FistFilter(img, tr_down, 255, category,name));
                } else {
                        tr_down = 200;
                    
                    filterCarouselMap[category]->addNode(new FaceFilter(img, tr_down, 255, category,name));
                }
            } 
        }
        
    }
}

void CentralWidget::createLayout() 
{
    //create a grid layout
    layout = new QGridLayout(this);
    //create a label to display the camera feed
    cameraLabel = new QLabel(this);
    //Align to center
    cameraLabel->setAlignment(Qt::AlignCenter);

    //initialize all filterCarousels in a map
    for(auto& name : filterNames)
    {
        filterCarouselMap[name] = new Carousel<BaseFilter>(name);
    }
    //initialize filterSetCarousel
    filterSetCarousel = new Carousel<FilterSet>("Filter Set");

    //add all filterCarousels to the layout
    int counter = 0;
    for (auto& filterCarousel : filterCarouselMap)
    {
        layout->addWidget(filterCarousel.second->getWidget(), 3, counter, 1, 1);
        counter++;
    }
    //add filterSetCarousel to the layout
    layout->addWidget(filterSetCarousel->getWidget(), 1, 0, 1, 1);
    //add cameraLabel to the layout
    layout->addWidget(cameraLabel, 0, 0, 3, filterCarouselMap.size());
    //set layout
    setLayout(layout);
}

void CentralWidget::createSets()
{
    //create a map of <string,string> to initialize the filterSets
    std::map<std::string,std::string> set1 = {
        {"hat","01"},
        {"glasses","01"},
        {"beard","01"},
        {"monocle","empty"},
        {"mask","empty"},
        {"glove","empty"},
        {"puppet","01"}
    };

    std::map<std::string,std::string> set2 = {
        {"hat","05"},
        {"glasses","empty"},
        {"beard","02"},
        {"monocle","01"},
        {"mask","empty"},
        {"glove","empty"},
        {"puppet","empty"}
    };

    std::map<std::string,std::string> set3 = {
        {"hat","05"},
        {"glasses","empty"},
        {"beard","01"},
        {"monocle","empty"},
        {"mask","03"},
        {"glove","empty"},
        {"puppet","empty"}
    };
    

    //fill filterSetCarousel with filterSets
    FilterSet* filterSet1 = new FilterSet("Italian Mafia",filterCarouselMap,set1);
    FilterSet* filterSet2 = new FilterSet("French Lord",filterCarouselMap,set2);
    FilterSet* filterSet3 = new FilterSet("Fancy Zulu",filterCarouselMap,set3);

    filterSetCarousel->addNode(filterSet1);
    filterSetCarousel->addNode(filterSet2);
    filterSetCarousel->addNode(filterSet3);
}