#include "rshell.h"
#include "read.h"

int main()
{
	string input;
    	Read* read = new Read;
    	while(read->get_found() != true)
    	{
        	cout << "$ ";
        	getline(cin,input);
      		read->set_input(input);
      		read->par();
    	}
	//delete read; need to figure out memory management...
    	return 0;
}
