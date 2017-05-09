#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "rshell.h"

class Command: public RShell
{
    private:
        string type; //Ex. ls, ls -a (Don't know what else should work TBH)
    public:
        Command(string i) //Constructor reads in command type
        :type(i)
        {}
        virtual bool execute() //Returns true if command exists
        {
          return true;
        }
        virtual string get_input() //Not really doing much
        {
          return "";
        }
        string get_type() //Returns type for rshell comparisons
        {
          return type;
        }
};

#endif
