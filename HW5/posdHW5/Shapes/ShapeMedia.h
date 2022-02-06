#ifndef SHAPEMEDIA_H_INCLUDED
#define SHAPEMEDIA_H_INCLUDED

#include "Shapes.h"
#include <vector>
#include <string>
#include <stack>

class ShapeMedia;
class ComboMedia;
class Visitor {
public:
    virtual void visitShapeMedia(ShapeMedia *sm) = 0;
    virtual void visitComboMediaPre(ComboMedia *cm) = 0;
    virtual void visitComboMediaPost(ComboMedia *cm) = 0;
};
class DescriptionVisitor : public Visitor{
public:
    DescriptionVisitor (): desc(std::string("")) {}
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMediaPre(ComboMedia *cm);
    void visitComboMediaPost(ComboMedia *cm);
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
        dv->visitComboMediaPre(this);
        for (Media *m: media)
            m->accept(dv);
        dv->visitComboMediaPost(this);
    }
    void add (Media *m) {
        media.push_back(m);
    }
};

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm) {
    desc += sm->getShape()->description();
}

void DescriptionVisitor::visitComboMediaPre(ComboMedia *cm) {
    desc = desc + std::string("x(");
}

void DescriptionVisitor::visitComboMediaPost(ComboMedia *cm) {
    desc = desc + std::string(")");
}


class MediaDirector{
 	public :
        MediaDirector():mb(0){}
		void setMediaBuilder(std::stack<MediaBuilder *> *mbs)
		{
            mb=mbs;
		}
		void concrete(string content)
		{
		    mb = new stack<MediaBuilder *>;
		    MediaBuilder* mbtop = 0;

		    while(!content.empty())
            {
                //在content中找尋不是空格的第一個字元，並回傳此字元位置
                size_t pos=content.find_first_not_of(" ");
                //從POS位置中開始搜尋content,找出"combo("第一次出現的位置
                size_t found=content.find("combo(", pos);
                if(found == pos)
                {
                    mb->push(new ComboMediaBuilder);
                    mb->top()->buildComboMedia();
                    if( !mbtop )
                        mbtop = mb->top();
                    //砍掉"combo("這6個字元
                    content = content.substr(pos+6);
                    continue;
                }

                pos=content.find_first_not_of(" ");
                found=content.find("r(",pos);
                if(found==pos)
                {
                    string s(content.substr(pos+2));
                    stringstream ss(s);
                    double x,y,l,w;
                    ss>>x>>y>>l>>w;
                    //不爲空
                    if(!mb->empty())
                    {
                        mb->top()->buildShapeMedia(new Rectangle(Point(x,y),l,w));
                    }
                    //空
                    else
                    {
                        mbtop = mb->top();
                        mb->push(new ShapeMediaBuilder());
                        mb->top()->buildShapeMedia(new Rectangle(Point(x,y),l,w));
                    }
                    content=content.substr(content.find(")", pos)+1);
                }

                pos=content.find_first_not_of(" ");

            }
		}
		Media *getMedia()
		{
            return mb->top()->getMedia();
		}
	private :
    		std::stack<MediaBuilder *> *mb;
	};

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
