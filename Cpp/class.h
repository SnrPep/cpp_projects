#ifndef CPP_CLASS_H
#define CPP_CLASS_H

#include <iostream>

const int MAX = 100;

class Store
{
private:
    int data[MAX];
    int size;
public:
    int a;
    Store();
    void add(int x);
    void del();
    void info();
    class iterator
    {
    private:
        int index;
        Store* pdata;
    public:
        iterator();
        iterator(int i, Store* p);
        Store::iterator operator++();
        bool operator !=(Store::iterator x);
        bool operator ==(Store::iterator x);
        int& operator*();
    };
    Store::iterator begin();
    Store::iterator end();
};

#endif
