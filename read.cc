#include "read.h"
#include<boost/tokenizer.hpp>

using namespace boost;
Read::Read(): found(false){}

Read::Read(string i) : input(i), found(false){}

void Read::par(){
  string parse;
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(" ","#;");//list of delimiters to check
    tokenizer tokens(input, sep);//parses string to tokens
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
        //Itereates through tokens and puts them into queue
        parse = *tok_iter;//pases token to string
        if (parse == "#")//Breaks if #
          break;
        else{
          if (parse == "exit"){//exits while loop if exit is found
            found = true;
          }
          commandList.push_back(parse);//pushes string to queue
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
vector<string> Read::get_commands(){
  return commandList;
}
