//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector //Conector is the base of operators
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
<<<<<<< HEAD
	string type; //Sets type of connector
=======
	string type; //Sets type of child

>>>>>>> 3b84fc71a49e1e0293eb17fabd0ee7abc945a78f
public:
	And() //Default Constructor
	: type("&&")
	{}
<<<<<<< HEAD
	And(RShell* l, RShell* r) //RShell Constructor for two children
	: left(l), right(r), type("&&")
	{}
	And(RShell* l) //RShell Constructor for one child
=======

	And(RShell* l) //RShell Constructor
>>>>>>> 3b84fc71a49e1e0293eb17fabd0ee7abc945a78f
	: left(l), type("&&")
	{}

	And(RShell* l, RShell* r) //RShell Constructor
	: left(l), right(r), type("&&")

	{}

	~And(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if both sides are true
	{
		bool exec = false;
		if(left->execute() && right->execute())
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
  virtual void set_right_child(RShell* r){this->right = r;}
	RShell* get_left(){return left;}
	RShell* get_right(){return right;}
	virtual string get_input(){return "";}//Prevents abstraction
};

#endif
