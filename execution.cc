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

void Execution::make_tree()
{
  vector<RShell*> leftChild; //Creates lefthand side vector
  vector<RShell*> rightChild; //Creates righthand side vector
  // while(commandList.size() <= 3 && (commandList.at(f)->get_type() != "&&"
  // && commandList.at(f)->get_type() != "||" && commandList.at(f)->get_type() != ";"))
  // {
  //   rightChild = commandList;
  //   f++;
  //   return;
  // }
  for(unsigned int i = 0; i < commandList.size(); i++)
  {
    //Checks for connector
    if(commandList.at(i)->get_type() == "&&" || commandList.at(i)->get_type() == "||"
    || commandList.at(i)->get_type() == ";")
    {
      if(commandList.at(i)->execute() == true) //If connector's children meet bool conditions
      {
        for(unsigned int j = 0; j < i; j++)
        {
          leftChild.push_back(commandList.at(j)); //Fills lefthand side vector
        }
        commandList.erase(commandList.begin() + i - 1); //Removes used part of commandList
        unsigned int z = 0;
        while(z < commandList.size() && (commandList.at(z)->get_type() != "&&"
        && commandList.at(z)->get_type() != "||" && commandList.at(z)->get_type() != ";"))
        {
          rightChild.push_back(commandList.at(z));
          z++;
        }
        if(z > 0)
        {
          commandList.erase(commandList.begin() + z - 1);
        }
        execute(rightChild);
        make_tree(); //Temporary solution
      }
      else
      {
        break;
      }
    }
  }
  rightChild = commandList;
  execute(rightChild);
}
