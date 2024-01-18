#include "carousel.h"

template<typename T>
Carousel<T>::Carousel() {
    index = 0;
}

template<typename T>
void Carousel<T>::indexDown()
{
    index--;
    if(index < 0)
    {
        index = nodes.size() - 1;
    }
}   

template<typename T>
T* Carousel<T>::currentNode()
{
    return nodes[index];
}

// Member function implementations
template<typename T>
void Carousel<T>::addNode(T *filter) {
    // Add the filter to the set
    filters.push_back(filter);
}

template<typename T>
Carousel<T>::~Carousel() {
    // Delete any dynamically allocated memory here
    for(int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}
