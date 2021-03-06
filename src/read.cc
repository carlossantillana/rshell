//Copyright 2017 Jonathan Woolf and Carlos Santillana
//This program is distributed under the terms of the GNU General Public License

#include "read.h"
#include<boost/tokenizer.hpp>
#include "and.h"
#include "or.h"
#include "semicolon.h"
#include "command.h"
#include "test.h"
#include "parentheses.h"
#include "inputRedirect.h"
#include "singleOutputRedirect.h"
#include "doubleOutputRedirect.h"
#include "pipe.h"

using namespace boost;

Read::Read(): foundExit(false), firstExit(false), foundTest(false), foundParenthesis(false), invalidParentheses(false) {}

Read::Read(string i) : input(i), foundExit(false), firstExit(false), foundTest(false), foundParenthesis(false), invalidParentheses(false) {}

Read::~Read(){
  for (vector<RShell* >::iterator iter = commandList.begin() ; iter != commandList.end(); ++iter)
  {
    delete (*iter);
  }
  commandList.clear();
}

void Read::par(){
  string tmp;
  unsigned int count =0;
  unsigned int leftParenthesesCounter = 0, rightParenthesesCounter = 0;
  unsigned int checkEmpty =0;
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ","#;[]()<");//list of delimiters to check
    tokenizer tokens(input, sep);//parses string to tokens
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
        //Itereates through tokens and puts them into vector
        tmp = *tok_iter;
        if (tmp == "#"){//Breaks if #
          break;
        }
        else if (tmp == "test" || tmp == "Test" || tmp == "["){
          Test* testing = new Test(tmp);
          commandList.push_back(testing);
        }
        else if (tmp == "&&"){
          And* anding = new And;
          commandList.push_back(anding);
        }
        else if (tmp == ";"){
          Semicolon* semying = new Semicolon;
          commandList.push_back(semying);
        }
        else if (tmp == "||"){
          Or* oring = new Or;
          commandList.push_back(oring);
        }
        else if (tmp == "<"){
          inputRedirect* inputting = new inputRedirect;
          commandList.push_back(inputting);
        }
        else if (tmp == ">"){
          singleOutputRedirect* outputting = new singleOutputRedirect;
          commandList.push_back(outputting);
        }
        else if (tmp == ">>"){
          doubleOutputRedirect* outputting1 = new doubleOutputRedirect;
          commandList.push_back(outputting1);
        }
        else if (tmp == "("){
          checkEmpty=0;
          leftParenthesesCounter++;
          Parentheses* parentheses = new Parentheses("left");
          commandList.push_back(parentheses);// pushes back a left parentheses
        }
        else if (tmp == ")"){
          if (checkEmpty == 1){
            break;
          }
          if (count ==0){
            cout << "bash: syntax error near unexpected token )\n";
            break;
          }
          rightParenthesesCounter++;
          Parentheses* parentheses = new Parentheses("right");
          commandList.push_back(parentheses);// pushes back a right parentheses
        }
        else if (tmp == "|"){
          Pipe* piping = new Pipe();
          commandList.push_back(piping);
      }
        else {
          if (tmp == "exit"){
            if (count == 0){
              firstExit = true;
              return;
            }
            foundExit = true;
          }
          Command* parse = new Command(tmp);
          commandList.push_back(parse);//pushes string to vector
        }
        count++;
        checkEmpty++;
  }
  if (leftParenthesesCounter != rightParenthesesCounter){
    invalidParentheses = true;// if invalid number of parentheses return strue
  }
}

bool Read::get_foundExit(){
  return this->foundExit;
}

bool Read::get_firstExit(){
  return this->firstExit;
}
bool Read::get_invalidParentheses(){
  return this->invalidParentheses;
}
bool Read::get_foundTest(){
  return this->foundTest;
}

bool Read::get_foundParenthesis(){
  return this->foundParenthesis;
}

string Read::get_type(){
  return "read";
}
bool Read::execute(){
  return true;
}

void Read::set_input(string input){
  this->input = input;
}
vector<RShell*> Read::get_commands(){
  return commandList;
}
void Read::clear(){
  this->commandList.clear();
}
bool Read::empty(){
  if (this->commandList.empty())
    return true;
  else
    return false;
}
