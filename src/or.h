//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __OR_H__
#define __OR_H__

#include "connector.h"

class Or : public Connector
{
private:
	RShell *left;
	RShell *right;
	string type;
public:
	Or()  //Default Constructor
	: type("||")
	{}
	Or(RShell *l, RShell *r) //Constructor
	: left(l), right(r), type("||")
	{}
	~Or(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if one argument is true
	{
		if(left->execute() || right->execute())
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
