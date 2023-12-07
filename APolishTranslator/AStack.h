#ifndef ASTACK_H
#define ASTACK_H
#include <assert.h>

#ifndef NULL
    #define NULL nullptr
#endif
typedef void *SCell;

class AStack
{
public:
    AStack();
    virtual ~AStack();

public:
    void ClearUp();
    void Init();
public:
    void InitBuf(int sz);
    void Push(void *);
    void *Pop();
    void *Last();
    void *Get(int pos);
    int GetCount();
    bool IsEmpty();

private:
    SCell *Buffer;
    int Size;
    int CPos;
};

#endif // ASTACK_H
