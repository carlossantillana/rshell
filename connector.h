#ifndef __CONNECTOR_H__
#define __CONNECTOR_H_

#include "rshell.h"

class Connector: public RShell //No longer child of execute
{
private:
        RShell *left; //Operation left of connector
        RShell *right; //Operation right of connector
public:
  string get_input() //Returns input (needs testing)
{
		string i;
		return i;
}
        virtual bool excute() = 0; //Pure virtual
};

#endif
