#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <string>
#include "Shapes.h"

class Text{
public:
    Text(Rectangle rect, std::string text):r(rect), t(text){}
    Rectangle r;
    std::string t;
};


#endif // TEXT_H_INCLUDED
