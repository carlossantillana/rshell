#include "read.h"
#include<boost/tokenizer.hpp>

using namespace boost;
Read::Read(){}

Read::Read(string i) : input(i) {}

void Read::par(){
  string parse;
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(";", "#");//list of delimiters to check
    tokenizer tokens(input, sep);//parses string to tokens
    for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter){
        //Itereates through tokens and puts them into queue
        parse = *tok_iter;
        if (parse == "#")
          break;
        else{
          commandList.push(*tok_iter);
          while (!commandList.empty()){
            cout << commandList.front() << endl;
            commandList.pop();
          }
        }
  }
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
