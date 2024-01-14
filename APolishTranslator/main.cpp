#include "APolishTranslator.h"
#include "A2TreeTranslator.h"
#include "NewBinTree.h"

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

void PrintSyntaxTree(ASmb *node, int depth = 0) {
    if (node) {
        for (int i = 0; i < depth; ++i) {
            printf("-");  // Adjust the spacing for better visualization
        }
        printf("%s\n", node->lexema.c_str());

        for (ASmb *child : node->children) {
            PrintSyntaxTree(child, depth + 1);
        }
    }
}

BinTree<string>::Node* make_node(ASmb* n)
{
    auto new_node = new BinTree<string>::Node(n->lexema);
    auto i = n->children.size();
    if (i >= 1)
    {
        new_node->left = make_node(n->children[0]);
    }
    if (i == 2)
    {
        new_node->right = make_node(n->children[1]);
    }
    return new_node;
}

BinTree<string> make_tree(ASmb* root)
{
    return BinTree<string>(make_node(root));
}

int main()
{
    APolishTranslator T;
    ShowTranslate(T,"A * B + C * D");
//    ShowTranslate(T,"A +B*C+ D");
    ShowTranslate(T,"( A + B ) * C - ( D - E ) * ( F + G )");
//    ShowTranslate(T,"Ab+Bc*Cd-(Dd-Ec)*(Fast+G)/X^2");
    A2TreeTranslator TT;
    ShowTranslate(TT,"A * B + C * D");

    printf("\nSyntax Tree:\n");
    PrintSyntaxTree(TT.root);

    return 0;
}
///////////////////////////////////////////////////////////////