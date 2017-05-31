//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector //Conector is the base of operators
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
	string type; //Sets type of child
	bool executed;//determines if was already executed
	bool exec;// determines whether or not to execute
public:
	And() //Default Constructor
	: type("&&"), executed(false), exec(true)
	{}

	And(RShell* l) //RShell Constructor
	: left(l), type("&&"), executed(false), exec(true)
	{}

	And(RShell* l, RShell* r) //RShell Constructor
	: left(l), right(r), type("&&"), executed(false), exec(true)

	{}

	~And(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if both sides are true
	{
		executed = true;
		if(!left->get_executed())
		{
			right->set_exec(false);
		}
		return executed;
	}

	string get_type()
	{
		return type;
	}
  void set_right_child(RShell* r){this->right = r;}
	RShell* get_left(){return left;}
	RShell* get_right(){return right;}
	virtual string get_input(){return "";}//Prevents abstraction
};

#endif
