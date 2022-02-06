#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
#include"ShapeMedia.h"
class Command{
    public:
        Command(){}
        virtual void Execute() = 0;
        virtual void Undo() = 0;
};
class DefineCommand:public Command
{
public:
    DefineCommand(vector<Media*> *mv, Media *m ):v(mv),media(m){}
    void Execute()
    {
        v->push_back(media);
    }
    void Undo()
    {
        v->pop_back();
    }
private:
    vector<Media*> *v;
    Media *media;
};
class AddCommand:public Command
{
public:
    AddCommand(Media *f,Media *s):father(f),son(s){}
    void Execute()
    {
        father->add(son);
//        DescriptionVisitor dv;
//        NameVisitor nv;
//        father->accept(&dv);
//        father->acceptName(&nv);
//        cout<<">>"<<father->getName()<<" = "<<nv.getDescription()<<"= "<<dv.getDescription()<<endl;
    }
    void Undo()
    {
        father->removeMedia(son);
//        DescriptionVisitor dv;
//        NameVisitor nv;
//        father->accept(&dv);
//        father->acceptName(&nv);
//        cout<<">>"<<father->getName()<<" = "<<nv.getDescription()<<"= "<<dv.getDescription()<<endl;
    }
private:
    Media *father;
    Media *son;
};
class DeleteCommand:public Command
{
public:
    DeleteCommand(vector<Media*> *mv, Media *m,int i):v(mv),targe(m),index(i){}
    void Execute()
    {
        v->erase(v->begin()+index);
    }
    void Undo()
    {
        v->insert(v->begin()+index,targe);
    }
private:
    vector<Media*> *v;
    Media *targe;
    int index;
};
class DeleteFromComboCommand:public Command
{
public:
    DeleteFromComboCommand(Media *f,Media *s,int i):father(f),son(s),index(i){}
    void Execute()
    {
        father->removeMedia(son);
//        DescriptionVisitor dv;
//        NameVisitor nv;
//        father->accept(&dv);
//        father->acceptName(&nv);
//        cout<<">>"<<father->getName()<<" = "<<nv.getDescription()<<"= "<<dv.getDescription()<<endl;
    }
    void Undo()
    {
        father->addByPosition(son,index);
//        DescriptionVisitor dv;
//        NameVisitor nv;
//        father->accept(&dv);
//        father->acceptName(&nv);
//        cout<<">>"<<father->getName()<<" = "<<nv.getDescription()<<"= "<<dv.getDescription()<<endl;
    }
private:
    Media *father;
    Media *son;
    int index;
};


#endif // COMMAND_H_INCLUDED
