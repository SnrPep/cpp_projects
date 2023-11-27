#include <iostream>
#include "class.h"

using namespace std;

int main()
{
    Store s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);

    s1.info();
    int counter = 0;

    // Делаем цикл с использованием итератора контейнера s1
    for (Store::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        counter++;
        *it = counter * 10;
        std::cout << *it << "\n";
    }

    return 0;
}
