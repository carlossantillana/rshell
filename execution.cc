#include "execution.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "and.h"
//#include "or.h"
//#include "semicolon.h"

Execution::Execution(){}

bool Execution::execute()// not done yet
{

  bool ret_val = true;
	pid = fork();
  if (pid == 0){//child
/*    if (execvp(insert command list here) == -1)
    {
      perror("execvp");
    }
*/
  }
  if (pid > 0){//parent
    if (wait(0) == -1){
    //  perror("wait");
    }
  }
  return ret_val;
}

void Execution::set_commands(vector<string> commandList){
  this->commandList = commandList;
}


string Execution::get_input(){
  return "";
}

void Execution::print(){}

void Execution::make_tree(){
  for(unsigned int i=0; i <this->commandList.size(); i++){
    string currentCommand = commandList.at(i);
    if (currentCommand == "&&" ){
      //do work
      And anding = new And();
    }
    else if (currentCommand == "||"){
      //do work
      //Or oring = new Or;
    }
    else if (currentCommand == ";"){
      //do work
    //Semicolon semicolon = new Semicolon;
    }
    else{
      //do something else

    }

   }
}
