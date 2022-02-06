#ifndef MIDIA_H_INCLUDED
#define MIDIA_H_INCLUDED

#include <vector>
#include <string>
#include "Shapes.h"
#include "Visitor.h"
#include "Text.h"

class Media{
public :
    virtual double area() const = 0 ;
    virtual void accept(MediaVisitor * mv) = 0;
    virtual void add(Media *m){}
    virtual void removeMedia(Media *m){}
};

class ShapeMedia:public Media{
private:
    Shape* shape ;
public :
    ShapeMedia(Shape *s): shape(s){}
    double area() const;
    void accept(MediaVisitor *mv);
    Shape *getShape() const;
};
class ComboMedia:public Media{
public:
    ComboMedia(){}
    ComboMedia(std::vector<Media*> m):media(m){}
    double area() const;
    void accept(MediaVisitor *mv);
    void add(Media *m);
    void removeMedia(Media *m);
private:
    std::vector<Media*> media;
};
class TextMedia:public Media{
public:
    TextMedia(Text text):t(&text){}
    double area() const;
    void accept(MediaVisitor *mv);
    Text* getText();
private:
    Text *t;
};

#endif // MIDIA_H_INCLUDED
