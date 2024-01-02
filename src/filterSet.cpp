#include "filterSet.h"

FilterSet::FilterSet() {
    // Initialize any member variables here
    index = 0;
}

void FilterSet::indexUp()
{
    index++;
    if(index >= filters.size())
    {
        index = 0;
    }
}

void FilterSet::indexDown()
{
    index--;
    if(index < 0)
    {
        index = filters.size() - 1;
    }
}   

FaceFilter* FilterSet::currentFilter()
{
    return filters[index];
}

// Member function implementations
void FilterSet::addFilter(FaceFilter *filter) {
    // Add the filter to the set
    filters.push_back(filter);
}

FilterSet::~FilterSet() {
    // Delete any dynamically allocated memory here
    for(int i = 0; i < filters.size(); i++)
    {
        delete filters[i];
    }
}
