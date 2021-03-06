//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __PARENTHESES_H__
#define __PARENTHESES_H__

#include "rshell.h"
#include "connector.h"
#include "command.h"

class Parentheses : public Connector
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
	string type; //Sets type of child
  string input;
	vector<RShell*> tree;
  vector<RShell*> commandList;
	pid_t pid;
	bool executed;//determines if was already executed
	bool exec;// determines whether or not to execute
public:
	Parentheses();
  Parentheses(string i);
	Parentheses(RShell* l);
	Parentheses(vector<RShell*> c);
	~Parentheses();
	bool execute();
	string get_type();
	virtual string get_input();//tells if left or right parentheses
	void add_command();
	void fill_parentheses();
	void make_tree();
	void set_commands(vector<RShell*> commandList);
	vector<RShell*> get_commands();
	bool get_executed();
	void set_exec(bool e);
};

#endif
