//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "rshell.h"

class Connector: public RShell //No longer child of execute
{
private:
    RShell* left; //Operation left of connector
    RShell* right; //Operation right of connector
    string type; //Sets type of child
public:
  Connector(){}
  ~Connector(){
    delete left;
    delete right;
  }
    string get_input() //Prevents abstraction, but does nothing
    {
      return "String";
    }

    virtual string get_type() = 0; //Outputs type string
    virtual bool execute() = 0; //Pure virtual
    virtual void set_right_child(RShell* r){
      right = r;
    }
    virtual RShell* get_left(){return left;}
    virtual RShell* get_right(){return right;}
};

#endif
