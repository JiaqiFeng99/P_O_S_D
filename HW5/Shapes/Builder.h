#ifndef BUILDER_H_INCLUDED
#define BUILDER_H_INCLUDED
#include "Shapes.h"
#include "Media.h"

class MediaBuilder{
 public:
    virtual void buildComboMedia() = 0;
    virtual void buildShapeMedia(Shape * s) = 0;
    virtual Media* getMedia() = 0;
};

class ShapeMediaBuilder:public MediaBuilder{
public:
    ShapeMediaBuilder():sm(0){}
    void buildComboMedia();
    void buildShapeMedia(Shape *s);
    Media* getMedia();
private:
    ShapeMedia *sm;
};

class ComboMediaBuilder:public MediaBuilder{
public:
    ComboMediaBuilder():cm(0){}
    void buildComboMedia();
    void buildShapeMedia(Shape *s);
    Media* getMedia();
private:
    ComboMedia *cm;
};



#endif // BUILDER_H_INCLUDED
