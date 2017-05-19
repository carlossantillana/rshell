//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "rshell.h"

class Command: public RShell
{
    private:
        string type;// command and arguement list
    public:
        Command(string i) //Constructor reads in command type
        :type(i)
        {}
        ~Command(){}
        virtual bool execute() //Returns true if command exists
        {
          return true;
        }
        string get_type() //Returns type for rshell comparisons
        {
          return type;
        }
};

#endif
