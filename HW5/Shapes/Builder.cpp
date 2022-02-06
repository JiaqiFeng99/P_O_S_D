#include "Builder.h"

void ShapeMediaBuilder::buildShapeMedia(Shape *s){
    sm = new ShapeMedia(s);
}
void ShapeMediaBuilder::buildComboMedia(){
}
Media* ShapeMediaBuilder::getMedia(){
    return sm;
}

void ComboMediaBuilder::buildShapeMedia(Shape *s){
    cm->add(new ShapeMedia(s));
}
void ComboMediaBuilder::buildComboMedia(){
    cm = new ComboMedia();
}
Media* ComboMediaBuilder::getMedia(){
    return cm;
}
