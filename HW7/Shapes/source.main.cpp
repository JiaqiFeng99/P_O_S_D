#include "utShapes.h"
#include "Analyzer.h"
#include <iostream>
#include "CommandManager.h"
int main()
{
    Analyzer ana;
    CommandManager cm;
    ana.getCommandManager(&cm);
    char command[100];
    cout<<"comand please such as :- def cSmall = Circle(2,1,1) like PPT,and better not enter spaces at the end of a comand\n\n";
    while(1)
    {
        cin.getline(command, 100);
        //ctrl-y
        if(command[0]==25)
        {
            cout<<">>redo"<<endl;
            cm.RedoCMD();
        }
        //ctrl-z
        else if(cin.eof())
        {
            cout<<">>undo"<<endl;
            cm.UndoCMD();
        }
        else
        {
            try{
                ana.print(command);
            }catch(string s){
                cout << s <<endl;
            }
        }
        cin.clear();
    }
    return 0;
}

