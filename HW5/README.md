HW5

Please pull the latest code from github. Use the Document interface below : 
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

The OpenDocument Method is the Template Method. The MyDocument class implements this interface.
Write tests and functions :
 Problem 1(test 10%, function 10%). Use MyDocument to load from the file ”myShape.txt”. The file content is 
                combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))         
         Please test the string returned by readFile() using the content of ”myShape.txt”. 

 class MediaDirector{
 	public :
		void setMediaBuilder(std::stack<MediaBuilder *> *mbs);
		void concrete(string content);
	private :
    		std::stack<MediaBuilder *> *mb;
	};

Problem 2(test 10%, function 20%). Based on Problem 1, use MediaDirector class to handle the contents returned by readFile() and call MediaBuilder’s methods buildComboMedia() and buildShapeMedia() to build a ComboMedia. 

Problem 3(30%) TA will load different files to test your program. The ComboMedia built should be correct.

