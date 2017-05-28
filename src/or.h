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
	bool executed;//determines if was already executed
	bool exec;// determines whether or not to execute
public:
	Or()  //Default Constructor
	: type("||"), executed(false), exec(true)
	{}
	Or(RShell* l) //Constructor
	: left(l), type("||"), executed(false), exec(true)
	{}
	~Or(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if one argument is true
	{
		bool executed = true;
		cout << "left executed = " << left->get_executed() << endl;
		if(!left->get_executed())
		{
			right->set_exec(true);
		}
		else
			right->set_exec(false);
		return executed;
	}

	string get_type()
	{
		return type;
	}
	virtual string get_input(){return "";}//Prevents abstraction
	void set_right_child(RShell* r){this->right = r;}
};

#endif
