#ifndef __READ_H__
#define __READ_H__

#include "rshell.h"
#include "execute.h"
#include <queue>

class Read: public RShell
{
private:
    string input;
    queue<RShell*> commandList;
public:
    Read(string i);
    void par();
};

#endif