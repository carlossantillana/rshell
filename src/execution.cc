//Copyright 2016 Jonathan Woolf and Carlos Santillana
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


Execution::~Execution() {
    for (vector<RShell* >::iterator iter = commandList.begin() ; iter != commandList.end(); ++iter)
    {
      delete (*iter);
    }
    commandList.clear();
}

bool Execution::execute(){
  return execute(tree);
}

bool Execution::execute(vector<RShell*> tree)
{
  if (tree.at(0) == NULL)//prevents empty input
    return false;
  bool ret_val = true;
  ret_val = tree.at(0)->execute();//executes tree
  return ret_val;
}


void Execution::set_commands(vector<RShell*> commandList)
{
  this->commandList = commandList;
}

string Execution::get_type()
{
  return "Execution";
}

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
vector<RShell*>  Execution::prep_tree(){
    vector<RShell*> children;
    unsigned int i=0;
    bool firstCommand = true;
    while (!commandList.empty()){
        while(i < commandList.size() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";")
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
    return tree;
}
void Execution::make_tree(){
    vector<RShell*>  tree = prep_tree();// prepares tree
    if (tree.size() > 0){//attaches right children to tree
      for (unsigned int i=0; i < tree.size()-1 ; i++){
        if (tree.at(i)->get_type() == "&&" || tree.at(i)->get_type() == "||" || tree.at(i)->get_type() == ";" ){
          tree.at(i)->set_right_child(tree.at(i+1));
        }
      }
  }
}
