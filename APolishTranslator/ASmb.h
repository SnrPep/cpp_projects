#ifndef ASMB_H
#define ASMB_H

#include <string>
#include <vector>

#define DIGITS "0123456789."
#define TEXT_SMB "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"
#define OPERATORS "( ) +- */ ^ sincostgctg"

enum STYPE{ SERR=0, SWHITE=1, STXT=2, SDIGIT=3,
    SEND=100, SLBR=111, SRBR=112, SADD=113, SMUL=114, SPOW=115, SPREOP=116,SPSTOP=117 };

typedef std::string SString;

class ASmb {
public:
    ASmb();
    ~ASmb();
    void Init(char c, int type, int a);
    void Init(const char *, int type, int a);
    ASmb *Copy(const char *lxm);

public:
    SString lexema;
    int stype;
    int arn; // positive for postfix form of arn=1 or infix form of arn = 3, negative for prefix form
    ASmb *parent;  // pointer to the parent node
    std::vector<ASmb *> children;  // vector of pointers to child nodes
};

#endif // ASMB_H
