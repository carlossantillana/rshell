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
	char buf[20];
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
    this->executed = true;
	right->set_exec(false);
    myPipe = pipe(pipefd);
    if (myPipe == -1){
      perror("pipe");
          this->executed = false;
      exit(1);

    }
    pid = fork();
    if (pid == 0){
		close(pipefd[0]);
		write(pipefd[1], "testing", 7);
		close(pipefd[0]);
		exit(0);
    }
    else {
		printf("Parent Process\n");
		//close(pipefd[0]);
		read(pipefd[0], buf, 15);
		printf("buf: %s\n", buf );
    }
    /*
		bool executed = true;
		if(!left->get_executed())
		{
			right->set_exec(true);
		}
		else
			right->set_exec(false);    */
		return executed;

	}

	string get_type()
	{
		return type;
	}
	virtual string get_input(){return "";}//Prevents abstraction
	void set_right_child(RShell* r){this->right = r;}
};

#endif
