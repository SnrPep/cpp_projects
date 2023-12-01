#include "class.h"

Store::Store()
{
    size = 0;
}

void Store::add(int x)
{
    if (size < MAX)
    {
        data[size] = x;
        size++;
    }
}

void Store::del()
{
    if (size > 0)
    {
        size--;
    }
}

void Store::info()
{
    for(int i = 0; i < size; i++)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

Store::iterator::iterator()
{
    index = 0;
    pdata = NULL;
}

Store::iterator::iterator(int i, Store *p)
{
    index = i;
    pdata = p;
}

Store::iterator Store::iterator::operator++()
{
    index++;
    return *this;
}

Store::iterator Store::iterator::operator--()
{
    index--;
    return *this;
}

bool Store::iterator::operator ==(Store::iterator x)
{
    return (index == x.index && pdata == x.pdata);
}

bool Store::iterator::operator !=(Store::iterator x)
{
    return (index != x.index || pdata != x.pdata);
}

int& Store::iterator::operator*()
{
    if (pdata)
    {
        return pdata->data[index];
    }
    else
    {
        throw 0;
    }
}

Store::iterator Store::begin()
{
    return iterator(0, this);
}
Store::iterator Store::end()
{
    return iterator(size, this);
}