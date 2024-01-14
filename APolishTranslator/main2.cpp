#include <string>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <map>

#define DIGITS "0123456789."
#define TEXT_SMB "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"
#define OPERATORS "( ) +- */ ^ sincostgctg"

typedef void *SCell;

typedef std::string SString;

enum STYPE{ SERR=0, SWHITE=1, STXT=2, SDIGIT=3,
    SEND=100, SLBR=111, SRBR=112, SADD=113, SMUL=114, SPOW=115, SPREOP=116,SPSTOP=117 };

class ASmb {
public:
    ASmb();
    ~ASmb();
    void Init(char c,int type,int a);
    void Init(const char *,int type,int a);
    ASmb *Copy(const char *lxm);
public:
    SString lexema;
    int stype;
    int arn; // positive for postfix form of arn=1 or infix form of arn = 3, negative for prefix form
};

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

class APolishTranslator{
public:
    APolishTranslator();
    ~APolishTranslator();
public:
    void InitSrc(const char *sset,int tp);
    void InitOp(const char *sset);
    int LastOpType();
public:
    virtual void ClearResult();
    virtual void InitTranslation();
    virtual void Output(ASmb *s);
    virtual void Parse(const char* lexema,ASmb &s);
public:
    const char *Translate(const char *text);
protected:
    char *result;
    int rpos;
    ASmb SrcSet[256];
    AStack OList;
};

typedef std::map <std::string, ASmb*> SmbMap;

class A2TreeTranslator: public APolishTranslator {
public:
    A2TreeTranslator();

public:
    virtual void Parse(const char *lexema, ASmb &s);

public:
    SmbMap sMap;
};


A2TreeTranslator::A2TreeTranslator() {
    ASmb *pSin = new ASmb;
    pSin->Init("sin", SPREOP, 1);
    sMap["sin"]=pSin;
}

void A2TreeTranslator::Parse(const char *lexema, ASmb &s) {
    printf(".");
    ASmb *ns = sMap[lexema];
    if (!ns) ns=&s;
    switch (ns->stype) {
        case SPREOP:
            printf("?");
            return;
        case SPSTOP:
            printf("!");
            return;
        default:
            APolishTranslator::Parse(lexema, s);
            return;
    }
}

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

ASmb::ASmb()
{
    stype=SERR;
    arn=-1;
}
/////////////////////////////////////////////
ASmb::~ASmb()
{
    //dtor
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

void ShowTranslate(APolishTranslator &T,const char *text)
{
    const char *result=T.Translate(text);
    printf("<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
    printf("source:\t%s\r\n",text);
    printf("result:\t%s\r\n",result);
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
}
///////////////////////////////////////////////////////////////
int main()
{
    APolishTranslator T;
    ShowTranslate(T,"A * B + C * D");
    ShowTranslate(T,"A +B*C+ D");
    ShowTranslate(T,"( A + B ) * C - ( D - E ) * ( F + G )");
    ShowTranslate(T,"Ab+Bc*Cd-(Dd-Ec)*(Fast+G)/X^2");
    A2TreeTranslator TT;
    ShowTranslate(TT,"sin X + 5 + a ++");
    ShowTranslate(TT,"sin(X) + 5 + (a++)");
    return 0;
}