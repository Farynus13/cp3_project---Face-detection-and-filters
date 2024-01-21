#include <QApplication>
#include "../include/mainWindow.h"


using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    int ret = app.exec();

    return ret;
}


