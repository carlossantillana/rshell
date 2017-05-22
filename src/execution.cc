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
bool Execution::execute(vector<RShell*> tree)
{
  if (tree.at(0) == NULL || tree.at(0)->get_type() == "exit")//makes sure exit quits
    return false;

  bool ret_val = true;
  vector<char *> argv = str_to_char(tree);//converts vect of string to vect of char* for execvp
  argv.push_back(NULL);
	pid = fork();
  if (pid == 0){//child commandList.at(0)->get_type().c_str()
    if (execvp(argv[0], argv.data()) == -1){// runs command
      perror("execvp");
      ret_val = false;
    }
  }
  if (pid > 0){//parent
    if (wait(0) == -1){
      perror("wait");
      ret_val = false;
    }

  }
  //memory management
  for (vector<char* >::iterator iter = argv.begin() ; iter != argv.end(); ++iter)
  {
    delete (*iter);
  }
  argv.clear();
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
vector<char *> Execution::str_to_char(vector<RShell*> tree){
    vector<char *> vectChar;

    for(unsigned int  i = 0; i < tree.size(); ++i){
        char *tmp;
        tmp = new char[tree[i]->get_type().size() + 1];
        memcpy(tmp, tree[i]->get_type().c_str(), tree[i]->get_type().size() + 1);

        vectChar.push_back(tmp);
    }
    return vectChar;
}


void Execution::make_tree(){
    vector<RShell*> rightChild;
    vector<RShell*> leftChild;
    string command = "";
    //---------------------------
    //cout << "printing entire tree\n";
    //for(unsigned int j=0; j < commandList.size(); j++){
    //  cout <<  j <<": " << commandList.at(j)->get_type() << endl;
    //}
    //cout << "finished printing entire tree\n\n";
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
      //---------------------------
      // cout << "printing left child\n";
      // for(unsigned int j=0; j < leftChild.size(); j++){
      //  cout <<  j <<": " << leftChild.at(j)->get_type() << endl;
      // }
      // cout << "finished printing left child\n\n";

      //cout << "printing right child\n";
      //for(unsigned int j=0; j < rightChild.size(); j++){
      //  cout <<  j <<": " << rightChild.at(j)->get_type() << endl;
      //}
      //cout << "finished printing right child\n\n";
      //---------------------------
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
}
