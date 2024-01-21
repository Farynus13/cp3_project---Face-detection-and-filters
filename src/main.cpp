#include <QApplication>
#include "../include/mainWindow.h"
<<<<<<< HEAD


=======
#include<crtdbg.h>
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
<<<<<<< HEAD
    int ret = app.exec();

    return ret;
=======
    _CrtDumpMemoryLeaks();
    return app.exec();
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
}


