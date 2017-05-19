//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

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
    virtual ~RShell() {}// for memory management
    virtual bool execute() = 0; //pure virtual
    virtual string get_input() = 0; //pure virtual
    virtual string get_type() {return type;} // pure virtual
    virtual void set_right_child(RShell* r)=0;
    virtual RShell* get_left()=0;
    virtual RShell* get_right()=0;
  };

#endif
