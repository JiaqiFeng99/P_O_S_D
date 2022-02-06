#include <string>
#include "Media.h"
#include "Visitor.h"

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm){
    desc += sm->getShape()->description();
}
void DescriptionVisitor::visitComboMedia(ComboMedia *cm, bool start){
    if( start )
        desc = desc + std::string("combo(");
    else
        desc = desc + std::string(")");
}
void DescriptionVisitor::visitTextMedia(TextMedia *tm){
    desc = tm->getText()->t;
}
std::string DescriptionVisitor::getDescription() const{
    return desc;
}

void AreaVisitor::visitShapeMedia(ShapeMedia *sm){
    area += sm->getShape()->area();
}
void AreaVisitor::visitComboMedia(ComboMedia *cm, bool start){
}
void AreaVisitor::visitTextMedia(TextMedia *tm){
    area = tm->area();
}
double AreaVisitor::getArea() const{
    return area;
}

void PerimeterVisitor::visitShapeMedia(ShapeMedia *sm){
    perimeter += sm->getShape()->perimeter();
}
void PerimeterVisitor::visitComboMedia(ComboMedia *cm, bool start){
}
void PerimeterVisitor::visitTextMedia(TextMedia *tm){
}
double PerimeterVisitor::getPerimeter() const{
    return perimeter;
}
