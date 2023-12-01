#ifndef CPP_MYCLASS_H
#define CPP_MYCLASS_H

#ifndef MYCLASS_H
#define MYCLASS_H

#include <iostream>

class Currency
{
public:
    std::string name;
    float cost;
    Currency();
    Currency(std::string name, float cost);
    bool operator==(Currency p);
    void info();
    operator char*();
};

#endif


#endif //CPP_MYCLASS_H
