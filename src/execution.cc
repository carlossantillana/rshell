//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

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
#include "parentheses.h"
#include "test.h"


Execution::~Execution() {
    for (vector<RShell* >::iterator iter = commandList.begin() ; iter != commandList.end(); ++iter)
    {
      delete (*iter);
    }
    commandList.clear();

    for (vector<RShell* >::iterator iter = tree.begin() ; iter != tree.end(); ++iter)
    {
      delete (*iter);
    }
    tree.clear();
}

bool Execution::execute(){return execute(tree);}

bool Execution::execute(vector<RShell*> tree)
{
  if (tree.size() == 0)//allows for single command
  {
    return false;
  }
  bool ret_val = true;

  for (unsigned int i =0; i < tree.size(); i++){
    ret_val = tree.at(i)->execute();//executes tree
  }
  return ret_val;
}


void Execution::set_commands(vector<RShell*> commandList){this->commandList = commandList;}

vector<RShell*> Execution::get_commands(){return this->commandList;}

string Execution::get_type(){return "Execution";}

//Converts vect of string ot vect of char pointers
vector<char *> Execution::str_to_char(vector<RShell*> vec){
    vector<char *> vectChar;

    for(unsigned int  i = 0; i < vec.size(); ++i){
        char *tmp;
        tmp = new char[vec[i]->get_type().size() + 1];
        memcpy(tmp, vec[i]->get_type().c_str(), vec[i]->get_type().size() + 1);
        vectChar.push_back(tmp);
    }
    return vectChar;
}
void  Execution::prep_tree(){
    vector<RShell*> children;
    RShell* child;
    unsigned int i=0;
    bool firstCommand = true;

    while (!commandList.empty()){
        while(i < commandList.size() && !commandList.empty() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";" && commandList.at(i)->get_type() != "()")

        {//fills left child
          children.push_back(commandList.at(i));
          i++;
        }
        commandList.erase(commandList.begin(), commandList.begin()+ i);//erases up to but not including connector
        i=0;
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
        if (commandList.size() >= 1 ){//probably going to run into issue with parentheses here.
          commandList.erase(commandList.begin(), commandList.begin() + 1);//erases connector
        }
        firstCommand = false;
    }
    commandList.clear();//clear all vectors
}

void Execution::make_tree(){
    prep_tree();// prepares tree
    if (tree.size() > 0){//attaches right children to tree
      for (unsigned int i=0; i < tree.size()-1 ; i++){
          tree.at(i)->set_right_child(tree.at(i+1));
      }
    }
}

void Execution::clear(){
  commandList.clear();
  tree.clear();
}
