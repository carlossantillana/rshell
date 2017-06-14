//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __INPUTREDIRECT_H__
#define __INPUTREDIRECT_H__

#include "connector.h"
#include "command.h"
#include "rshell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>

class inputRedirect : public Connector
{
private:
	RShell* left; //Operation left of redirect
	RShell* right; //file right of redirect
	string type; //Sets type of child
	bool executed;//determines if was already executed
	bool exec;// determines whether or not to execute
public:
  inputRedirect() //Default Constructor
	: type("<"), executed(false), exec(true)
	{}
  inputRedirect(RShell* l) //Single RShell Constructor
  : left(l), type("<"), executed(false), exec(true)
  {}
  inputRedirect(RShell* l, RShell* r) //Double RShell Constructor
  : left(l), right(r), type("<"), executed(false), exec(true)
  {}
  ~inputRedirect(){}
  string get_input() //Prevents abstraction, but does nothing
  {
    return "<";
  }
  string get_type() {return type;}//Outputs type string
  bool execute()
  {
		return true;
  }
};

#endif
