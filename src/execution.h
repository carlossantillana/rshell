//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include "rshell.h"
#include "command.h"
class Command;

class Execution: public RShell
{
private:
    vector<RShell*> commandList;
    RShell* tree;
    pid_t pid;
public:
    Execution(){}
    ~Execution();
    bool execute(){return true;}
    bool execute(vector<RShell*> tree);
    string get_input();
    void set_commands(vector<RShell*> commandList);
    vector<RShell*>  prep_tree();
    void make_tree();
    virtual string get_type();
    vector<char *> str_to_char(vector<RShell*> tree);
    virtual void set_right_child(RShell* r){r->get_type();};
};

#endif
