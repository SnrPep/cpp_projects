#ifndef MYTEMPLATES
#define MYTEMPLATES

#include<iostream>

const int MAXSIZE = 10;

class Full{};
class Empty{};
class Big{};

template <class T>
class Container
{
private:
    T data[MAXSIZE];
    T max;
    int size;
public:
    Container();
    void add(T x);
    void del();
    void info();
};

template <class T>
Container<T>::Container()
{
    size = 0;
}

template <class T>
void Container<T>::add(T x)
{
    if (max == NULL)
    {
        max = x;
    }
    if (size < MAXSIZE && sizeof(max) * 2 > sizeof(x))
    {
        if (max < x)
        {
            max = x;
        }
        data[size] = x;
        size++;
    }
    else if (size >= MAXSIZE)
    {
        throw Full();
    }
    else
    {
        throw Big();
    }
}

template <class T>
void Container<T>::del()
{
    if (size > 0)
    {
        size--;
    }
    else
    {
        throw Empty();
    }
}

template <class T>
void Container<T>::info()
{
    for (int i = 0; i < size - 1; i++)
    {
        std::cout << data[i] << ", ";
    }
    if (size > 0)
    {
        std::cout << data[size - 1];
    }
    std::cout << "\n";
}

#endif // MYTEMPLATES

