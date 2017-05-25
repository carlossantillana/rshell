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
void Parentheses::fill_parentheses(){//fills up Parentheses with commands
  vector<RShell*> children;
  unsigned int leftParenthesesCounter = 0;//probably auto initalize to zero
  unsigned int rightParenthesesCounter = 0;//used to check if parenthese is done
  //unsigned int num_commands_used =0;probably use later if execute duplicates
  // if leftParenthesesCounter.at (1) == 1 then left parenthese found; else not found or already closed.
  unsigned int i=0;
  bool firstCommand = true;
  cout << "first element in fill parenthese " << commandList.front()->get_type()  << " erasing now"<< endl;
  commandList.erase(commandList.begin(), commandList.begin() + 1);//removes first connector which is probably "("
  cout << " new first element in fill parenthese " << commandList.front()->get_type() << endl;
  while (commandList.front()->get_input() != "right"){
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
      else if(commandList.front()->get_type() == "()" && commandList.front()->get_input() == "left"){
        leftParenthesesCounter++;
        Parentheses* parentheses = new Parentheses(commandList);
        parentheses->fill_parentheses();
        commandList = parentheses->get_commands();//updates command list
        tree.push_back(parentheses);
      }
      else if(commandList.front()->get_type() == "()" && commandList.front()->get_input() == "right"){//probably not going to need this
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
  make_tree();
  execute(tree);
}

void Parentheses::make_tree(){
  cout << "entering make tree\n";
    if (tree.size() > 0){//attaches right children to tree
      for (unsigned int i=0; i < tree.size()-1 ; i++){
        if (tree.at(i)->get_type() == "&&" || tree.at(i)->get_type() == "||" || tree.at(i)->get_type() == ";" || tree.at(i)->get_type() == "()" ){
          tree.at(i)->set_right_child(tree.at(i+1));
        }
      }
  }
}

void Parentheses::set_commands(vector<RShell*> commandList){this->commandList = commandList;}

vector<RShell*> Parentheses::get_commands(){return this->commandList;}

bool Parentheses::execute(vector<RShell*> tree)
{
  if (tree.size() == 0)//allows for single command
    return executed = false;

  if (tree.at(0) != NULL)
    executed = tree.at(0)->execute();//executes tree
  return executed;
}
