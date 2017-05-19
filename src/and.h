//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector //Conector is the base of operators
{
private:
	RShell* left;
	RShell* right;
	string type;
public:
	And() //Default Constructor
	: type("&&")
	{}

	And(RShell* l, RShell* r) //RShell Constructor
	: left(l), right(r), type("&&")
	{}

	bool execute() //Returns true if both sides are true
	{
		if(left->execute() && right->execute())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string get_type()
	{
		return type;
	}
};

#endif
