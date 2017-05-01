#ifndef __RSHELL_H__
#define __RSHELL_H__

#include <iostream>
#include <string>

using namespace std;

class RShell //Base class
{
private:
    string input; //User input
public:
    virtual bool execute() = 0; //pure virtual
    virtual string get_input() = 0; //pure virtual
};

#endif
