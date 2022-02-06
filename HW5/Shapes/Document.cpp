#include "Document.h"
#include <string>
#include <fstream>
#include <iostream>

std::string Document::openDocument(const std::string name){
	if(!canOpenDocument(name))
		throw std::string("file is not existed.");
	openFile(name);
	return readFile();
}


void MyDocument::openFile(const std::string name){
    fs.open(name);
}
bool MyDocument::canOpenDocument(const std::string name){
    std::fstream fss;
    fss.open(name);
    if(!fss.is_open())
        return false;
    return true;
}
std::string MyDocument::readFile(){
    std::string line;
    getline(fs, line);
    return line;
}
