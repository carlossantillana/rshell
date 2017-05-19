//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __TEST_H__
#define __TEST_H__

#include "rshell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstring>
#include <sys/stat.h>

class Test: public RShell
{
    private:
        string type;// Test and arguement list
        vector<RShell*> commandList;
    public:
        Test() :type("test") {} //Sets string variable to "test"
        ~Test(){}
        void set_commands(vector<RShell*> commandList)
        {
          this->commandList = commandList; //Provides test object with RShell list
        }
        bool execute() //Returns true if Test runs otherwise fails
        {
          for (unsigned i = 0; (i + 1) < commandList.size(); i++)
          {
            if (commandList.at(i)->get_type() == "test")
            {
              if (commandList.at(i+1)->get_type() == "-f")
              {
                return true;
              }
              else if (commandList.at(i+1)->get_type() == "-d")
              {
                return true;
              }
              else
              {
                return true;
              }
            }
          }
          return false;
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
