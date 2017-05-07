#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class SemiColon : public Connector
{
private:
	RShell *left;
	RShell *right;
public:
	SemiColon(RShell *l, RShell *r) //Constructor
	: left(l}, right(r)
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
