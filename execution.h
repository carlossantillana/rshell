#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include "rshell.h"

class Execution: public RShell
{
private:
    string input;
    string exe;
    string connectors;
    vector<RShell*> commandList;
    pid_t pid;
public:
    Execution();
    bool execute();
    string get_input();
    void set_commands(vector<string> commandList);
    void print();
    void make_tree();
};

#endif
