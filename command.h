#ifndef __COMMAND_H__
#define __COMMAND_H__

#include<String>

class Command: public Execution{
    private:
        String execute, args, cmd, input;
    public:
        String get_input();
        virtual bool execute();
        virtual string get_input();
};

#endif
