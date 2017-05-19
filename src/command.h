//Copyright 2016 Jonathan Woolf and Carlos Santillana
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
class Command: public Connector
{
    private:
        RShell* left; //Operation left of connector
        RShell* right; //Operation right of connector
        string type;// command and arguement list
        vector<RShell*> command;
            pid_t pid;
    public:
      Command(string t) //Constructor reads in command type
      :type(t)
      {}

      Command(string t, vector<RShell*> c) //Constructor reads in command type
      : type(t), command(c)
      {}

      Command(vector<RShell*> c) //Constructor reads in command type
      : type("command"),command(c)
      {}
      Command() //Constructor reads in command type
      : type("command")
      {}
      ~Command(){
      for (vector<RShell* >::iterator iter = command.begin() ; iter != command.end(); ++iter)
      {
        delete (*iter);
      }
      command.clear();
    }
    virtual bool execute() //Returns true if command exists
    {
      bool ret_val= true;
      vector<char *> argv = str_to_char(command);//converts vect of string to vect of char* for execvp
      for (unsigned int i=0; i < argv.size(); i++){
        cout << argv.at(i) << endl;
      }
      argv.push_back(NULL);
      pid = fork();
      if (pid == 0){//child commandList.at(0)->get_type().c_str()
        if (execvp(argv[0], argv.data()) == -1){// runs command
          perror("execvp");
          ret_val = false;
        }
      }
      if (pid > 0){//parent
        if (wait(0) == -1){
          perror("wait");
          ret_val = false;
        }

      }
      //memory management
      for (vector<char* >::iterator iter = argv.begin() ; iter != argv.end(); ++iter)
      {
        delete (*iter);
      }
      argv.clear();
      return ret_val;
    }
    virtual string get_input() //Not really doing much
    {
      return "";
    }
    string get_type() //Returns type for rshell comparisons
    {
      return type;
    }
    void add_command(RShell* r){
      command.push_back(r);
    }
    vector<char *> str_to_char(vector<RShell*> vec){
        vector<char *> vectChar;

        for(unsigned int  i = 0; i < vec.size(); ++i){
            char *tmp;
            tmp = new char[vec[i]->get_type().size() + 1];
            memcpy(tmp, vec[i]->get_type().c_str(), vec[i]->get_type().size() + 1);

            vectChar.push_back(tmp);
        }
        return vectChar;
    }
    RShell* get_left(){return left;}
    RShell* get_right(){return right;}

};

#endif
