#include "myclass.h"
#include <sstream>

Currency::Currency()
{
    name = "NO NAME";
    cost = 1000;
}

Currency::Currency(std::string name, float cost)
{
    this->name = name;
    this->cost = cost;
}

bool Currency::operator ==(Currency p)
{
    return (this->cost == p.cost);
}
bool Currency::operator >(Currency p)
{
    return (this->cost > p.cost);
}
bool Currency::operator <(Currency p)
{
    return (this->cost < p.cost);
}

void Currency::info()
{
    std::cout << name << "\t" << cost << "\n";
}

Currency::operator char *() // оператор преобразования в char* нужен для возможности вывода с помощью cout
{
    std::stringstream result;
    result << name << " " << cost;
    return (char*)result.str().c_str();
}