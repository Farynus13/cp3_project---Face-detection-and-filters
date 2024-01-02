#ifndef FILTERSET_H
#define FILTERSET_H

#include <vector>
#include "faceFilter.h"

class FilterSet {
public:
    // Constructor
    FilterSet();

    // Destructor
    ~FilterSet();

    // Member functions
    void addFilter(FaceFilter *filterId);
    FaceFilter* currentFilter();
    void indexUp();
    void indexDown();
private:
    // Private member variables
    std::vector<FaceFilter*> filters;
    int index;
};


#endif  // FILTERSET_H