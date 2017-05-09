#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include "rshell.h"

class Execution: public RShell
{
private:
    vector<RShell*> commandList;
    pid_t pid;
public:
    Execution();
    bool execute();
    string get_input();
    void set_commands(vector<RShell*> commandList);
    void make_tree(vector<RShell*> cList);
    virtual string get_type();
    vector<char *> str_to_char();
};

#endif
