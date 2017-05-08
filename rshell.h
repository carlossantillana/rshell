#ifndef __RSHELL_H__
#define __RSHELL_H__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RShell //Base class
{
private:
    string input; //User input
    string type; //Visible representation of children
public:
    RShell() {} //Default Constructor
    virtual bool execute() = 0; //pure virtual
    virtual string get_input() = 0; //pure virtual
    /*virtual void set_input(string i)
    {
      this->input = i;
    } delete later if remained unused.*/
};

#endif
