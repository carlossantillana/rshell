//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "rshell.h"

class Connector: public RShell //No longer child of execute
{
private:
    vector<RShell* > left; //Operations left of connector
    vector<RShell* > right; //Operations right of connector
    string type; //Sets type of child
public:
    Connector(){}
    ~Connector(){}
    virtual string get_type() = 0; //Outputs type string
    virtual bool execute() = 0; //Pure virtual
};

#endif
