#ifndef UPDATELABELINTERFACE_H
#define UPDATELABELINTERFACE_H
#include <QLabel>

// Contract for updating a label
class UpdateLabelInterface {
public:
    virtual void update(QLabel *label) = 0;
};

#endif // UPDATELABELINTERFACE_H