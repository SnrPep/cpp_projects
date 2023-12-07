#include "AStack.h"

///////////////////////////////////////
AStack::AStack()
{
    Buffer=NULL;
    Init();
}
///////////////////////////////////////
AStack::~AStack()
{
    //dtor
}
///////////////////////////////////////
void AStack::ClearUp()
{
    if (Buffer)
        delete Buffer;
    Buffer=NULL;
    CPos=0;
    Size=0;
}
///////////////////////////////////////
void AStack::Init()
{
    ClearUp();
    InitBuf(30);
}
///////////////////////////////////////
void AStack::InitBuf(int sz)
{
    assert(Buffer==NULL);
    Buffer=new SCell[sz];
    Size=sz;
}
///////////////////////////////////////
void AStack::Push(void *val)
{
    assert(CPos<Size);
    Buffer[CPos++]=val;
}
///////////////////////////////////////
void *AStack::Pop()
{
    if (CPos==0)
        return NULL;
    CPos--;
    return Buffer[CPos];
}
///////////////////////////////////////
void *AStack::Last()
{
    if (CPos==0)
        return NULL;
    return Buffer[CPos-1];
}
///////////////////////////////////////
void *AStack::Get(int i)
{
    return Buffer[i];
}
///////////////////////////////////////
int AStack::GetCount()
{
    return CPos;
}
///////////////////////////////////////
bool AStack::IsEmpty()
{
    return CPos==0;
}

