#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector //Conector is the base of operators
{
private:
	RShell *left;
	RShell *right;
public:
	And(RShell *l, RShell *r); //Constructor
	bool execute(); //Returns true if both sides are true

#endif
