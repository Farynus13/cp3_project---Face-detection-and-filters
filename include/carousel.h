#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <vector>
#include <string>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "updateLabelInterface.h"
#include "carouselWidget.h"
template <typename T>
class Carousel: public CarouselWidget{
    private:

    std::vector<T*> nodes; // Vector of nodes
    int index; // Index of the current node
    std::string name; // Name of the carousel
    public:
    // Constructors
    Carousel() = default;
    Carousel(std::string name): name(name) 
    {
        // Initialize the member variables
        index = 0;
        label = new QLabel();
        buttonUp = new QPushButton("Up");
        buttonDown = new QPushButton("Down");
        //center all labels
        label->setAlignment(Qt::AlignCenter);
        //set layout
        layout = new QVBoxLayout();
        layout->addWidget(label);
        layout->addWidget(buttonUp);
        layout->addWidget(buttonDown);
        carouselWidget = new QWidget();
        carouselWidget->setLayout(layout);
        // Connect the buttons to the indexUp and indexDown slots
        connect(buttonUp, &QPushButton::clicked, this, &Carousel::indexUp);
        connect(buttonDown, &QPushButton::clicked, this, &Carousel::indexDown);
    }
    // Destructor
    ~Carousel();



    // Member functions
    void updateLabel(); // Updates the label with the current node
    void addNode(T *NodeId); // Adds a node to the set
    T* currentNode(); // Returns the current node
    T* getNode(int index); // Returns the node at the given index
    T* getNode(std::string name); // Returns the node with the given name
    void setNode(int index); // Sets the current node to the node at the given index
    void setNode(std::string name); // Sets the current node to the node with the given name
    T* getNode(int index); // Returns the node at the given index
    T* getNode(std::string name); // Returns the node with the given name
    void setNode(int index); // Sets the current node to the node at the given index
    void setNode(std::string name); // Sets the current node to the node with the given name
    void indexUp(); // Increments the index
    void indexDown(); // Decrements the index
    std::string getName() const { return name; } // Returns the name of the carousel
    static_assert(std::is_base_of<UpdateLabelInterface, T>::value,
             "T must be a subclass of UpdateLabelInterface"); // Checks that T is a subclass of UpdateLabel

};

template<typename T>
void Carousel<T>::indexDown()
{
    index--;
    if(index < 0) //if index is less than 0, set it to the last node
    {
        index = nodes.size() - 1;
    }
    updateLabel();
}   

template<typename T>
void Carousel<T>::indexUp()
{
    index++;
    if(index >= nodes.size()) //if index is greater than the size of the vector, set it to the first node
    {
        index = 0;
    }
    updateLabel();
}

template<typename T>
T* Carousel<T>::currentNode()
{
    if(nodes.size() == 0)
    {
        throw std::runtime_error("No nodes in carousel");
    }
    return nodes[index];
}

template<typename T>
void Carousel<T>::addNode(T *node) {
    // Add the filter to the set
    nodes.push_back(node);
}

template<typename T>
void Carousel<T>::updateLabel()
{
    // Update the label
    nodes[index]->update(label);
}

//get node by index
template<typename T>
T* Carousel<T>::getNode(int index) {
    // Return the filter at the given index
    if(index < 0 || index >= nodes.size())
    {
        throw std::runtime_error("Index out of bounds");
    }
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

    throw std::runtime_error("No node with name " + name + " found");
}

//set node by index
template<typename T>
void Carousel<T>::setNode(int index) {
    // Set the current filter to the filter at the given index
    if(index < 0 || index >= nodes.size())
    {
        throw std::runtime_error("Index out of bounds");
    }
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
    throw std::runtime_error("No node with name " + name + " found");
}

template<typename T>
Carousel<T>::~Carousel() {
    // Delete any dynamically allocated memory here
    for(int i = 0; i < nodes.size(); i++)
    {
        delete nodes[i];
    }
    delete label;
    delete buttonUp;
    delete buttonDown;
    delete layout;
    delete carouselWidget;
}

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

    throw std::runtime_error("No node with name " + name + " found");
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
    throw std::runtime_error("No node with name " + name + " found");
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