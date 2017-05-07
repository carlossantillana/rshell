#ifndef __COMMAND_H__
#define __COMMAND_H__

#include<String>

class Command: public Execution{
    private:
        string Command
    public:
        Command(string i)
        :Command(i)
        {}
        virtual bool execute();
        virtual string get_input();
}
#endif
