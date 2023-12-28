#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "centralWidget.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        CentralWidget *centralWidget = new CentralWidget(this);
        setCentralWidget(centralWidget);
        this->setWindowTitle("Face Detection");
    }
};

#endif // MAINWINDOW_H
