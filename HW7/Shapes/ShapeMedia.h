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
class NameVisitor : public Visitor{
public:
    NameVisitor (): desc(std::string("")) {}
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
    virtual double perimeter()const=0;
    virtual void accept(DescriptionVisitor * dv) = 0;
    virtual void acceptName(NameVisitor * dv) = 0;
    virtual void add(Media * m) {
        throw std::string("Illegal: add on media");
    }
    virtual void setName(string _name)=0;
    virtual string getName()const=0;
    virtual string getAllName()=0;
    virtual void removeMedia(Media* m)=0;
    virtual void addByPosition(Media *m,int i)=0;
};

class ShapeMedia :public Media {
private:
    Shape* shape ;
    string name;
public :
    ShapeMedia( Shape* s ): shape(s) {}
    virtual void accept(DescriptionVisitor * dv) {
        dv->visitShapeMedia(this);
    }
    void acceptName(NameVisitor * nv)
    {
        nv->visitShapeMedia(this);
    }
    double area() const { return shape->area() ; }
    double perimeter()const{ return shape->perimeter() ; }
    Shape * getShape()const {return shape;}
    void setName(string _name)
    {
        name=_name;
    }
    string getName()const
    {
        return name;
    }
    string getAllName()
    {
        return "";
    }
    void removeMedia(Media* m){};
    void addByPosition(Media *m,int i){};
};

class ComboMedia : public Media {
private:
    std::vector<Media*> media;
    string name;
    string allName;
public:
    ComboMedia( std::vector<Media*> m ) : media(m) {}
    ComboMedia () {}
    double area( ) const {
        double total =0;
            for (Media *m: media)
                total += m->area();
        return total;
    }
    double perimeter()const{
        double total =0;
            for (Media *m: media)
                total += m->perimeter();
        return total;
    }
    void accept(DescriptionVisitor * dv) {
        dv->visitComboMediaPre(this);
        for (Media *m: media)
            m->accept(dv);
        dv->visitComboMediaPost(this);
    }
    void acceptName(NameVisitor * nv)
    {
        nv->visitComboMediaPre(this);
        for (Media *m: media)
            m->acceptName(nv);
        nv->visitComboMediaPost(this);
    }
    void add (Media *m) {
        media.push_back(m);
    }
    void setName(string _name)
    {
        name=_name;
    }
    string getName()const
    {
        return name;
    }
    string getAllName()
    {
        for (Media *m: media)
        {
            allName += m->getName();
            allName += " ";
        }
        return allName;
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
               // return;
            }
            p->removeMedia(m);
            i++;
        }
    }
    void addByPosition(Media *m,int i)
    {
        media.insert(media.begin()+i,m);
    }
};

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm) {
    desc += sm->getShape()->description();
}

void DescriptionVisitor::visitComboMediaPre(ComboMedia *cm) {
    desc = desc + std::string("combo(");
}

void DescriptionVisitor::visitComboMediaPost(ComboMedia *cm) {
    desc = desc + std::string(")");
}
void NameVisitor::visitShapeMedia(ShapeMedia *sm) {
    desc += sm->getName()+string(" ");
}

void NameVisitor::visitComboMediaPre(ComboMedia *cm) {
    desc = desc +cm->getName()+std::string("{");
}

void NameVisitor::visitComboMediaPost(ComboMedia *cm) {
    desc = desc + std::string("}");
}

//----------------------------------------MediaBuilder-------------------------
class MediaBuilder {
public:
    virtual void buildComboMedia()=0;
    virtual void buildShapeMedia(Shape *s)=0;
    virtual Media* getMedia()=0;
};
class ShapeMediaBuilder:public MediaBuilder
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
class ComboMediaBuilder:public MediaBuilder
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

class MediaDirector{
 	public :
        MediaDirector():mb(0){}
		void setMediaBuilder(std::stack<MediaBuilder *> *mbs)
		{
            mb=mbs;
		}
		void concrete(string content)
		{

		    while(!content.empty())
            {
                //在content中找尋不是空格的第一個字元，並回傳此字元位置
                size_t pos=content.find_first_not_of(" ");
                //從POS位置中開始搜尋content,找出"combo("第一次出現的位置
                size_t chPosition=content.find("combo(", pos);
                if(chPosition == pos)
                {
                    mb->push(new ComboMediaBuilder);
                    mb->top()->buildComboMedia();
                    //砍掉"combo("這6個字元
                    content = content.substr(pos+6);
                    continue;
                }

                pos=content.find_first_not_of(" ");
                chPosition=content.find("r(",pos);
                if(chPosition==pos)
                {
                    string s(content.substr(pos+2));
                    stringstream ss(s);
                    double x,y,l,w;
                    ss>>x>>y>>l>>w;
                    //空
                    if(mb->empty())
                    {
                        mb->push(new ShapeMediaBuilder());
                        mb->top()->buildShapeMedia(new Rectangle(x,y,l,w));
                    }
                    //不爲空
                    else
                    {
                        mb->top()->buildShapeMedia(new Rectangle(x,y,l,w));
                    }
                    if(mb->size()!=1)
                    {
                        content = content.substr(content.find(")", pos)+2);
                    }
                    else
                    {
                        content = content.substr(content.find(")", pos));
                    }
                }

                pos=content.find_first_not_of(" ");
                chPosition=content.find("c(",pos);
                if(chPosition==pos)
                {
                    string s(content.substr(pos+2));
                    stringstream ss(s);
                    double x,y,r;
                    ss>>x>>y>>r;
                    if(mb->empty())
                    {
                        mb->push(new ShapeMediaBuilder());
                        mb->top()->buildShapeMedia(new Circle(x,y,r));
                    }
                    else
                    {
                        mb->top()->buildShapeMedia(new Circle(x,y,r));
                    }
                    if(mb->size()!=1)
                    {
                        content = content.substr(content.find(")", pos)+2);
                    }
                    else
                    {
                        content = content.substr(content.find(")", pos));
                    }
                }

                pos=content.find_first_not_of(" ");
                chPosition=content.find("t(",pos);
                if(chPosition==pos)
                {
                    string s(content.substr(pos+2));
                    stringstream ss(s);
                    double x1,x2,x3,y1,y2,y3;
                    ss>>x1>>y1>>x2>>y2>>x3>>y3;
                    if(mb->empty())
                    {
                        mb->push(new ShapeMediaBuilder());
                        mb->top()->buildShapeMedia(new Triangle(x1,y1,x2,y2,x3,y3));
                    }
                    else
                    {
                        mb->top()->buildShapeMedia(new Triangle(x1,y1,x2,y2,x3,y3));
                    }
                    if(mb->size()!=1)
                    {
                        content = content.substr(content.find(")", pos)+2);
                    }
                    else
                    {
                        content = content.substr(content.find(")", pos));
                    }
                }

                pos=content.find_first_not_of(" ");
                chPosition=content.find(")",pos);
                if(chPosition==pos)
                {
                    if(!mb->empty()&&(mb->size()!=1))
                    {
                        MediaBuilder *aMb=mb->top();
                        mb->pop();
                        mb->top()->getMedia()->add(aMb->getMedia());
                    }
                    content=content.substr(pos+1);
                }
            }
		}
//		Media *getMedia()
//		{
//            return mb->top()->getMedia();
//		}
	private :
    		std::stack<MediaBuilder *> *mb;
};
#endif // SHAPEMEDIA_H_INCLUDED
