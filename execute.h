#ifndef __EXECUTE_H__
#define __EXECUTE_H__

#include "rshell.h"

class Execute: public RShell
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