#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED
#include <string>
#include <fstream>

class Document{
public :
    std::string openDocument(const std::string name);
protected :
    virtual void openFile(const std::string name) = 0;
    virtual bool canOpenDocument(const std::string name) = 0;
    virtual std::string readFile() = 0;
};

class MyDocument: public Document{
public:
    MyDocument():fs(0){};
protected:
    void openFile(const std::string name);
    bool canOpenDocument(const std::string name);
    std::string readFile();
private:
    std::fstream fs;
};

#endif // DOCUMENT_H_INCLUDED
