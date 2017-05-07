#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "rshell.h"

class Connector: public RShell //No longer child of execute
{
private:
    RShell *left; //Operation left of connector
    RShell *right; //Operation right of connector
public:
    string get_input() //Prevents abstraction, but does nothing
    {
          return "String Theory";
    }

    virtual bool execute() = 0; //Pure virtual
};

#endif
