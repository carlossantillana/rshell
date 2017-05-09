#include "read.h"
#include<boost/tokenizer.hpp>
#include "and.h"
#include "or.h"
#include "semicolon.h"
#include "command.h"
using namespace boost;

Read::Read(): found(false){}

Read::Read(string i) : input(i), found(false){}

void Read::par(){
  string tmp;
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ","#;");//list of delimiters to check
    tokenizer tokens(input, sep);//parses string to tokens
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
        //Itereates through tokens and puts them into vector
        tmp = *tok_iter;
        if (tmp == "#"){//Breaks if #
          break;
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
        else {
          if (tmp == "exit"){
            found = true;
          }
          Command* parse = new Command(tmp);
          commandList.push_back(parse);//pushes string to vector
        }
  }

}

bool Read::get_found(){
  return this->found;
}
string Read::get_type(){
  return "read";
}
bool Read::execute(){
  return true;
}

string Read::get_input(){
  return input;
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
