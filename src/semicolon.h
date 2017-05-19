//Copyright 2016 Jonathan Woolf and Carlos Santillana
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
