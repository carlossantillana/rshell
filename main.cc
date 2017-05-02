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
      		cout << "Testing Read" << endl;
      		read->set_input(input);
      		read->par();
    	}
    	//Make # a dilimeter and remove the pound condition from while loop
	//delete read; need to figure out memory management...
    	return 0;
}
