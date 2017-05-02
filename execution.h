#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include "rshell.h"

class Execution: public RShell
{
private:
    string input;
    string exe;
    string connectors;
public:
    bool execute();
    string get_input();
    void print();
};

#endif
