#ifndef FILTERSET_H
#define FILTERSET_H

#include <vector>
#include <string>
#include <map>
#include "updateLabelInterface.h"
#include "baseFilter.h"
#include "carousel.h"
class FilterSet: public UpdateLabelInterface{
private:
        std::map<std::string,Carousel<BaseFilter>*> carousels;
        std::map<std::string,BaseFilter*> filters;
        const std::string name;

    public:
        FilterSet() {}

        FilterSet(std::string name, std::map<std::string,Carousel<BaseFilter>*> carousels) : name(name), carousels(carousels) {}

        FilterSet(std::map<std::string,BaseFilter*> filters,std::string name, std::map<std::string,Carousel<BaseFilter>*> carousels) :
                 filters(filters), name(name), carousels(carousels) {}

        // Method to add a filter to the set
        void addFilter(std::string name,BaseFilter* filter) {
            filters[name] = filter;
        }

        // Method to get all filters in the set
        std::map<std::string,BaseFilter*> getFilters() const {
            return filters;
        }

    // Method to get the name of the set
    std::string getName() const {
        return name;
    }

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