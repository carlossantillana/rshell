#include "read.h"
#include<boost/tokenizer.hpp>

using namespace boost;
Read::Read(){}

Read::Read(string i) : input(i) {}

void Read::par(){
    tokenizer<> tok(input);
    for(tokenizer<>::iterator begin=tok.begin(); begin!=tok.end();++begin){
        commandList.push(*begin);
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
