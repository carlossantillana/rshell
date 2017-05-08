#include "execution.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "and.h"
#include "or.h"
#include "semicolon.h"

Execution::Execution(){}

//very basic. only work with one arguement and doesnt handle connectors or arguement
//list yet.
bool Execution::execute()
{
  if (commandList.at(0) == NULL || commandList.at(0)->get_input() == "exit")
    return false;
  char* argv[] = {(char*)commandList.at(0)->get_input().c_str(), NULL};
  bool ret_val = true;
	pid = fork();
  if (pid == 0){//child
    if (execvp((char*)commandList.at(0)->get_input().c_str(), argv) == -1){
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
  this->commandList.push_back(NULL);//used for execvp
}

string Execution::get_input()
{
  return "";
}

/*
=======
>>>>>>> master
void Execution::make_tree(){
  for(unsigned int i=0; i <this->commandList.size(); i++)
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
}
*/
