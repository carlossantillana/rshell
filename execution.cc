#include "execution.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
  for(unsigned int i=0; i <this->commandList.size(); i++){
    cout << commandList.at(i) << endl;
  }
}
