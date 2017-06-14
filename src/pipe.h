//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __PIPE_H__
#define __PIPE_H__

#include "connector.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

class Pipe : public Connector
{
private:
	RShell* left; //Operation left of connector
	RShell* right; //Operation right of connector
	string type; //Sets type of child
	bool executed;//determines if was already executed
	bool exec;// determines whether or not to execute
	pid_t pid;
	int pipefd[2];
	int myPipe;
public:
	Pipe()  //Default Constructor
	: type("|"), executed(false), exec(true)
	{}
	Pipe(RShell* l) //Constructor
	: left(l), type("|"), executed(false), exec(true)
	{}
	~Pipe(){
		delete left;
		delete right;
	}

	bool execute() //Returns true if one argument is true
	{
	cout << "inside pipe\n";
	this->executed = true;
	vector<RShell*> lCommandList = left->get_commandList(), rCommandList = right->get_commandList();
	vector<char *> largv = str_to_char(lCommandList);//converts vect of string to vect of char* for execvp
	vector<char *> rargv = str_to_char(rCommandList);//converts vect of string to vect of char* for execvp
	largv.push_back(NULL);
	rargv.push_back(NULL);
	int pipefd[2];
	   pipe(pipefd);
	   switch (pid = fork()) {

	   	case 0:
	   		dup2(pipefd[1], 1);
	   		close(pipefd[0]);
	   		execvp(largv[0], largv.data());
	   		perror(largv[0]);
			break;

	   	case -1:
	   		perror("fork");
	   		exit(1);
			break;

		default:
			break;
   	}

	switch (pid = fork()) {

	case 0:
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		execvp(rargv[0], rargv.data());
		perror(rargv[0]);
		break;

	case -1:
		perror("fork");
		exit(1);
		break;

	default:
		break;
	}

	close(pipefd[0]); close(pipefd[1]);
   right->set_exec(false);

	return executed;
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
	string get_type()
	{
		return type;
	}
	virtual string get_input(){return "";}//Prevents abstraction
	void set_right_child(RShell* r){this->right = r;}
};

#endif
