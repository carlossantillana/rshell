//Copyright 2016 Jonathan Woolf and Carlos Santillana
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
        string type;// Test and arguement list
        bool e,f,d;
    public:
        Test() : type("test"), e(false), f(false), d(false) {}
        Test(vector<RShell*> i) :commandList(i), type("test"), e(false), f(false), d(false) {} //Sets string variable to "test"
        ~Test(){}
        void set_commands(vector<RShell*> commandList)
        {
          this->commandList = commandList; //Provides test object with RShell list
        }
        bool execute() //Returns true if Test runs otherwise fails
        {
          char* c;
          string test = "test";
          string bracket = "[";
          string eflag = "-e";
          string fflag = "-f";
          string dflag = "-d";
          struct stat sb;
          vector<char *> argv = str_to_char(commandList);//converts vect of string to vect of char*
          //Base case
          // cout << "\n" << argv.size() << endl << endl;
          // for (unsigned int i = 0; i < argv.size(); i++)
          // {
          //   cout << argv.at(i) << endl;
          // }
          //cout << endl;
	         if (argv.size() == 0)
	         {
		           cout << "(False)" << endl;
		           return false;
	         }
           else if (argv.at(0) == test)
	         {
		           if (argv.size() == 3)
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
		           else if (argv.size() == 2)
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
           else if(argv.at(0) == bracket)
           {
             if (argv.size() == 4)
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
             else if (argv.size() == 3)
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
               return true;
             }
           }
           else if (f)
           {
             if (S_ISREG(sb.st_mode))
             {
               cout << "(True)\n";
               return true;
             }
           }
           else if (d)
           {
             if (S_ISDIR(sb.st_mode))
             {
               cout << "(True)\n";
               return true;
             }
           }
           cout << "(False)\n";
           return false;
        }
        string get_type() //Returns type for rshell comparisons
        {
          return type;
        }
        //Converts vect of string ot vect of char pointers
        vector<char *> str_to_char(vector<RShell*> commandList){
            vector<char *> vectChar;

            for(unsigned int  i = 0; i < commandList.size(); ++i){
                char *tmp;
                tmp = new char[commandList[i]->get_type().size() + 1];
                memcpy(tmp, commandList[i]->get_type().c_str(), commandList[i]->get_type().size() + 1);

                vectChar.push_back(tmp);
            }
            return vectChar;
        }
};

#endif
