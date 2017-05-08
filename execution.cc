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
  if (commandList.at(0) == NULL || commandList.at(0)->get_type() == "exit")
    return false;
    const int size = commandList.size();
    char ** argv = new char* [size];
  for (unsigned int i=1; i < commandList.size()-1; i++){
    argv[i] = (char*)commandList.at(i)->get_type().c_str();
  }
  argv[commandList.size()-1] = NULL;
  bool ret_val = true;
	pid = fork();
  if (pid == 0){//child
    if (execvp(commandList.at(0)->get_type().c_str(), argv) == -1){
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
string Execution::get_type(){
  return "Execution";
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
