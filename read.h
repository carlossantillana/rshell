#ifndef __READ_H__
#define __READ_H__

#include "rshell.h"
#include "execute.h"
#include <queue>

class Read: public RShell
{
private:
    string input;
    //queue<RShell*> commandList;
    queue<string> commandList;
public:
    Read();
    Read(string i);
    void par();
    void set_input(string input);
    virtual bool execute(); //pure virtual
    virtual string get_input(); //pure virtual
};

#endif
