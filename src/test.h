//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#ifndef __TEST_H__
#define __TEST_H__

#include "rshell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

class Test: public RShell
{
    private:
        vector<RShell*> commandList;
        RShell* child;
        string type; //Returns "type"
        string input; //Returns actual input
        bool e,f,d; //Flags
        bool executed;//determines if was already executed
        bool exec;// determines whether or not to execute
    public:
        Test(string in) : type("test"), input(in), e(false), f(false), d(false), executed(false), exec(true) {}
        Test(RShell* i, string in) :child(i), type("test"), input(in), e(false), f(false), d(false), executed(false), exec(true) {} //Sets string variable to "test"
        ~Test()
        {
          for (vector<RShell* >::iterator iter = commandList.begin(); iter != commandList.end(); ++iter)
          {
            delete (*iter);
          }
          commandList.clear();
        }

        bool execute() //Returns true if Test runs otherwise fails
        {
          this->executed = true;
          commandList = child->get_commandList();
          char* c;
          string test = "test";
          string bracket = "[";
          string eflag = "-e";
          string fflag = "-f";
          string dflag = "-d";
          struct stat sb;
          vector<char *> argv = str_to_char(commandList);//converts vect of string to vect of char*
	        if (argv.size() == 0)
	        {
		          cout << "(False)" << endl;
		          return false;
	        }
          else if (argv.at(0) == test) //If user wrote "test"
	        {
		          if (argv.size() == 3) //If user specified a flag
		          {
			              c = argv.at(2);
			              if (argv.at(1) == eflag)
			              {
				                  e = true;
			              }
			              else if (argv.at(1) == fflag)
			              {
				                  f = true;
			              }
			              else if (argv.at(1) == dflag)
			              {
				                  d = true;
			              }
		          }
		          else if (argv.size() == 2) //Default flag is -e
		          {
			              c = argv.at(1);
			              e = true;
		          }
		          else
		          {
			              cout << "(False)" << endl;
			              return false;
		          }
	        }
          else if(argv.at(0) == bracket) //User input brackets
          {
            if (argv.size() == 4) //User specified a flag
            {
              c = argv.at(2);
              if (argv.at(1) == eflag)
              {
                e = true;
              }
              else if (argv.at(1) == fflag)
                  {
                        f = true;
                  }
                  else if (argv.at(1) == dflag)
                  {
                        d = true;
                  }
             }
             else if (argv.size() == 3) //Default flag is -e
             {
                  c = argv.at(1);
                  e = true;
             }
             else
             {
                  cout << "(False)" << endl;
                  return false;
             }
           }

           stat(c, &sb);

           if (e)
           {
             if (S_ISDIR(sb.st_mode) || S_ISREG(sb.st_mode))
             {
               cout << "(True)\n";
               return executed = true;
             }
           }
           else if (f)
           {
             if (S_ISREG(sb.st_mode))
             {
               cout << "(True)\n";
               return executed = true;
             }
           }
           else if (d)
           {
             if (S_ISDIR(sb.st_mode))
             {
               cout << "(True)\n";
               return executed = true;
             }
           }
           cout << "(False)\n"; //Should still return true signifying that the test happened
           return true;
        }
        string get_type() //Returns type for rshell comparisons
        {
          return type;
        }
        //Converts vect of string ot vect of char pointers
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
        void set_right_child(RShell* r){r->get_type();}
        RShell* get_left(){return commandList.at(0);}
        RShell* get_right(){return commandList.at(0);}
      	string get_input(){return input;}
        bool get_executed() {return this->executed;}
        void set_exec(bool e){this->exec = e;}
};


#endif
