//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#include "rshell.h"
#include "read.h"
#include "test.h"

int main()
{
	string input;
	Read* read = new Read;
	Execution* execution = new Execution;
	Test* test = new Test;
  while(!read->get_foundExit())
  {
  	cout << "$ ";
    getline(cin,input);
		if (!input.empty()){//checks for empty string case
	    read->set_input(input);
	    read->par();
			test->set_commands(read->get_commands());
			execution->set_commands(read->get_commands());
			execution->make_tree();
			read->clear();
		}
	}
		delete read;
		delete execution;
  	return 0;
}
