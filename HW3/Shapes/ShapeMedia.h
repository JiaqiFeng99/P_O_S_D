#ifndef SHAPEMEDIA_H_INCLUDED
#define SHAPEMEDIA_H_INCLUDED

#include "Shapes.h"
#include <vector>
class ShapeMedia;
class ComboMedia;
class MediaVisitor
{
public:
    virtual void visitShapeMedia(ShapeMedia *sm)=0;
    virtual void visitComboMedia(ComboMedia *cm)=0;
};
class AreaVisitor:public MediaVisitor
{
public:
    AreaVisitor():area(0){}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm);
    double getArea()const
    {
        return area;
    }
private:
    double area;
};
class PerimeterVisitor:public MediaVisitor
{
public:
    PerimeterVisitor():perimeter(0){}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm);
    double getPerimeter()const
    {
        return perimeter;
    }
private:
    double perimeter;
};


class Media {
public :
    virtual double area() const = 0 ;
    virtual double perimeter() const=0;
    virtual void accept(MediaVisitor *mv)=0;
};

class ShapeMedia :public Media {
private:
    Shape* shape ;
public :
    ShapeMedia( Shape* s ): shape(s) {}
    double area() const { return shape->area() ; }
    double perimeter()const{ return shape->perimeter();}
    void accept(MediaVisitor *mv)
    {
        mv->visitShapeMedia(this);
    }
    Shape* getShape()
    {
        return shape;
    }
};

class ComboMedia : public Media {
private:
    std::vector<Media*> media;
public:
    ComboMedia( std::vector<Media*> m ) : media(m) {}
    double area( ) const {
        double total =0;
        for (Media *m: media)
            total += m->area();
        return total;
    }
    double perimeter()const
    {
        double total=0;
        for(Media *m:media)
            total+=m->perimeter();
        return total;
    }
    void add(Media* p)
    {
        media.push_back(p);
    }
    void accept(MediaVisitor *mv)
    {
        for(Media* p:media)
            p->accept(mv);
        mv->visitComboMedia(this);
    }
};


void AreaVisitor::visitShapeMedia(ShapeMedia *sm)
{
    area+=sm->getShape()->area();
}
void AreaVisitor::visitComboMedia(ComboMedia *cm)
{
//    area=cm->area();
}
void PerimeterVisitor::visitShapeMedia(ShapeMedia *sm)
{
    perimeter+=sm->getShape()->perimeter();
}
void PerimeterVisitor::visitComboMedia(ComboMedia *cm)
{
//    perimeter=cm->perimeter();
}

#endif // SHAPEMEDIA_H_INCLUDED
