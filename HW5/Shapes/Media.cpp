#include <string>
#include <iostream>
#include "Media.h"
#include "Visitor.h"

double ShapeMedia::area() const{
    return shape->area();
}
void ShapeMedia::accept(MediaVisitor * mv){
    mv->visitShapeMedia(this);
}
Shape* ShapeMedia::getShape() const{
    return shape;
}

double ComboMedia::area() const{
    double total =0;
    for(Media *m: media)
        total += m->area();
    return total;
}
void ComboMedia::accept(MediaVisitor * mv){
    mv->visitComboMedia(this, true);
    for (Media *m: media)
        m->accept(mv);
    mv->visitComboMedia(this, false);
}
void ComboMedia::add(Media *m){
    media.push_back(m);
}
void ComboMedia::removeMedia(Media *m){
    int index = 0;
    DescriptionVisitor dv;
    m->accept(&dv);

    for(Media *mm: media){
        DescriptionVisitor dvv;
        mm->accept(&dvv);
        if( dv.getDescription() == dvv.getDescription() ){
            media.erase(media.begin()+index);
            index--; // solved for two shapes with same Description
        }
        mm->removeMedia(m);
        index++;
    }
}

Text* TextMedia::getText(){
    return t;
}
double TextMedia::area() const{
    return t->r.area();
}
void TextMedia::accept(MediaVisitor *mv){
    mv->visitTextMedia(this);
}
