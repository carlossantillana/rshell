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

Execution::Execution(){}

bool Execution::execute()
{
  if (commandList.at(0) == NULL || commandList.at(0)->get_type() == "exit")//makes sure exit quits
    return false;
  bool ret_val = true;
  vector<char *> argv = str_to_char();//converts vect of string to vect of char* for execvp
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
string Execution::get_type(){
  return "Execution";
}
//Converts vect of string ot vect of char pointers
vector<char *> Execution::str_to_char()
{
    vector<char *> vectChar;

    for(unsigned int  i = 0; i < commandList.size(); ++i){
        char *tmp;
        tmp = new char[commandList[i]->get_type().size() + 1];
        memcpy(tmp, commandList[i]->get_type().c_str(), commandList[i]->get_type().size() + 1);

        vectChar.push_back(tmp);
    }
    return vectChar;
}

vector<RShell*> Execution::make_tree()
{
  vector<RShell*> tree;
  /*for(unsigned int i=0; i <this->commandList.size(); i++)
  {
    string currentCommand = commandList.at(i);
    if (currentCommand == "&&" )
    {
      //do work
      And* anding = new And;
      anding->execute();
    }
    else if (currentCommand == "||")
    {
      //do work
      Or* oring = new Or;
      oring->execute();
    }
    else if (currentCommand == ";")
    {
      //do work
      Semicolon* semying = new Semicolon;
      semying->execute();
    }
    else
    {
      //do something else

    }
  }
  */
  return  tree;
}
