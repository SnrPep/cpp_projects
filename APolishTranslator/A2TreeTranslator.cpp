#include "A2TreeTranslator.h"

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
