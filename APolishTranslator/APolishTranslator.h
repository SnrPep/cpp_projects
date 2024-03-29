#ifndef APOLISHTRANSLATOR_H
#define APOLISHTRANSLATOR_H

#include <stdio.h>
#include <string.h>
#include <memory>
#include "AStack.h"
#include "ASmb.h"


class APolishTranslator{
 public:
    APolishTranslator();
    ~APolishTranslator();
 public:
    void InitSrc(const char *sset,int tp);
    void InitOp(const char *sset);
    int LastOpType();
    ASmb SrcSet[256];
public:
    virtual void ClearResult();
    virtual void InitTranslation();
    virtual void Output(ASmb *s);
    virtual void Parse(const char* lexema,ASmb &s);
    ASmb* root = nullptr;
 public:
    const char *Translate(const char *text);
 protected:
    char *result;
    int rpos;
    AStack OList;
};

#endif // APOLISHTRANSLATOR_H
