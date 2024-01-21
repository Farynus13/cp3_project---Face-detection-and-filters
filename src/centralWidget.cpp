#include "centralWidget.h"

using namespace cv;
using namespace std;

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
<<<<<<< HEAD
    //initialize filter names
    filterNames = {"hat","glasses","beard","monocle","mask","glove","puppet"};

    //create layout
    createLayout();
    
    //load filters
    loadFilters();
=======
    
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
    QLabel  *filterSetLabel = new QLabel(this);
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
    QPushButton *filterSetButtonUp = new QPushButton("Filter Set>", this);
    QPushButton *filterSetButtonDown = new QPushButton("<Filter Set", this);
    //center all labels 
    cameraLabel->setAlignment(Qt::AlignCenter);
    hatLabel->setAlignment(Qt::AlignCenter);
    glassesLabel->setAlignment(Qt::AlignCenter);
    beardLabel->setAlignment(Qt::AlignCenter);
    monocleLabel->setAlignment(Qt::AlignCenter);
    maskLabel->setAlignment(Qt::AlignCenter);
    gloveLabel->setAlignment(Qt::AlignCenter);
    puppetLabel->setAlignment(Qt::AlignCenter);
    filterSetLabel->setAlignment(Qt::AlignCenter);
    //set layout
    layout->addWidget(cameraLabel,0,1,3,7);
    layout->addWidget(filterSetButtonUp,0,1);
    layout->addWidget(filterSetButtonDown,2,1);
    layout->addWidget(filterSetLabel,1,1);
    layout->addWidget(hatButtonUp,3,0);
    layout->addWidget(hatButtonDown,5,0);
    layout->addWidget(glassesButtonUp,3,1);
    layout->addWidget(glassesButtonDown,5,1);
    layout->addWidget(beardButtonUp,3,2);
    layout->addWidget(beardButtonDown,5,2);
    layout->addWidget(monocleButtonUp,3,3);
    layout->addWidget(monocleButtonDown,5,3);
    layout->addWidget(maskButtonUp,3,4);
    layout->addWidget(maskButtonDown,5,4);
    layout->addWidget(gloveButtonUp,3,5);
    layout->addWidget(gloveButtonDown,5,5);
    layout->addWidget(hatLabel,4,0);
    layout->addWidget(glassesLabel,4,1);
    layout->addWidget(beardLabel,4,2);
    layout->addWidget(monocleLabel,4,3);
    layout->addWidget(maskLabel,4,4);
    layout->addWidget(gloveLabel,4,5);
    layout->addWidget(puppetButtonUp,3,6);
    layout->addWidget(puppetButtonDown,5,6);
    layout->addWidget(puppetLabel,4,6);
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61

    //create filter sets
    createSets();

