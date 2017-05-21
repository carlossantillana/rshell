//Copyright 2016 Jonathan Woolf and Carlos Santillana
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

public:
	And() //Default Constructor
	: type("&&")
	{}

	And(RShell* l) //RShell Constructor
	: left(l), type("&&")
	{}
	And(RShell* l, RShell* r) //RShell Constructor
	: left(l), right(r), type("&&")

	{}
	~And(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if both sides are true
	{
		bool exec = false;
		if(left->execute() || right->execute())
		{
			exec = true;
		}
		else
		{
			exec = false;
		}
		return exec;
	}

	string get_type()
	{
		return type;
	}
};

#endif
