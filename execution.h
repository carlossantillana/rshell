#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include "rshell.h"

class Execution: public RShell
{
private:
    vector<string> commandList;
    pid_t pid;
public:
    Execution();
    bool execute();
    string get_input();
    void set_commands(vector<string> commandList);
    void make_tree();
};

#endif
