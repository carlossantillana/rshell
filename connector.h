#ifndef __CONNECTOR_H__
#define __CONNECTOR_H_

#include "execute.h"

class Connector: public Execute{
    private:
        String connector, input;
    public:
        void get_input();
        void or();
        void and();
        void semiColon();
        void excute();
        void print();
}
#endif