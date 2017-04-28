#include "rshell.h"
#include "read.h"

int main()
{
    string input;
    while(input != "exit")
    {
        cout << "$ ";
        getline(cin,input);
        if(input != "exit" || input.find_first_of('#') != string::npos) 
        {
            cout << "Testing Read" << endl;
        }
    }
    return 0;
}