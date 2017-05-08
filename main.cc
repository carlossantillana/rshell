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
			cout << input << endl;
      read->set_input(input);
      read->par();
			if (!read->get_found()){// if exit was found dont execute..probably change later
				cout << "inner if\n";
				execution->set_commands(read->get_commands());
				execution->execute();
				read->clear();
			}
		}

		//delete read; need to figure out memory management...
  	return 0;
}
