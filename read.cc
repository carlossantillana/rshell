#include "read.h"
#include<boost/tokenizer.hpp>

using namespace boost;

Read::Read(string i)
: input(i)
{}

void Read::par(){
    tokenizer<> tok(input);
    for(tokenizer<>::iterator begin=tok.begin(); begin!=tok.end();++begin){    
        
    }
}