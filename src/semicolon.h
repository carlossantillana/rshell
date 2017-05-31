//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class Semicolon : public Connector
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
	string type; //Sets type of child
	bool executed;//determines if was already executed
	bool exec;// determines whether or not to execute
public:
	Semicolon() //Defalut Constructor
	: type(";")
	{}

	Semicolon(RShell* l) //Constructor
	: left(l), type(";")
	{}

		~Semicolon(){
			delete left;
			delete right;
		}
	bool execute() //Returns true if one argument is true
	{
		executed = true;
		return exec;
	}

	string get_type()
	{
		return type;
	}
	void set_right_child(RShell* r){this->right = r;}
};

#endif
