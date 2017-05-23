//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __PARENTHESES_H__
#define __PARENTHESES_H__

#include "connector.h"

class Parentheses : public Connector
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
	string type; //Sets type of child
  string input;
  bool executed;
  bool executeSuccessful;
public:
	Parentheses()  //Default Constructor
	: type("()"), input(""), executed(false), executeSuccessful(false)
	{}

  Parentheses(string i)  //Default Constructor
  : type("()"), input(i), executed(false), executeSuccessful(false)
  {}

	Parentheses(RShell* l) //Constructor
	: left(l), type("()"), input(""), executed(false), executeSuccessful(false)
	{}
	~Parentheses(){
		delete left;
		delete right;
	}
	bool execute() //Returns true if one argument is true
	{
		if (executed == false){// actually execute, change executeSuccessful depending on if it was or not
      executed = true;
	    return executeSuccessful;
  }
  else{// if already executed simply return if it was sucessful or not
    return executeSuccessful;
  }
	}

	string get_type()
	{
		return type;
	}
	virtual string get_input(){return input;}//tells if left or right parentheses
};

#endif
