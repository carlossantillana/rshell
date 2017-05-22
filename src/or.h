//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __OR_H__
#define __OR_H__

#include "connector.h"

class Or : public Connector
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
	string type; //Sets type of child
public:
	Or()  //Default Constructor
	: type("||")
	{}
	Or(RShell* l) //Constructor
	: left(l), type("||")
	{}
	~Or(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if one argument is true
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
	virtual string get_input(){return "";}//Prevents abstraction
};

#endif