<<<<<<< HEAD
=======
    //call constructor for all filterCarousels
    glassesCarousel = Carousel<BaseFilter>(glassesLabel);
    beardCarousel = Carousel<BaseFilter>(beardLabel);
    hatCarousel = Carousel<BaseFilter>(hatLabel);
    maskCarousel = Carousel<BaseFilter>(maskLabel);
    monocleCarousel = Carousel<BaseFilter>(monocleLabel);
    gloveCarousel = Carousel<BaseFilter>(gloveLabel);
    puppetCarousel = Carousel<BaseFilter>(puppetLabel);
    filterSetCarousel = Carousel<FilterSet>(filterSetLabel);

    //get all file names in a given directory
    QDir directory("../../media/img");
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg",QDir::Files);
    //fill filterCarousel with images
    for (int i = 0; i < images.size(); ++i) {
        cv::Mat img = cv::imread("../../media/img/" + images[i].toStdString(), cv::IMREAD_UNCHANGED);
        if(images[i].contains("glasses"))
        {
            std::string name = images[i].toStdString().substr(8);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            glassesCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Glasses,name));
        }
        else if(images[i].contains("beard"))
        {
            std::string name = images[i].toStdString().substr(6);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            beardCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Beard,name));
        }
        else if(images[i].contains("hat"))
        {
            std::string name = images[i].toStdString().substr(4);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            hatCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Hat,name));
        }
        else if(images[i].contains("mask"))
        {
            std::string name = images[i].toStdString().substr(5);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            maskCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Mask,name));
        }
        else if(images[i].contains("monocle"))
        {
            std::string name = images[i].toStdString().substr(8);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            monocleCarousel.addNode(new FaceFilter(img, 100, 255, FaceFilter::Monocle,name));
        }
        else if(images[i].contains("glove"))
        {
            std::string name = images[i].toStdString().substr(6);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            gloveCarousel.addNode(new FistFilter(img, 200, 255, FistFilter::Glove,name));
        }
        else if(images[i].contains("puppet"))
        {
            std::string name = images[i].toStdString().substr(7);
            //delete .png / .jpg from name
            name.erase(name.end()-4,name.end());
            puppetCarousel.addNode(new FistFilter(img, 200, 255, FistFilter::Puppet,name));
        }
        else if(images[i].contains("empty"))
        {
            std::string name = "empty";
            glassesCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty,name));
            beardCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty,name));
            hatCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty,name));
            maskCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty,name));
            monocleCarousel.addNode(new FaceFilter(img, 0, 255, FaceFilter::Empty,name));
            gloveCarousel.addNode(new FistFilter(img, 0, 255, FistFilter::Empty,name));
            puppetCarousel.addNode(new FistFilter(img, 0, 255, FistFilter::Empty,name));
        }
    }
    
    //map of pointers to all filterCarousels
    map<string,Carousel<BaseFilter>*> filterCarousels;
    filterCarousels["Hat"] = &hatCarousel;
    filterCarousels["Glasses"] = &glassesCarousel;
    filterCarousels["Beard"] = &beardCarousel;
    filterCarousels["Monocle"] = &monocleCarousel;
    filterCarousels["Mask"] = &maskCarousel;
    filterCarousels["Glove"] = &gloveCarousel;
    filterCarousels["Puppet"] = &puppetCarousel;


    //fill filterSetCarousel with filterSets
    FilterSet* filterSet1 = new FilterSet("Filter Set 1",filterCarousels);
    filterSet1->addFilter("Hat",hatCarousel.getNode("1"));
    filterSet1->addFilter("Glasses",glassesCarousel.getNode("1"));
    filterSet1->addFilter("Beard",beardCarousel.getNode("1"));
    filterSet1->addFilter("Monocle",monocleCarousel.getNode("empty"));
    filterSet1->addFilter("Mask",maskCarousel.getNode("empty"));
    filterSet1->addFilter("Glove",gloveCarousel.getNode("empty"));
    filterSet1->addFilter("Puppet",puppetCarousel.getNode("1"));
    filterSetCarousel.addNode(filterSet1);

    FilterSet* filterSet2 = new FilterSet("Filter Set 2",filterCarousels);
    filterSet2->addFilter("Hat",hatCarousel.getNode("5"));
    filterSet2->addFilter("Glasses",glassesCarousel.getNode("empty"));
    filterSet2->addFilter("Beard",beardCarousel.getNode("2"));
    filterSet2->addFilter("Monocle",monocleCarousel.getNode("1"));
    filterSet2->addFilter("Mask",maskCarousel.getNode("empty"));
    filterSet2->addFilter("Glove",gloveCarousel.getNode("2"));
    filterSet2->addFilter("Puppet",puppetCarousel.getNode("empty"));
    filterSetCarousel.addNode(filterSet2);



    //create camera object
    cv::VideoCapture capture;
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
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
        readCamera();
    });

    //set initial filter set to 1
    filterSetCarousel->updateLabel();
    
    timer->start(50); // Start the timer to update the camera feed
<<<<<<< HEAD
}
void CentralWidget::readCamera() {
=======

    //set initial filter set to 1
    filterSetCarousel.updateLabel();


    //connect buttons to functions
    connect(hatButtonUp, &QPushButton::clicked, [=]() {
        hatCarousel.indexUp();
    });

    connect(hatButtonDown, &QPushButton::clicked, [=]() {
        hatCarousel.indexDown();
    });

    connect(glassesButtonUp, &QPushButton::clicked, [=]() {
        glassesCarousel.indexUp();
    });

    connect(glassesButtonDown, &QPushButton::clicked, [=]() {
        glassesCarousel.indexDown();
    });

    connect(beardButtonUp, &QPushButton::clicked, [=]() {
        beardCarousel.indexUp();
    });

    connect(beardButtonDown, &QPushButton::clicked, [=]() {
        beardCarousel.indexDown();
    });

    connect(monocleButtonUp, &QPushButton::clicked, [=]() {
        monocleCarousel.indexUp();
    });

    connect(monocleButtonDown, &QPushButton::clicked, [=]() {
        monocleCarousel.indexDown();
    });

    connect(maskButtonUp, &QPushButton::clicked, [=]() {
        maskCarousel.indexUp();
    });

    connect(maskButtonDown, &QPushButton::clicked, [=]() {
        maskCarousel.indexDown();
    });

    connect(gloveButtonUp, &QPushButton::clicked, [=]() {
        gloveCarousel.indexUp();
    });

    connect(gloveButtonDown, &QPushButton::clicked, [=]() {
        gloveCarousel.indexDown();
    });

    connect(puppetButtonUp, &QPushButton::clicked, [=]() {
        puppetCarousel.indexUp();
    });

    connect(puppetButtonDown, &QPushButton::clicked, [=]() {
        puppetCarousel.indexDown();
    });

    connect(filterSetButtonUp, &QPushButton::clicked, [=]() {
        filterSetCarousel.indexUp();
    }
    );

    connect(filterSetButtonDown, &QPushButton::clicked, [=]() {
        filterSetCarousel.indexDown();
    });
}
void CentralWidget::readCamera(QLabel *cameraLabel,cv::VideoCapture capture) {
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
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
    fistCascade.detectMultiScale(gray, fists, 1.1, 4, 0 | CASCADE_SCALE_IMAGE, Size(80,80));
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