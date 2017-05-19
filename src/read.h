//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __READ_H__
#define __READ_H__

#include "rshell.h"
#include "execution.h"

class Read: public RShell
{
private:
    string input;
    bool found;
    vector<RShell*> commandList;
public:
    Read();
    Read(string i);
    ~Read();
    void par();
    void set_input(string input);
    bool get_found();
    virtual bool execute();
    virtual string get_input();
    vector<RShell*> get_commands();
    void clear();
    bool empty();
    virtual string get_type();
    virtual void set_right_child(RShell* r){r->get_type();};
    virtual RShell* get_left(){return commandList.at(0);};
    virtual RShell* get_right(){return commandList.at(0);};
};

#endif
