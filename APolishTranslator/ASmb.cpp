#include <string.h>
#include "ASmb.h"

/////////////////////////////////////////////
ASmb::ASmb()
{
    stype=SERR;
    arn=-1;
}
/////////////////////////////////////////////
ASmb::~ASmb()
{
    for (ASmb *child : children) {
        delete child;
    }
}
/////////////////////////////////////////////
void ASmb::Init(char c,int type,int a)
{
    char x[2]={c,0};
    lexema=x;
    stype=type;
    arn=a;
}
/////////////////////////////////////////////
void ASmb::Init(const char *s,int type,int a)
{
    lexema=s;
    stype=type;
   arn=a;
}
/////////////////////////////////////////////
ASmb *ASmb::Copy(const char *lxm)
{
    ASmb *result=new ASmb;
    result->stype=stype;
    result->arn=arn;
    result->lexema=lxm;
    return result;
}
/////////////////////////////////////////////
