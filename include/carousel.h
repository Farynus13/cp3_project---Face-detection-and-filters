#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <vector>

template <typename T>
class Carousel{
public:
    // Constructor
    Carousel();

    // Destructor
    ~Carousel();

    // Member functions
    void addNode(T *NodeId);
    T* currentNode(); // Returns the current node
    void indexUp(); // Increments the index
    void indexDown(); // Decrements the index
private:
    std::vector<T*> nodes; // Vector of node
    int index;
};


#endif  // CAROUSEL_H