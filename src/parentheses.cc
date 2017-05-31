//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#include "parentheses.h"
#include "execution.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstring>
#include "and.h"
#include "or.h"
#include "semicolon.h"
#include "test.h"

Parentheses::Parentheses()  //Default Constructor
: type("()"), input(""), executed(false), exec(true)
{}

Parentheses::Parentheses(string i)  //Default Constructor
: type("()"), input(i), executed(false), exec(true)
{}

Parentheses::Parentheses(RShell* l) //Constructor
: left(l), type("()"), input(""), executed(false), exec(true)
{}

Parentheses::Parentheses(vector<RShell*> c) //Constructor
:type("()"), input(""), commandList(c), executed(false), exec(true)
{}

Parentheses::~Parentheses(){
	delete left;
	delete right;
}
bool Parentheses::execute() //Returns true if one argument is true
{
	executed = true;
  if (tree.size() == 0)//allows for single command
  {
    return executed = false;
  }
	if (exec == true){
  bool ret_val = true;
  for (unsigned int i =0; i < tree.size(); i++){
    ret_val = tree.at(i)->execute();//executes tree
		if (ret_val == false){
			executed = false;
		}
  }
}
  return executed;
}

string Parentheses::get_type() {return type;}

string Parentheses::get_input(){return input;}//tells if left or right parentheses

void Parentheses::add_command(){}

// note does not work yet!
void Parentheses::fill_parentheses(){//fills up Parentheses with commands
  vector<RShell*> children;
  RShell* child;
  unsigned int j = 0;
  bool firstCommand = true;
  this->commandList.erase(commandList.begin(), commandList.begin() + 1);//removes first connector which is probably "("
  while (commandList.front()->get_input() != "right" && !commandList.empty()){
      while(j < commandList.size() && commandList.at(j)->get_type() != "&&" && commandList.at(j)->get_type() != "||" && commandList.at(j)->get_type() != ";"  && commandList.at(j)->get_type() != "()")
      {//fills left child
        children.push_back(commandList.at(j));
        j++;
      }
      this->commandList.erase(commandList.begin(), commandList.begin()+ j);//erases up to connector
      j=0;
			if (!children.empty()){
				if (firstCommand)
					child = new Command(children);
				else
					child = new Command(children, tree.back());//makes Rshell command object to put into connector

				tree.push_back(child);
		}
		if (commandList.front()->get_type() == "&&"){
				And* anding = new And(tree.back());
				tree.push_back(anding);
		}
		else if(commandList.front()->get_type() == "||"){
					Or* oring = new Or(tree.back());
					tree.push_back(oring);
		}
		else if(commandList.front()->get_type() == ";"){
				Semicolon* semying = new Semicolon(tree.back());
				tree.push_back(semying);
		}
		//we can safely assume all parentheses have matching pair by now.
		else if(commandList.front()->get_type() == "()" && commandList.front()->get_input() == "left"){
			Parentheses* parentheses = new Parentheses(commandList);
			parentheses->fill_parentheses();
			commandList = parentheses->get_commands();//updates command list
			tree.push_back(parentheses);
		}
      children.clear();
      if (commandList.size() >= 1 && commandList.front()->get_input() != "right")
        commandList.erase(commandList.begin(), commandList.begin() + 1);//erases up to connector
      firstCommand = false;
  }
  make_tree();
}

void Parentheses::make_tree(){
	if (tree.size() > 0){//attaches right children to tree
		for (unsigned int i=0; i < tree.size()-1 ; i++){
				tree.at(i)->set_right_child(tree.at(i+1));
		}
	}
}

void Parentheses::set_commands(vector<RShell*> commandList){this->commandList = commandList;}
vector<RShell*> Parentheses::get_commands(){return this->commandList;}
bool Parentheses::get_executed() {return this->executed;}
void Parentheses::set_exec(bool e){this->exec = e;}
