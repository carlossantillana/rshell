#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class Semicolon : public Connector
{
private:
	RShell *left;
	RShell *right;
public:
	Semicolon() {} //Defalut Constructor

	Semicolon(RShell *l, RShell *r) //Constructor
	: left(l), right(r)
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
};

#endif
