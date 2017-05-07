#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector //Conector is the base of operators
{
private:
	RShell *left;
	RShell *right;
public:
	And(); //Defalut Constructor
	And(RShell *l, RShell *r); //RShell Constructor
	bool execute(); //Returns true if both sides are true
	string get_input();
};

#endif
