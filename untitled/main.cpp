#include <iostream>
#include "mytemplates.h"
#include "person.h"

using namespace std;

int main()
{
    Container<int> contInt;

    contInt.add(10);
    contInt.add(3);
    contInt.add(8);
    contInt.add(1);
    contInt.add(5);
    contInt.add(2);
    contInt.add(7);
    contInt.info();

    contInt.del();
    contInt.del();
    contInt.info();

    contInt.info();


    Container<Person> contPerson;

    contPerson.add(Person("Ivan", 1984));
    contPerson.add(Person("Petr", 1988));
    contPerson.add(Person("Natasha", 2014));
    contPerson.add(Person("Olga", 2010));
    contPerson.add(Person("Vasily", 2001));
    contPerson.add(Person("Timofey", 1999));
    contPerson.add(Person("Kostya", 2005));
    contPerson.info();

    contPerson.del();
    contPerson.del();
    contPerson.info();

    contPerson.info();

    try
    {
        contInt.add(8);
        contInt.add(1);
        contInt.add(5);
        contInt.add(2);
        contInt.add(7);
        contInt.add(25);
    }
    catch (Full)
    {
        std::cout << "Contaner is full!" << "\n";
    }

    try
    {
        Container<float> contFloat;
        contFloat.add(0.5);
        contFloat.del();
        contFloat.del();
    }
    catch (Empty)
    {
        std::cout << "Contaner is empty!" << "\n";
    }

    try
    {
        Container<float> contFloat;
        contFloat.add(1);
        contFloat.add(2);
        contFloat.add(1000000000000000000);
    }
    catch (Big)
    {
        std::cout << "This value is big!" << "\n";
    }

    return 0;
}

