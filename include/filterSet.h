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
    FaceFilter* currentFilter(); // Returns the current filter
    void indexUp(); // Increments the index
    void indexDown(); // Decrements the index
private:
    std::vector<FaceFilter*> filters; // Vector of filters
    int index;
};


#endif  // FILTERSET_H