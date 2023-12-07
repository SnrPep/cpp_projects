#ifndef ASMB_H
#define ASMB_H
#include <string>

#define DIGITS "0123456789."
#define TEXT_SMB "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"
#define OPERATORS "( ) +- */ ^ sincostgctg"

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

#endif // ASMB_H
