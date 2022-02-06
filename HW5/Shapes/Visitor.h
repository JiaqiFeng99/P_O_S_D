#ifndef VISITOR_H_INCLUDED
#define VISITOR_H_INCLUDED

#include <string>
#include "Media.h"

class ShapeMedia;
class ComboMedia;
class TextMedia ;

class MediaVisitor{
public:
    virtual void visitShapeMedia(ShapeMedia *sm) = 0;
    virtual void visitComboMedia(ComboMedia *cm, bool start) = 0;
    virtual void visitTextMedia (TextMedia  *tm) = 0;
};

class DescriptionVisitor:public MediaVisitor{
public:
    DescriptionVisitor(): desc(std::string("")) {}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm, bool start);
    void visitTextMedia (TextMedia  *tm);
    std::string getDescription() const;
private:
    std::string desc;
};

class AreaVisitor:public MediaVisitor{
public:
    AreaVisitor():area(0){}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm, bool start);
    void visitTextMedia (TextMedia  *tm);
    double getArea() const;
private:
    double area;
};

class PerimeterVisitor:public MediaVisitor{
public:
    PerimeterVisitor():perimeter(0){}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm, bool start);
    void visitTextMedia (TextMedia  *tm);
    double getPerimeter() const;
private:
    double perimeter;
};

#endif // VISITOR_H_INCLUDED
