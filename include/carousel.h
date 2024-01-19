#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <vector>
#include <QLabel>
#include "updateLabelInterface.h"

template <typename T>
class Carousel{
public:
    // Constructor
    Carousel() = default;
    Carousel(QLabel *label);
    // Destructor
    ~Carousel();


    // Member functions
    void updateLabel(); // Declare the updateLabel function


    void addNode(T *NodeId);
    T* currentNode(); // Returns the current node
    T* getNode(int index); // Returns the node at the given index
    T* getNode(std::string name); // Returns the node with the given name
    void setNode(int index); // Sets the current node to the node at the given index
    void setNode(std::string name); // Sets the current node to the node with the given name
    void indexUp(); // Increments the index
    void indexDown(); // Decrements the index
    static_assert(std::is_base_of<UpdateLabelInterface, T>::value, "T must be a subclass of ActionInterface");

    private:
    QLabel *label;
    std::vector<T*> nodes; // Vector of node
    int index;
};


template<typename T>
Carousel<T>::Carousel(QLabel *label) : label(label) {
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
    updateLabel();
}   

template<typename T>
void Carousel<T>::indexUp()
{
    index++;
    if(index >= nodes.size())
    {
        index = 0;
    }
    updateLabel();
}

template<typename T>
T* Carousel<T>::currentNode()
{
    return nodes[index];
}

// Member function implementations
template<typename T>
void Carousel<T>::addNode(T *node) {
    // Add the filter to the set
    nodes.push_back(node);
}

template<typename T>
void Carousel<T>::updateLabel()
{
    nodes[index]->update(label);
}

//get node by index
template<typename T>
T* Carousel<T>::getNode(int index) {
    // Return the filter at the given index
    return nodes[index];
}

//get node by name
template<typename T>
T* Carousel<T>::getNode(std::string name) {
    // Return the filter with the given name
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->getName() == name)
        {
            return nodes[i];
        }
    }

    std::cerr << "No node with name " << name << " found" << std::endl;
    //available in
    std::cerr << "Available nodes: " << std::endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        std::cerr << nodes[i]->getName() << std::endl;
    }
    return nullptr;
}

//set node by index
template<typename T>
void Carousel<T>::setNode(int index) {
    // Set the current filter to the filter at the given index
    this->index = index;
    updateLabel();
}

//set node by name
template<typename T>
void Carousel<T>::setNode(std::string name) {
    // Set the current filter to the filter with the given name
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->getName() == name)
        {
            index = i;
            updateLabel();
            return;
        }
    }
    std::cerr << "No node with name " << name << " found" << std::endl;
    //available in
    std::cerr << "Available nodes: " << std::endl;
    for(int i = 0; i < nodes.size(); i++)
    {
        std::cerr << nodes[i]->getName() << std::endl;
    }
}

template<typename T>
Carousel<T>::~Carousel() {
    // Delete any dynamically allocated memory here
    for(int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
}

#endif  // CAROUSEL_H