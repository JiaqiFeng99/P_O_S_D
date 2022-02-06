#ifndef SHAPEMEDIA_H_INCLUDED
#define SHAPEMEDIA_H_INCLUDED

#include "Shapes.h"
#include "Text.h"
#include <vector>
#include <string>

class ShapeMedia;
class ComboMedia;
class TextMedia;
class DescriptionVisitor {
public:
    DescriptionVisitor (): desc(std::string("")) {}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm,bool start);
    void visitTextMedia(TextMedia *tm);
    std::string getDescription() const {return desc;}
private:
    std::string desc;
};

class Media {
public :
    virtual double area() const = 0 ;
    virtual void accept(DescriptionVisitor * dv) = 0;
    virtual void add(Media * m) {
        throw std::string("Illegal: add on media");
    }
    virtual void removeMedia(Media* m)=0;
};
//----------------------------------------TextMedia-------------------------
class TextMedia:public Media
{
public:
    TextMedia(Text *t):text(t){}
    double area()const{return text->getRect()->area();}
    void accept(DescriptionVisitor * dv){dv->visitTextMedia(this);}
    void add(Media * m) {}
    void removeMedia(Media* m){}
    string getString(){return text->getStr();}
private:
    Text *text;
};
class ShapeMedia :public Media {
private:
    Shape* shape ;
public :
    ShapeMedia( Shape* s ): shape(s) {}
    virtual void accept(DescriptionVisitor * dv) {
        dv->visitShapeMedia(this);
    }
    double area() const { return shape->area() ; }
    Shape * getShape()const {return shape;}
    void removeMedia(Media* m){};
};

class ComboMedia : public Media {
private:
    std::vector<Media*> media;
public:
    ComboMedia( std::vector<Media*> m ) : media(m) {}
    ComboMedia () {}
    double area( ) const {
        double total =0;
            for (Media *m: media)
                total += m->area();
        return total;
    }
    void accept(DescriptionVisitor * dv) {
        dv->visitComboMedia(this,true);
        for (Media *m: media)
            m->accept(dv);
        dv->visitComboMedia(this,false);
    }
    void add (Media *m) {
        media.push_back(m);
    }
    void removeMedia(Media* m)
    {
        int i=0;
        DescriptionVisitor dv1;
        m->accept(&dv1);
        for(Media *p:media)
        {
            DescriptionVisitor dv2;
            p->accept(&dv2);
            if(dv1.getDescription()==dv2.getDescription())
            {
                media.erase(media.begin()+i);
                i--;
                return;
            }
            p->removeMedia(m);
            i++;
        }
    }
};

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm) {
    desc += sm->getShape()->description();
}

void DescriptionVisitor::visitComboMedia(ComboMedia *cm,bool start) {
    if(start)
        desc = desc + std::string("combo(");
    else
        desc = desc + std::string(")");
}
void DescriptionVisitor::visitTextMedia(TextMedia *tm)
{
    desc=tm->getString();
}
//----------------------------------------MediaBuilder-------------------------
class MediaBuilder {
public:
    virtual void buildComboMedia()=0;
    virtual void buildShapeMedia(Shape *s)=0;
    virtual Media* getMedia()=0;
};
class ShapeMediaBuilder:MediaBuilder
{
public:
    ShapeMediaBuilder():shape(0){}
    void buildComboMedia()
    {

    }
    void buildShapeMedia(Shape *s)
    {
        shape=new ShapeMedia(s);
    }
    Media* getMedia()
    {
        return shape;
    }
private:
    ShapeMedia* shape;
};
class ComboMediaBuilder:MediaBuilder
{
public:
    ComboMediaBuilder():combo(0){}
    void buildComboMedia()
    {
        combo=new ComboMedia;
    }
    void buildShapeMedia(Shape *s)
    {
        combo->add(new ShapeMedia(s));
    }
    void buildAddComboMedia(Media* cm)
    {
        combo->add(cm);
    }
    Media* getMedia()
    {
        return combo;
    }
private:
    ComboMedia* combo;
};
#endif // SHAPEMEDIA_H_INCLUDED
