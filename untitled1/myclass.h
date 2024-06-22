#ifndef MYCLASS
#define MYCLASS

#include <iostream>

class Currency
{
public:
    std::string name;
    float cost;
    Currency();
    Currency(std::string name, float cost);
    bool operator==(Currency p);
    bool operator>(Currency p);
    bool operator<(Currency p);
    void info();
    operator char*();
};

#endif
