#ifndef __READ_H__
#define __READ_H__

#include "rshell.h"
#include "execution.h"

class Read: public RShell
{
private:
    string input;
    bool found;
    //queue<RShell*> commandList;
    vector<string> commandList;
public:
    Read();
    Read(string i);
    void par();
    void set_input(string input);
    bool get_found();
    virtual bool execute();
    virtual string get_input();
    vector<string> get_commands();
};

#endif
