#include "A2TreeTranslator.h"
#define ADD_OP(name,pos) {ASmb *p = new ASmb;sMap[name] =p;p->Init(name, pos, 1);}

class Node{
    std::string s;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
};

std::shared_ptr<Node> root = nullptr;

A2TreeTranslator::A2TreeTranslator(){
    ADD_OP("++",SPSTOP);
    ADD_OP("--",SPSTOP);
    ADD_OP("sin",SPREOP);
    ADD_OP("cos",SPREOP);
    ADD_OP("tan",SPREOP);
    ADD_OP("ctan",SPREOP);
    ADD_OP("log",SPREOP);
    ADD_OP("exp",SPREOP);
}

void A2TreeTranslator::Parse(const char* lexema, ASmb &s) {
    ASmb *ns = sMap[lexema];
    if (!ns) ns = &s;
    switch (ns->stype) {
        case SPREOP:
            OList.Push(ns->Copy(lexema));
            return;
        case SPSTOP:
            while (ns->stype <= LastOpType())
                Output((ASmb*)OList.Pop());
            OList.Push(ns->Copy(lexema));
            return;
        default:
            APolishTranslator::Parse(lexema, s);
            return;
    }
}
