#ifndef FILTERSET_H
#define FILTERSET_H

#include <vector>
#include <string>
#include <map>
#include "updateLabelInterface.h"
#include "baseFilter.h"
#include "carousel.h"
<<<<<<< HEAD
#include <string>
class FilterSet: public UpdateLabelInterface{
private:
        
        std::map<std::string,Carousel<BaseFilter>*> carousels; // map containing all off the button carousels
        std::map<std::string,BaseFilter*> filters; // map containing all of the filters in a set
        const std::string name; // name of the set
=======
class FilterSet: public UpdateLabelInterface{
private:
        std::map<std::string,Carousel<BaseFilter>*> carousels;
        std::map<std::string,BaseFilter*> filters;
        const std::string name;
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61

    public:
        FilterSet() {}

<<<<<<< HEAD
        FilterSet(std::string name, std::map<std::string,Carousel<BaseFilter>*> carousels,
                 std::map<std::string,std::string>set) : name(name), carousels(carousels)
        {
            for (auto& filter : set)
            {
                addFilter(filter.first,filter.second);
            }
        }

        // Method to add a filter to the set
        void addFilter(std::string type, std::string name) {
            filters[type] = carousels[type]->getNode(name);
=======
        FilterSet(std::string name, std::map<std::string,Carousel<BaseFilter>*> carousels) : name(name), carousels(carousels) {}

        FilterSet(std::map<std::string,BaseFilter*> filters,std::string name, std::map<std::string,Carousel<BaseFilter>*> carousels) :
                 filters(filters), name(name), carousels(carousels) {}

        // Method to add a filter to the set
        void addFilter(std::string name,BaseFilter* filter) {
            filters[name] = filter;
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
        }

        // Method to get all filters in the set
        std::map<std::string,BaseFilter*> getFilters() const {
            return filters;
        }

    // Method to get the name of the set
    std::string getName() const {
        return name;
    }

<<<<<<< HEAD
    //method to update the label with the name of the set and recusively set all of the filters from the set
=======
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
    void update(QLabel *label) override
    {
        label->setText(QString::fromStdString(getName()));
        //make text bigger
        QFont font = label->font();
        font.setPointSize(20);
        label->setFont(font);  
        for (auto& carousel : carousels)
        {
            try
            {
<<<<<<< HEAD
                //set the node of the filter carousel to the name of the filter
=======
>>>>>>> fa854b025811298ef2e98ea42d1f8358b65bda61
                carousel.second->setNode(filters[carousel.first]->getName());
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }

};

#endif // FILTERSET_H