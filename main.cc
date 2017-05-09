#include "rshell.h"
#include "read.h"

int main()
{
	string input;
	Read* read = new Read;
	Execution* execution = new Execution;
  while(!read->get_found())
  {
  	cout << "$ ";
    getline(cin,input);
		if (!input.empty()){//checks for empty string case
	    read->set_input(input);
	    read->par();
			execution->set_commands(read->get_commands());
			execution->execute();
			read->clear();
	}
	}
		//delete read; need to figure out memory management...
  	return 0;
}
