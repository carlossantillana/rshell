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

Parentheses::Parentheses()  //Default Constructor
: type("()"), input(""), executed(false), executeSuccessful(false)
{}

Parentheses::Parentheses(string i)  //Default Constructor
: type("()"), input(i), executed(false), executeSuccessful(false)
{}

Parentheses::Parentheses(RShell* l) //Constructor
: left(l), type("()"), input(""), executed(false), executeSuccessful(false)
{}

Parentheses::Parentheses(vector<RShell*> c) //Constructor
:type("()"), input(""), executed(false), executeSuccessful(false), commandList(c)
{}

Parentheses::~Parentheses(){
	delete left;
	delete right;
}
bool Parentheses::execute() //Returns true if one argument is true
{
	if (executed == false){// actually execute, change executeSuccessful depending on if it was or not
    executed = true;
    return executeSuccessful;
  }
  else{// if already executed simply return if it was sucessful or not
    return executeSuccessful;
  }
}

string Parentheses::get_type() {return type;}
string Parentheses::get_input(){return input;}//tells if left or right parentheses

void Parentheses::add_command(){}

// note does not work yet!
void Parentheses::fill_parentheses(){//fills up Parentheses with commands, figure out execute...
  vector<RShell*> children;
  unsigned int leftParenthesesCounter = 0;//probably auto initalize to zero
  unsigned int rightParenthesesCounter = 0;//used to check if parenthese is done
  // if leftParenthesesCounter.at (1) == 1 then left parenthese found; else not found or already closed.
  unsigned int i=0;
  bool firstCommand = true;
  while (commandList.front()->get_input() != ")"){
      while(i < commandList.size() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";"  && commandList.at(i)->get_type() != "()")
      {//fills left child
        children.push_back(commandList.at(i));
        i++;
      }
      commandList.erase(commandList.begin(), commandList.begin()+ i);//erases up to connector
      i=0;
      RShell* child = new Command(children);//makes Rshell command object to put into connector
      if (commandList.front()->get_type() == "&&"){
        And* anding = new And(child);
        tree.push_back(anding);
      }
      else if(commandList.front()->get_type() == "||"){
        Or* oring = new Or(child);
        tree.push_back(oring);
      }
      else if(commandList.front()->get_type() == ";"){
        Semicolon* semying = new Semicolon(child);
        tree.push_back(semying);
      }
      //we can safely assume all parentheses have matching pair by now.
      else if(commandList.front()->get_type() == "()" && commandList.front()->get_input() == "("){
        leftParenthesesCounter++;
        Parentheses* parentheses = new Parentheses();
        parentheses->fill_parentheses();
        tree.push_back(parentheses);
      }
      else if(commandList.front()->get_type() == "()" && commandList.front()->get_input() == ")"){//probably not going to need this
        rightParenthesesCounter++;
      }
      else{
          //if only one input simply execute
          if (firstCommand == true){
            child->execute();
          }
          else{
            //if there is a hanging command, set it the last connector's right child
            tree.at(tree.size()-1)->set_right_child(child);
          }
        }
      children.clear();
      if (commandList.size() > 1 )
        commandList.erase(commandList.begin(), commandList.begin() + 1);//erases up to connector
      firstCommand = false;
  }
  commandList.clear();//clear all vectors
}

void Parentheses::set_commands(vector<RShell*> commandList){this->commandList = commandList;}

vector<RShell*> Parentheses::get_commands(){return this->commandList;}
