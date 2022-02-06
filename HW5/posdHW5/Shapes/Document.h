#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED
#include<fstream>
#include<iostream>
class Document
{
public :
     string openDocument(const string name){
        if(!canOpenDocument(name))
            throw std::string("file is not existed.");
        openFile(name);
        return readFile();
    }
protected :
    virtual void openFile(const string name) = 0;
    virtual bool canOpenDocument(const string name) = 0;
    virtual string readFile() = 0;
};
class MyDocument:public Document
{
protected :
    void openFile(const string name)
    {
        in.open(name);
    }
    bool canOpenDocument(const string name)
    {
        in.open(name);
        bool i=in.is_open();
        in.close();
        return i;
    }
    string readFile()
    {
        return getline(in,fileContent);
    }
private:
        ifstream in;
};


#endif // DOCUMENT_H_INCLUDED
