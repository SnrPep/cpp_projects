#include <iostream>
#include "myclass.h"
#include "class.h"

int main() {
    Container<int> intContainer;
    intContainer.add(1);
    intContainer.add(2);
    intContainer.add(4);
    intContainer.add(3);
    intContainer.add(5);
    intContainer.add(6);
    intContainer.add(7);

    intContainer.info();

    Container<Currency> contCurrency;
    contCurrency.add(Currency("Dollar", 97.14));
    contCurrency.add(Currency("Euro", 102.75));
    contCurrency.add(Currency("Yuan", 13.29));
    contCurrency.add(Currency("Bitcoin", 36557.86));
    contCurrency.info();

    cout << "Int Container ->: " << endl;
    int count = 0;
    int a = INT_MAX;
    for(Container<int>::iterator it = intContainer.begin(); count != 15; ++it, count++){
        if (a < *it)
        {
            continue;
        }
        else
        {
            a = *it;
            cout << *it << " ";
        }
    }
    cout << endl;
    cout << "Int Container <-: " << endl;
    count = 0;
    a = INT_MAX;
    for(Container<int>::iterator it = intContainer.end(); count != 15; --it, count++){
        if (a < *it)
        {
            continue;
        }
        else
        {
            a = *it;
            cout << *it << " ";
        }
    }
    cout << endl;

    cout << "Currency Container ->: ";
    cout << endl;
    count = 0;
    Currency b("a", INT_MAX);
    for(Container<Currency>::iterator it = contCurrency.begin(); count != 15; ++it, count++){
        if (b < *it)
        {
            continue;
        }
        else
        {
            b = *it;
            cout << *it << " ";
        }
    }
    cout << endl;
    cout << "Currency Container <-: ";
    cout << endl;
    count = 0;
    Currency c("a", INT_MAX);
    for(Container<Currency>::iterator it = contCurrency.end(); count != 15; --it, count++){
        if (c < *it)
        {
            continue;
        }
        else
        {
            c = *it;
            cout << *it << " ";
        }
    }
    cout << endl;
    return 0;
}