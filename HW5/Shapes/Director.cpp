#include "Director.h"
#include "Shapes.h"
#include "Point.h"
#include "Visitor.h"
#include <iostream>
using namespace std;
#include <stack>
#include <string>
#include <sstream>

void MediaDirector::setMediaBuilder(std::stack<MediaBuilder *> *mbs){
    mb = mbs;
}
void MediaDirector::concrete(std::string content){

    mb = new std::stack<MediaBuilder *>;
    MediaBuilder* mbtop = 0;

    while( !content.empty() ){
        std::size_t pos = content.find_first_not_of(" ");
        std::size_t found = content.find("combo(", pos);
        if(found == pos){
            cout<<"1";
            mb->push(new ComboMediaBuilder);
            mb->top()->buildComboMedia();
            if( !mbtop )
                mbtop = mb->top();
            content = content.substr(pos+6);
            continue;
        }

        pos = content.find_first_not_of(" ");
        found = content.find("r(", pos);
        if(found == pos){
                cout<<"2";
            std::string s(content.substr(pos+2));
            std::stringstream ss(s);
            double x, y, l, w;
            ss >> x >> y >> l >> w;
            if( !mb->empty() )
                mb->top()->buildShapeMedia(new Rectangle(Point(x, y), l, w));
            else{

                mb->push(new ShapeMediaBuilder());
                mb->top()->buildShapeMedia(new Rectangle(Point(x, y), l, w));
                mbtop = mb->top();
            }
            if(mb->size()!=1)
            {
                content = content.substr(content.find(")", pos)+2);
            }

            else
            {
                content = content.substr(content.find(")", pos));
                //cout<<"!!"<<content<<"!!";
            }

        }

        pos = content.find_first_not_of(" ");
        found = content.find("c(", pos);
        if(found == pos){
                cout<<"3";
            std::string s(content.substr(pos+2));
            std::stringstream ss(s);
            double x, y, r;
            ss >> x >> y >> r;
            if( !mb->empty() )
                mb->top()->buildShapeMedia(new Circle(Point(x, y), r));
            else{

                mb->push(new ShapeMediaBuilder());
                mb->top()->buildShapeMedia(new Circle(Point(x, y), r));
                mbtop = mb->top();
            }
                content = content.substr(content.find(")", pos)+2);

        }

        pos = content.find_first_not_of(" ");
        found = content.find("t(", pos);
        if(found == pos ){
                cout<<"4";
            std::string s(content.substr(pos+2));
            std::stringstream ss(s);
            double x1, y1, x2, y2, x3, y3;
            ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            if( !mb->empty() )
                mb->top()->buildShapeMedia(new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3)));
            else{

                mb->push(new ShapeMediaBuilder());
                mb->top()->buildShapeMedia(new Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3)));
                mbtop = mb->top();
            }
                content = content.substr(content.find(")", pos)+2);
        }

        pos = content.find_first_not_of(" ");
        found = content.find(")", pos);
        if(found == pos){
                cout<<"5";
            if( !mb->empty() && (mb->size()!=1) ){
                cout<<"5_2";
                MediaBuilder* cmb = mb->top();
                mb->pop();
                mb->top()->getMedia()->add(cmb->getMedia());
            }
            content = content.substr(pos+1);
            //cout<<"??"<<content<<"??";
        }
    }
}

Media* MediaDirector::getMedia(){
    return mb->top()->getMedia();
}
