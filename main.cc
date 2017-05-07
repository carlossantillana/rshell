#include "rshell.h"
#include "read.h"

int main()
{
	string input;
		Read* read = new Read;
		Execution* execution = new Execution;
    while(true)
    {
    	cout << "$ ";
      getline(cin,input);
      read->set_input(input);
      read->par();
			if(read->get_found())
			{
				break;
			}
		execution->set_commands(read->get_commands());
		}
		//delete read; need to figure out memory management...
  	return 0;
}
