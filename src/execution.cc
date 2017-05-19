//Copyright 2016 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#include "execution.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <cstring>
#include "and.h"
#include "or.h"
#include "semicolon.h"

Execution::~Execution() {
    for (vector<RShell* >::iterator iter = commandList.begin() ; iter != commandList.end(); ++iter)
    {
      delete (*iter);
    }
    commandList.clear();
}
bool Execution::execute(vector<RShell*> tree)
{
  if (tree.at(0) == NULL || tree.at(0)->get_type() == "exit")//makes sure exit quits
    return false;

  bool ret_val = true;
  vector<char *> argv = str_to_char(tree);//converts vect of string to vect of char* for execvp
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

void Execution::set_commands(vector<RShell*> commandList)
{
  this->commandList = commandList;
}

string Execution::get_input()
{
  return "";
}
string Execution::get_type()
{
  return "Execution";
}
//Converts vect of string ot vect of char pointers
vector<char *> Execution::str_to_char(vector<RShell*> vec){
    vector<char *> vectChar;

    for(unsigned int  i = 0; i < vec.size(); ++i){
        char *tmp;
        tmp = new char[vec[i]->get_type().size() + 1];
        memcpy(tmp, vec[i]->get_type().c_str(), vec[i]->get_type().size() + 1);

        vectChar.push_back(tmp);
    }
    return vectChar;
}
vector<RShell*>  Execution::prep_tree(){
    //Command* child = new Command;
    vector<RShell*> children;
    vector<RShell*> ordered_connectors;
    unsigned int i=0;

    while (!commandList.empty()){
      //-----------------------------------------------------------------
      cout << "printing entire command list\n";
      for(unsigned int j=0; j < commandList.size(); j++){
        cout <<  j <<": " << commandList.at(j)->get_type() << endl;
      }
      cout << "finished printing command list\n\n";
      //-----------------------------------------------------------------

      bool first = true;
        while(i < commandList.size() && commandList.at(i)->get_type() != "&&" && commandList.at(i)->get_type() != "||" && commandList.at(i)->get_type() != ";")
        {//fills left child
          children.push_back(commandList.at(i));
          i++;
        }
        commandList.erase(commandList.begin(), commandList.begin()+ i);//erases up to connector
          Command* child = new Command(children);
        if (commandList.front()->get_type() == "&&"){
          And* anding = new And(child);
          ordered_connectors.push_back(anding);
        }
        else if(commandList.front()->get_type() != "||"){
          Or* oring = new Or(child);
          ordered_connectors.push_back(oring);
        }
        else if(commandList.front()->get_type() != ";"){
          Semicolon* semying = new Semicolon(child);
          ordered_connectors.push_back(semying);
        }
        else{
            if (first == true)
              child->execute();
            else
              ordered_connectors.at(ordered_connectors.size()-1)->set_right_child(child);
          }
      //  commandList.erase(commandList.begin(), commandList.begin()+ i);
        children.clear();
        delete child;
        commandList.erase(commandList.begin(), commandList.begin()+ 1);//erases up to connector
        first = false;
        //-------------------------------------------------------------
        cout << "printing commands Left \n";
        for(unsigned int j=0; j < commandList.size(); j++){
          cout <<  j <<": " << commandList.at(j)->get_type() << endl;
        }
        cout << "finished printing commandsLeft\n\n";
        //---------------------------
    }
    commandList.clear();//clear all vectors
    return ordered_connectors;
}
void Execution::make_tree(){

    vector<RShell*>  ordered_connectors = prep_tree();
    for (unsigned int i=0; i < ordered_connectors.size(); i++){
      if (ordered_connectors.at(i)->get_type() == "&&" || ordered_connectors.at(i)->get_type() == "||" || ordered_connectors.at(i)->get_type() == ";" ){

        ordered_connectors.at(i)->set_right_child(ordered_connectors.at(i+1));

      }
    }
    tree = ordered_connectors.at(0);
}
