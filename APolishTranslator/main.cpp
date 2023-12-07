#include "APolishTranslator.h"
#include "A2TreeTranslator.h"


///////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////