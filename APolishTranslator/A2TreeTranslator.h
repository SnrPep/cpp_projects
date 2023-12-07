#ifndef APOLISHTRANSLATOR_A2TREETRANSLATOR_H
#define APOLISHTRANSLATOR_A2TREETRANSLATOR_H

#include <stdio.h>
#include <string.h>
#include "AStack.h"
#include "APolishTranslator.h"
#include "ASmb.h"
#include "map"

typedef std::map <std::string, ASmb*> SmbMap;

class A2TreeTranslator: public APolishTranslator {
public:
    A2TreeTranslator();

public:
    virtual void Parse(const char *lexema, ASmb &s);

public:
    SmbMap sMap;
};

#endif //APOLISHTRANSLATOR_A2TREETRANSLATOR_H