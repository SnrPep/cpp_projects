#ifndef CLASS
#define CLASS

#include <iostream>

using namespace std;

const int MAXSIZE = 100;

template<class T>
class Container {
private:
    T data[MAXSIZE];
    int size;
public:

    Container();
    void add(T x);
    void remove();
    void info();
    class iterator {
    private:
        int index;
        Container *pdata;
    public:
        iterator();
        iterator(int i, Container *p);
        iterator &operator++();
        iterator operator++(int);
        iterator &operator--();
        iterator operator--(int);
        T& operator*();
        bool operator !=(typename Container<T>::iterator x);
        bool operator ==(typename Container<T>::iterator x);
        bool operator <(typename Container<T>::iterator x);
    };
    Container<T>::iterator begin();
    Container<T>::iterator end() ;
};

template <class T>
Container<T>::Container()
{
    size = 0;
}

template <class T>
void Container<T>::add(T x)
{
    data[size] = x;
    size++;
}

template <class T>
void Container<T>::remove() {
    size--;
}

template <class T>
void Container<T>::info()
{
    for (int i = 0; i < size - 1; i++)
    {
        cout << data[i] << ", ";
    }
    if (size > 0)
    {
        cout << data[size - 1];
    }
    cout << "\n";
}

template <class T>
Container<T>::iterator::iterator()
{
    index = 0;
    pdata = NULL;
}

template <class T>
Container<T>::iterator::iterator(int i, Container *p)
{
    index = i;
    pdata = p;
}

template <class T>
typename Container<T>::iterator Container<T>::begin()
{
    return iterator(0, this);
}
template <class T>
typename Container<T>::iterator Container<T>::end()
{
    return iterator(size-1, this);
}
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator++() {
    index += 2;
    if (index >= pdata->size) {
        index = 0;
    }
    return *this;
}

template<class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int) {
    iterator temp = this;
    ++(this);
    return temp;
}

template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator--() {
    if (index == 0) {
        index = pdata->size - 1;
    } else {
        index -= 2;
    }
    return *this;
}

template<class T>
typename Container<T>::iterator Container<T>::iterator::operator--(int) {
    iterator temp = *this;
    --(*this);
    return temp;
}

template <class T>
T& Container<T>::iterator::operator*() {
    return pdata->data[index];
}

template <class T>
bool Container<T>::iterator:: operator==( iterator x)  {
    return index == x.index && pdata == x.pdata;
}

template <class T>
bool Container<T>::iterator:: operator<( iterator x)  {
    return index < x.index && pdata < x.pdata;
}

template <class T>
bool Container<T>::iterator:: operator!=( iterator x)  {
    return !(*this == x);
}

#endif