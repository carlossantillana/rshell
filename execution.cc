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
  return ret_val;
}

void Execution::set_commands(vector<RShell*> commandList)
{
  this->commandList = commandList;
}

string Execution::get_input()
{
  return "";
}
string Execution::get_type()
{
  return "Execution";
}
//Converts vect of string ot vect of char pointers
vector<char *> Execution::str_to_char(vector<RShell*> tree)
{
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
  unsigned int i=0, k=1;
  while (i < commandList.size()){
      while(i < commandList.size() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";")
      {
        rightChild.push_back(commandList.at(i));
        i++;
      }
      commandList.erase(commandList.begin(), commandList.begin()+ i);
      if (i < commandList.size()){
        while(k < commandList.size() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";")
        {
          leftChild.push_back(commandList.at(k));
          k++;
        }
        command = commandList.front()->get_type();
        cout << "command " << command << endl;
        commandList.erase(commandList.begin(), commandList.begin()+ k);
    }
       for(unsigned int j=0; j < rightChild.size(); j++){
         cout << "right child at " << j  <<" " << rightChild.at(j)->get_type() << endl;
       }
       for(unsigned int j=0; j < leftChild.size(); j++){
         cout << "left child at " << j  <<" " << leftChild.at(j)->get_type() << endl;
       }
      k=0;
      i=0;
      if (!command.empty()){
        if (command == "&&"){
          execute(rightChild);
          execute(leftChild);
        }
        if (command == "||"){
          if (!execute(rightChild)){
            execute(leftChild);
          }
        }
        if (command == ";"){
          execute(rightChild);
          execute(leftChild);
        }
      }
      else{
        execute(rightChild);
      }
      rightChild.clear();
      leftChild.clear();
      command.clear();
    }
}
