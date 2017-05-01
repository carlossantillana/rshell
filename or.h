#ifndef __OR_H__
#define __OR_H__

#include "constructor.h"

class Or : public Connector
{
private: 
	RShell *left;
	RShell *right;
public:
	Or(RShell *l, RShell *r) //Constructor
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
