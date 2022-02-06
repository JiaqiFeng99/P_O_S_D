#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include"Shapes.h"
class Text
{
public:
    Text(Rectangle boundingbox, string text ):r(boundingbox),str(text){}
    string getStr() {return str;}
    Rectangle* getRect() {return &r;}
private:
    Rectangle r;
    string str;
};


#endif // TEXT_H_INCLUDED
