#ifndef DIRECTOR_H_INCLUDED
#define DIRECTOR_H_INCLUDED
#include "Builder.h"
#include <stack>
#include <string>

class MediaDirector{
public :
    MediaDirector():mb(0){}
    void setMediaBuilder(std::stack<MediaBuilder *> *mbs);
    void concrete(std::string content);
    Media* getMedia();
private :
    std::stack<MediaBuilder *> *mb;
};


#endif // DIRECTOR_H_INCLUDED
