#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "execution.h"

class Command: public Execution
{
    private:
        string type;
    public:
        Command(string i)
        :type(i)
        {}
        virtual bool execute()
        {
          return true;
        }
        virtual string get_input()
        {
          return "";
        }
        string get_type()
        {
          return type;
        }
};

#endif
