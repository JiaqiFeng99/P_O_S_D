#ifndef ANALYZER_H_INCLUDED
#define ANALYZER_H_INCLUDED
#include "ShapeMedia.h"
#include <iostream>
#include<fstream>
#include <algorithm>
#include"Command.h"
#include"CommandManager.h"
using namespace std;
class Analyzer
{
public:
    void print(char command[100])
    {
//        char command[100];
//        cout<<"comand please such as :- def cSmall = Circle(2,1,1) like PPT,and better not enter spaces at the end of a comand\n\n";
//        while(gets(command))
//        {
            cout<<concrete(command)<<endl;
//        }
    }
    string concrete(string content)
    {
        size_t pos=content.find_first_not_of(" ");//在content中找尋不是空格的第一個字元，並回傳此字元位置
        //cut :- def
        size_t found=content.find(":- def ", pos);//從POS位置中開始搜尋content,找出":- def("第一次出現的位置
        if(pos==found)
        {
            return create(content.substr(pos+7));
        }
        //cut :- save
        found=content.find(":- save ", pos);
        if(pos==found)
        {
            return save(content.substr(pos+8));

        }
        //cut :- load
        found=content.find(":- load ", pos);
        if(pos==found)
        {
            return load(content.substr(pos+9));
        }
        //cut :- show
        found=content.find(":- show", pos);
        if(pos==found)
        {
            return show();
        }
        //cut :- add
        found=content.find(":- add", pos);
        if(pos==found)
        {
            return add(content.substr(pos+7));
        }
        //cut :- delete
        found=content.find(":- delete", pos);
        if(pos==found)
        {
            content=content.substr(pos+10);
            found=content.find("from", pos);

            if(found==string::npos)
            {
                return deleteReal(content);
            }
            else
            {
                return deleteFromCombo(content);
            }
        }
        //cut :-
        found=content.find(":- ", pos);
        if(pos==found)
        {
            return areaAndPerimeter(content.substr(pos+3));
        }
        throw string("error\n");
    }
    string deleteReal(string content)
    {
        //判斷有沒有這個
        if(getMediaByName(content)==0)
        {
            throw string("haven't this shape\n");
        }
        Media* targe=getMediaByName(content);
        int i=0;
        int index;
        for(Media* m:media)
        {
            if(m->getName()==targe->getName())
            {
                media.erase(media.begin()+i);
                index=i;
            }
            i++;
            m->removeMedia(targe);
        }
        Command *command=new DeleteCommand(&media,targe,index);
        commandManager->ExecuteCMD(command);
        return "";
    }
    string deleteFromCombo(string content)
    {
        size_t pos=content.find_first_not_of(" ");
        size_t found=content.find(" ", pos);
        string shape;
        string combo;
        shape=content.substr(pos,found);
        found=content.find("from", pos);
        combo=content.substr(found+5);
        //判斷有沒有這個shape
        if(getMediaByName(shape)==0)
        {
            throw string("haven't this shape\n");
        }
        //判斷有沒有這個combo
        if(getMediaByName(combo)==0)
        {
            throw string("haven't this combo\n");
        }
        //找到在vector裏面的第幾個
        int i=0;
        for(Media* m:media)
        {
            if(m->getName()==shape)
            {
                break;
            }
            else
                i++;
        }
        Media* cm=getMediaByName(combo);
        Media* sh=getMediaByName(shape);
        cm->removeMedia(sh);

        Command *command=new DeleteFromComboCommand(cm,sh,i);
        commandManager->ExecuteCMD(command);
        return "";
    }
    string add(string content)
    {
        //被加入的shape的name
        string fatherName;
        //要加入的shape的name
        string sonName;
        size_t pos=content.find_first_not_of(" ");
        size_t found=content.find("to", pos);
        sonName=content.substr(pos,found-1);
        fatherName=content.substr(found+3);
        //判斷有沒有這個shape
        if(getMediaByName(sonName)==0)
        {
            throw string("haven't this shape\n");
        }
        //判斷有沒有這個combo
        if(getMediaByName(fatherName)==0)
        {
            throw string("haven't this combo\n");
        }
        Media* father=getMediaByName(fatherName);
        Media* son=getMediaByName(sonName);
        father->add(son);
        stringstream sr;
        DescriptionVisitor dv;
        NameVisitor nv;
        father->accept(&dv);
        father->acceptName(&nv);
        sr<<">>"<<fatherName<<" = "<<nv.getDescription()<<"= "<<dv.getDescription();

        Command *command=new AddCommand(father,son);
        commandManager->ExecuteCMD(command);
        return sr.str();
    }
    string show()
    {
        stringstream sr;
        for(Media *m:media)
        {
            sr<<"  "<<m->getName()<<"\n";
        }
        return sr.str();
    }
    string load(string content)
    {
        media.clear();
        string fileName;
        string type;
        string name;
        string comboname;
        size_t pos=content.find_first_not_of(" ");
        size_t found=content.find("txt", pos);
        fileName=content.substr(pos,found+3);
        ifstream fin(fileName);
        string s1,s2;
        while(getline(fin,s1)&&getline(fin,s2))
        {
            size_t pos=s1.find_first_not_of(" ");
            size_t found=s1.find("(", pos);
            type=s1.substr(pos,found);
            s1=s1.substr(found+1);
            //is combo
            if(type=="combo")
            {
                found=s2.find("{", pos);
                comboname=s2.substr(pos,found);
                s2=s2.substr(found+1);
                Media* cm = new ComboMedia();
                cm->setName(comboname);
                media.push_back(cm);
                Media* me;
                while(!s1.empty())
                {
                    pos=s1.find_first_not_of(" ");
                    found=s1.find("r(",pos);
                    if(found==pos)
                    {
                        pos=s2.find_first_not_of(" ");
                        found=s2.find(" ",pos);
                        name=s2.substr(pos,found);
                        s2=s2.substr(found+1);
                        string s(s1.substr(pos+2));
                        stringstream ss(s);
                        double x,y,l,w;
                        ss>>x>>y>>l>>w;
                        //判斷是否有重名
                        if(getMediaByName(name)!=0)
                        {
                            throw string("this name is exist\n");
                        }
                        me=new ShapeMedia(new Rectangle(x,y,l,w));
                        me->setName(name);
                        cm->add(me);
                        media.push_back(me);
                        s1 = s1.substr(s1.find(")", pos)+2);
                    }
                    pos=s1.find_first_not_of(" ");
                    found=s1.find("c(",pos);
                    if(found==pos)
                    {
                        pos=s2.find_first_not_of(" ");
                        found=s2.find(" ",pos);
                        name=s2.substr(pos,found);
                        s2=s2.substr(found+1);
                        string s(s1.substr(pos+2));
                        stringstream ss(s);
                        double x,y,r;
                        ss>>x>>y>>r;
                        //判斷是否有重名
                        if(getMediaByName(name)!=0)
                        {
                            throw string("this name is exist\n");
                        }
                        me=new ShapeMedia(new Circle(x,y,r));
                        me->setName(name);
                        cm->add(me);
                        media.push_back(me);
                        s1 = s1.substr(s1.find(")", pos)+2);
                    }
                    pos=s1.find_first_not_of(" ");
                    found=s1.find("t(",pos);
                    if(found==pos)
                    {
                        pos=s2.find_first_not_of(" ");
                        found=s2.find(" ",pos);
                        name=s2.substr(pos,found);
                        s2=s2.substr(found+1);
                        string s(s1.substr(pos+2));
                        stringstream ss(s);
                        double x1,x2,x3,y1,y2,y3;
                        ss>>x1>>y1>>x2>>y2>>x3>>y3;
                        //判斷是否有重名
                        if(getMediaByName(name)!=0)
                        {
                            throw string("this name is exist\n");
                        }
                        me=new ShapeMedia(new Triangle(x1,y1,x2,y2,x3,y3));
                        me->setName(name);
                        cm->add(me);
                        media.push_back(me);
                        s1 = s1.substr(s1.find(")", pos)+2);
                    }
                    pos=s1.find_first_not_of(" ");
                    found=s1.find(")",pos);
                    if(found==pos)
                    {
                        s1="";
                    }
                }
                stringstream sr;
                sr<<">>loading "<<fileName<<"...\n";
                DescriptionVisitor dv;
                NameVisitor nv;
                cm->accept(&dv);
                cm->acceptName(&nv);
                sr<<comboname<<" = "<<nv.getDescription()<<" = "<<dv.getDescription();
                return sr.str();
            }
            else
            {
                name=s2;
                Media* me;
                if(type=="c")
                {
                    stringstream ss(s1);
                    double x,y,r;
                    ss>>x>>y>>r;
                    //判斷是否有重名
                    if(getMediaByName(name)!=0)
                    {
                        throw string("this name is exist\n");
                    }
                    me=new ShapeMedia(new Circle(x,y,r));
                    me->setName(name);
                    media.push_back(me);
                }
                else if(type=="r")
                {
                    stringstream ss(s1);
                    double x,y,l,w;
                    ss>>x>>y>>l>>w;
                    //判斷是否有重名
                    if(getMediaByName(name)!=0)
                    {
                        throw string("this name is exist\n");
                    }
                    me=new ShapeMedia(new Rectangle(x,y,l,w));
                    me->setName(name);
                    media.push_back(me);
                }
                else if(type=="t")
                {
                    stringstream ss(s1);
                    double x1,x2,x3,y1,y2,y3;
                    ss>>x1>>y1>>x2>>y2>>x3>>y3;
                    //判斷是否有重名
                    if(getMediaByName(name)!=0)
                    {
                        throw string("this name is exist\n");
                    }
                    me=new ShapeMedia(new Triangle(x1,y1,x2,y2,x3,y3));
                    me->setName(name);
                    media.push_back(me);
                }
                stringstream sr;
                sr<<">>loading "<<fileName<<"...\n";
                DescriptionVisitor dv;
                NameVisitor nv;
                me->accept(&dv);
                me->acceptName(&nv);
                sr<<name<<" = "<<nv.getDescription()<<"= "<<dv.getDescription();
                return sr.str();
            }
        }
        return "";
    }
    string save(string content)
    {
        string fileName;
        size_t pos=content.find_first_not_of(" ");
        size_t found=content.find("to", pos);
        string name;
        string out;
        stringstream sr;

        name=content.substr(pos,found-1);
        content=content.substr(found+4);//“要兩個字元所以+5
        found=content.find("txt", pos);
        fileName=content.substr(pos,found+3);
        ofstream fout(fileName);
        Media* me=getMediaByName(name);
        //不存在
        if(me==0)
            throw string("haven't this name\n");

        DescriptionVisitor dv;
        NameVisitor nv;
        me->accept(&dv);
        me->acceptName(&nv);
        fout<<dv.getDescription()<<"\n";
        fout<<nv.getDescription()<<"\n";

        sr<<">>"<<name<<" saved to "<<fileName;
        return sr.str();
    }
    string areaAndPerimeter(string content)
    {
        size_t pos=content.find_first_not_of(" ");
        size_t found=content.find(".", pos);
        string name;
        string compute;
        stringstream sr;
        name=content.substr(pos,found);
        content=content.substr(found+1);//剪到只剩area?或perimeter?
        Media* me=getMediaByName(name);
        if(me==0)
            throw string("haven't this name\n");

        pos=content.find_first_not_of(" ");
        found=content.find("?", pos);
        compute=content.substr(pos,found);
        if(compute=="area")
        {
            sr<<">>"<<me->area();
        }
        else if(compute=="perimeter")
        {
            sr<<">>"<<me->perimeter();
        }
        else
        {
            throw string("error");
        }
        return sr.str();
    }
    string create(string content)
    {
        //get name
        string type;
        string name;
        string out;
        size_t pos=content.find_first_not_of(" ");
        size_t found=content.find("=", pos);
        name=content.substr(0,found-1);
        //判斷是否有重名
        if(getMediaByName(name)!=0)
        {
            throw string("this name is exist\n");
        }
        //cut =
        content=content.substr(found+2);

        //cout type
        out=content;
        //get type
        pos=content.find_first_not_of(" ");
        found=content.find("combo", pos);
        if(found==string::npos)
        {
            //is a shape
            pos=content.find_first_not_of(" ");
            found=content.find("(", pos);
            type=content.substr(pos,found);
            content=content.substr(found+1);
            if(type=="Circle")
            {
                double x,y,r;
                stringstream ss(content);
                ss>>x;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss1(content);
                ss1>>y;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss2(content);
                ss2>>r;

                //creat Circle
                Media* m=new ShapeMedia(new Circle(x,y,r));
                m->setName(name);
                media.push_back(m);
                Command *command =new DefineCommand(&media,m);
                commandManager->ExecuteCMD(command);
            }
            else if(type=="Rectangle")
            {
                double x,y,l,w;
                stringstream ss(content);
                ss>>x;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss1(content);
                ss1>>y;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss2(content);
                ss2>>l;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss3(content);
                ss3>>w;

                //creat Rectangle
                Media* m=new ShapeMedia(new Rectangle(x,y,l,w));
                m->setName(name);
                media.push_back(m);
                Command *command =new DefineCommand(&media,m);
                commandManager->ExecuteCMD(command);
            }
            else if(type=="Triangle")
            {
                double x1,x2,x3,y1,y2,y3;
                stringstream ss(content);
                ss>>x1;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss1(content);
                ss1>>y1;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss2(content);
                ss2>>x2;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss3(content);
                ss3>>y2;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss4(content);
                ss4>>x3;
                content=content.substr(content.find(",",pos)+1);
                stringstream ss5(content);
                ss5>>y3;

                //creat Triangle
                Media* m=new ShapeMedia(new Triangle(x1,y1,x2,y2,x3,y3));
                m->setName(name);
                media.push_back(m);
                Command *command =new DefineCommand(&media,m);
                commandManager->ExecuteCMD(command);
            }

        }
        else
        {

            //is combo
            Media* cm = new ComboMedia();
            cm->setName(name);
            //cout<<"!!"<<cm.getName()<<"!!";
            media.push_back(cm);
            Command *command =new DefineCommand(&media,cm);
            commandManager->ExecuteCMD(command);
            Media* md;
            pos=content.find_first_not_of(" ");
            found=content.find("{", pos);
            type=content.substr(pos,found);
            content=content.substr(found+1);

            //把字串末尾的}變爲，
            replace(content.begin(),content.end(), '}', ',');
            //這時found指向rTall
            string n;
            while(!content.empty())
            {
                pos=content.find_first_not_of(" ");
                found=content.find(",", pos);
                n=content.substr(pos,found);
                content=content.substr(found+1);
                md=getMediaByName(n);
                if(md!=0)
                {
                    cm->add(md);
                }
                else
                {
                    throw string("haven't this shape");
                }
            }
        }
        stringstream sr;
        sr<<">>"<<out;

//        Command *c =new DefineCommand(&meida, );
        return sr.str();
    }
    Media* getMediaByName(string n)
    {
        for (Media *m: media)
        {
            if(m->getName()==n)
                return m;
        }
        return 0;
    }
    void getCommandManager(CommandManager *cm)
    {
        commandManager=cm;
    }
private:
    vector<Media*>media;
    CommandManager *commandManager;
};


#endif // ANALYZER_H_INCLUDED
