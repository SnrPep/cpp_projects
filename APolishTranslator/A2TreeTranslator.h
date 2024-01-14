#ifndef A2TREETRANSLATOR_H
#define A2TREETRANSLATOR_H
#include "APolishTranslator.h"
#include "ASmb.h"
#include <string>
#include <memory>
#include <map>

typedef std::map<std::string, ASmb*> sM;

class A2TreeTranslator: public APolishTranslator{
public:
    A2TreeTranslator();
public:
    virtual void Parse(const char* lexema, ASmb &s);
    //void Output(ASmb *psmb);
    ASmb SrcSet[256];
public:
    sM sMap;
};


#endif //A2TREETRANSLATOR_H