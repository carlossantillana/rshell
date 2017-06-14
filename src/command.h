//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __COMMAND_H__
#define __COMMAND_H__


#include "connector.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstring>
#include "test.h"
class Command: public Connector
{
    private:
        RShell* left; //Operation left of connector
        RShell* right; //Operation right of connector
        string type;// command and arguement list
        string input;// type of command for parsing
        vector<RShell*> command;
        pid_t pid;
        bool executed;//determines if was already executed
        bool exec;// determines whether or not to execute
    public:
      Command() //Constructor reads in command type
      : type("command"), executed(false), exec(true)
      {}
      Command(string i) //Constructor reads in string type
      : type("command"), input(i), executed(false), exec(true)
      {}

      Command(vector<RShell*> c) //Constructor reads in command type
      : type("command"), command(c), executed(false), exec(true)
      {}

        Command(vector<RShell*> c, RShell* parent) //Constructor reads in command type
        : left(parent), type("command"), command(c), executed(false), exec(true)
        {}
      ~Command()
      {
        for (vector<RShell* >::iterator iter = command.begin() ; iter != command.end(); ++iter)
        {
          delete (*iter);
        }
        command.clear();
        delete left;
        delete right;
      }
    virtual bool execute() //Returns true if command exists
    {
      this->executed = true;
      if (command.at(0)->get_input() == "exit"){
        return executed = false;
      }
      if (exec == true){
        if(command.at(0)->get_type() == "test"){
            Test* testing = new Test(this, "test");
            testing->execute();
            this->executed = testing->get_executed();
            return executed;
        }

        vector<char *> argv = str_to_char(command);//converts vect of string to vect of char* for execvp
        argv.push_back(NULL);
        pid = fork();
        if (pid == 0){
          if (execvp(argv[0], argv.data()) == -1){// runs command
            perror("execvp");
            this->executed = false;
            exit(1);
          }
        }
        if (pid > 0){//parent
          if (wait(0) == -1){
            perror("wait");
            this->executed = false;
            exit(1);
          }
        }
        //memory management
        for (vector<char* >::iterator iter = argv.begin() ; iter != argv.end(); ++iter)
        {
          delete (*iter);
        }
        argv.clear();
      }
      return executed;
    }
    virtual string get_input() //Returns input for read par
    {
      return input;
    }
    string get_type() //Returns type for rshell comparisons
    {
      return type;
    }
    void print_commands() //Returns type for rshell comparisons
    {
      for(unsigned int i=0; i < command.size(); i++){
          cout << command.at(i)->get_input() << endl;
      }
    }
    void add_command(RShell* r){
      command.push_back(r);
    }
    vector<RShell*> get_commandList(){
      return command;
    }
    vector<char *> str_to_char(vector<RShell*> vec){
        vector<char *> vectChar;

        for(unsigned int  i = 0; i < vec.size(); ++i){
            char *tmp;
            tmp = new char[vec[i]->get_input().size() + 1];
            memcpy(tmp, vec[i]->get_input().c_str(), vec[i]->get_input().size() + 1);

            vectChar.push_back(tmp);
        }
        return vectChar;
    }
    RShell* get_left(){return left;}
    RShell* get_right(){return right;}
    bool get_executed() {return this->executed;}
    void set_exec(bool e){this->exec = e;}
};

#endif
