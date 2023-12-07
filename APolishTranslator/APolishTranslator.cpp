#include <assert.h>
#include "APolishTranslator.h"

///////////////////////////////////////////////////////
APolishTranslator::APolishTranslator(){
    result=new char[2000];
    InitSrc(DIGITS,SDIGIT);
    InitSrc(TEXT_SMB,STXT);
    InitSrc(" \t\r\n",SWHITE);
    InitOp(OPERATORS);
    SrcSet[0].Init(char(0),SEND,0);
}
///////////////////////////////////////////////////////
APolishTranslator::~APolishTranslator()
{
    ClearResult();
    delete result;
}
///////////////////////////////////////////////////////
void APolishTranslator::ClearResult()
{
    result[0]=0;
    rpos=0;
}
///////////////////////////////////////////////////////
void APolishTranslator::InitSrc(const char *sset,int tp)
{
    int len=strlen(sset);
    for (int i=0;i<len;i++)
    {
        char c=sset[i];
        ASmb &s=SrcSet[int(c)];
        s.Init(c,tp,0);
    }
}
///////////////////////////////////////////////////////
void APolishTranslator::InitOp(const char *sset)
{
    int len=strlen(sset);
    int prio=0;
    for (int i=0;i<len;i++)
    {
        char c=sset[i];
        if (c==' ')
        {
            prio++;
            continue;
        }
        ASmb &s=SrcSet[int(c)];
        s.Init(c,prio+SLBR,2);
    }
}
///////////////////////////////////////////////////////
void APolishTranslator::InitTranslation()
{
    ClearResult();
    OList.Init();
}
///////////////////////////////////////////////////////
int APolishTranslator::LastOpType()
{
    ASmb *l=(ASmb *)OList.Last();
    if (!l)
        return SEND;
    return l->stype;
}
///////////////////////////////////////////////////////
void APolishTranslator::Output(ASmb *psmb)
{
    int len=psmb->lexema.length();
    strncpy(&result[rpos],psmb->lexema.c_str(),len);
    rpos+=len;
    strcpy(&result[rpos]," ");
    rpos+=1;

}

///////////////////////////////////////////////////////
void APolishTranslator::Parse(const char* lexema,ASmb &s)
{
    switch(s.stype) {
        case SERR:
            printf("Unrecognized symbol %s\r\n", lexema);
        case SWHITE:
            return;
        case STXT:
        case SDIGIT:
            Output(s.Copy(lexema));
            return;
        case SLBR:
            OList.Push(s.Copy(lexema));
            return;
        case SPOW:
        case SMUL:
        case SADD:
            while (s.stype <= LastOpType())
                Output((ASmb *) OList.Pop());
            OList.Push(s.Copy(lexema));
            return;
        case SRBR:
        case SEND:
            ASmb *l;
            while (l = (ASmb *) OList.Pop()) {
                if (l->stype == SLBR)
                    break;
                Output(l);
            }

            if ((!l && s.stype == SRBR) || (l && s.stype != SRBR))
                printf("Wrong number of brackets (%s)\r\n", lexema);
            if (l)
                delete l;
            return;
    }
}
///////////////////////////////////////////////////////
const char *APolishTranslator::Translate(const char *text)
{
    InitTranslation();
    int sz=0,len=strlen(text);
    char lexema[25];
    ASmb *lt=&SrcSet[int(text[0])];

    for (int i=0;i<=len;i++)
    {
        char c=text[i];
        ASmb &s=SrcSet[int(c)];
        if (s.stype==lt->stype || sz==0)
            lexema[sz++]=c;
        else
        {
            lexema[sz]=0;
            Parse(lexema,*lt);
            sz=0;
            lexema[sz++]=c;
            lt=&s;
        }
    }
    Parse("",*lt);
    return result;
}
///////////////////////////////////////////////////////
