#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class Semicolon : public Connector
{
private:
	RShell *left;
	RShell *right;
	string type;
public:
	Semicolon() //Defalut Constructor
	: type(";")
	{}

	Semicolon(RShell *l, RShell *r) //Constructor
	: left(l), right(r), type(";")
	{}

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
