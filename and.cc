#include "and.h"

And::And() {} //Default Constructor

And::And(RShell *l, RShell *r) //Constructor
: left(l), right(r)
{}

bool And::execute() //Returns true if both sides are true
{
  if(left->execute() && right->execute())
  {
    return true;
  }
  else
  {
    return false;
  }
}

string And::get_input()
{
  return "";
}
