#ifndef __READ_H__
#define __READ_H__

#include "rshell.h"
#include "execute.h"
#include <queue>

class Read: public RShell
{
private:
    string input;
    bool found = false;
    //queue<RShell*> commandList;
    queue<string> commandList;
public:
    Read();
    Read(string i);
    void par();
    void set_input(string input);
    bool get_found();
    virtual bool execute(); //pure virtua
    virtual string get_input(); //pure virtual
};

#endif
