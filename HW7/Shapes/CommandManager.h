#ifndef COMMANDMANAGER_H_INCLUDED
#define COMMANDMANAGER_H_INCLUDED
#include "Command.h"
class CommandManager{
     public:
        CommandManager()
        {
        }
        void ExecuteCMD(Command *cmd)
        {
            undocmds.push(cmd);
        }
        void RedoCMD()
        {
            if(redocmds.empty())
            {
                cout<<"no command, redo fail!"<<endl;
                return;
            }
            else
            {
                Command *cm=redocmds.top();
                redocmds.pop();
                cm->Execute();
                undocmds.push(cm);
            }
        }
        void UndoCMD()
        {
            if(undocmds.empty())
            {
                cout<<"no command, undo fail!"<<endl;
                return;
            }
            else
            {
                Command *cm=undocmds.top();
                undocmds.pop();
                cm->Undo();
                redocmds.push(cm);
            }
        }
    private:
        stack<Command*> undocmds;
        stack<Command*> redocmds;
};

#endif // COMMANDMANAGER_H_INCLUDED
