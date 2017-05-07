#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>

class Command: public Execution{
    private:
        string command;
    public:
        Command(string i)
        :command(i)
        {}
        virtual bool execute()
        {return true;};
        virtual string get_input()
        {return command;};
};

#endif
