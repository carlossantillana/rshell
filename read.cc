#include "read.h"
#include<boost/tokenizer.hpp>
#include "and.h"
#include "or.h"
#include "semicolon.h"
using namespace boost;

Read::Read(): found(false){}

Read::Read(string i) : input(i), found(false){}

void Read::par(){
  RShell* parse;
  string input;
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ","#;");//list of delimiters to check
    tokenizer tokens(input, sep);//parses string to tokens
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
        //Itereates through tokens and puts them into vector
        input = *tok_iter;
        if (input == "#")//Breaks if #
          break;
        else if (input == "&&"){
          And* anding = new And;
          commandList.push_back(anding);
        }
        else if (input == ";"){
          Semicolon* semying = new Semicolon;
          commandList.push_back(semying);
        }
        else if (input == "||"){
          Or* oring = new Or;
          commandList.push_back(oring);
        }
        else {
          if (input == "exit"){//exits while loop if exit is found
            found = true;
          }
          parse->set_input(input);
          commandList.push_back(parse);//pushes string to vector
        }
  }
}

bool Read::get_found(){
  return this->found;
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
