#ifndef CAROUSELWIDGET_H
#define CAROUSELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class CarouselWidget : public QWidget {
    Q_OBJECT
    // Member variables
    protected:
    QWidget* carouselWidget; // Widget to add the label and buttons to
    QLabel* label; // Label to update
    QVBoxLayout* layout; // Layout to add the label and buttons to
    QPushButton* buttonUp; // Button to increment the index
    QPushButton* buttonDown; // Button to decrement the index
public:
    CarouselWidget() {}
    // Other member functions and signals/slots can be added here
    QWidget* getWidget() { return carouselWidget; }
};

#endif // CAROUSELWIDGET_H