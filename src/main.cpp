#include <QApplication>
#include "../include/mainWindow.h"
#include<crtdbg.h>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    _CrtDumpMemoryLeaks();
    return app.exec();
}


