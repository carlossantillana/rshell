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
#include "test.h"


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

string Execution::get_type()
{
  return "Execution";
}

void Execution::set_commands(vector<RShell*> commandList)
{
  this->commandList = commandList;
}

void Execution::make_tree(){
    vector<RShell*> rightChild;
    vector<RShell*> leftChild;
    string command = "";
  unsigned int i=0, k=1;
  while (i < commandList.size()){
      while(i < commandList.size() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";")
      {//fills left child
        leftChild.push_back(commandList.at(i));
        i++;
      }
      commandList.erase(commandList.begin(), commandList.begin()+ i);
      if (i < commandList.size()){//if i hasnt already iterated through entirerty of list
        while(k < commandList.size() && commandList.at(k)->get_type() != "&&" && commandList.at(k)->get_type() != "||" && commandList.at(k)->get_type() != ";")
        {// if left child had a connector fill right child
          rightChild.push_back(commandList.at(k));
          k++;
        }
        command = commandList.front()->get_type();
        commandList.erase(commandList.begin(), commandList.begin()+ k-1);
      }

      if (!command.empty()){//if connector found run connector
        if (command == "&&"){
          if (execute(leftChild)){
            if(rightChild.at(0)->get_type() == "test"
            || rightChild.at(0)->get_type() == "Test" || rightChild.at(0)->get_type() == "[")
            {
              Test* testing = new Test(rightChild);
              testing->execute();
            }
            else {
              execute(rightChild);
            }
          }
        }
        if (command == "||"){
          if (!execute(leftChild)){
            if(rightChild.at(0)->get_type() == "test"
            || rightChild.at(0)->get_type() == "Test" || rightChild.at(0)->get_type() == "[")
            {
              Test* testing = new Test(rightChild);
              testing->execute();
            }
            else {
              execute(rightChild);
            }
          }
        }
        if (command == ";"){
          execute(leftChild);
          if(rightChild.at(0)->get_type() == "test"
          || rightChild.at(0)->get_type() == "Test" || rightChild.at(0)->get_type() == "[")
          {
            Test* testing = new Test(rightChild);
            testing->execute();
          }
          else {
            execute(rightChild);
          }
        }
      }
      else{
        if(leftChild.at(0)->get_type() == "test"
        || leftChild.at(0)->get_type() == "Test" || leftChild.at(0)->get_type() == "[")
        {
          Test* testing = new Test(leftChild);
          testing->execute();
        }
        execute(leftChild);// if no connector only run left child
      }
      leftChild.clear();//clear all vectors
      rightChild.clear();
      command.clear();
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
