#include "and.h"
And(RShell *l, RShell *r) //Constructor
{
  this->left=l;
  this->right=r;
}
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
};
