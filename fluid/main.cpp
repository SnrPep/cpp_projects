#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <stdio.h>
#include <string.h>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>

const int nops = 12;
static char va, vb;
static long a, b, c;
int VA,VB,VC;
Fl_Window *w;
Fl_Button *R, *S, *lA, *lB, *lC, *Op[nops];
Fl_Button *A[3][32], *B[3][32], *C[3][32];
Fl_Input *vA, *vB, *vC;



char *op[nops] = {"+", "-", "*", "/", "%", "<<", ">>", "-A", "-B", "&", "|", "^"};
// Number of operations

void cb_R(Fl_Button *w, void *data) {
    // Implement the callback for the "Paзp=8" button
    // This function will be called when the button is clicked
    if (button) {
        // Получаем текущий текст кнопки
        const char *currentText = button->label();
        if (strcmp(currentText, "Разр=10") == 0) {
            button->label("Разр=16");
        }
        else if (strcmp(currentText, "Разр=16") == 0) {
            button->label("Разр=2");
        }
        else if (strcmp(currentText, "Разр=2") == 0) {
            button->label("Разр=8");
        }
        else if (strcmp(currentText, "Разр=8") == 0) {
            button->label("Разр=10");
        }
    }
}

void cb_S(Fl_Widget *w, void *data) {
    // Implement the callback for the "syst==8" button
    // This function will be called when the button is clicked
}




static void cb_op(Fl_Widget *w, void *data) {
    char s[256];

    if (op[0])
    {

    }
    for (char *p : op){
        switch (*p) {
            case '+':
                VC = VA+VB;
                sprintf(s, "%ld", VC);
                vC->value(s);
                break;
            case'-':
                VC = VA-VB;
                sprintf(s, "%ld", VC);
                vC->value(s);
                break;
            case'*':
                VC = VA*VB;
                sprintf(s, "%ld", VC);
                vC->value(s);
                break;
            default:
                VC = 100;
                sprintf(s, "%ld", VC);
                vC->value(s);
        }
    }
}

void cb_a(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w); // Преобразование указателя к типу Fl_Button
    VA = 0;
    char s[30];
    int val;
    if (button) {
        // Получаем текущий текст кнопки
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for (int i = 0; i < 32; i++) {
        val = (strcmp(A[0][31-i]->label(),"1")==0)?1:0;
        VA += val * (1 << i);
        sprintf(s,"%d", VA);
        vA->value(s);
    }
}

void cb_b(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w); // Преобразование указателя к типу Fl_Button
    VB = 0;
    char s[30];
    int val;
    if (button) {
        // Получаем текущий текст кнопки
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for (int i = 0; i < 32; i++) {
        val = (strcmp(B[0][31-i]->label(),"1")==0)?1:0;
        VB += val * (1 << i);
        sprintf(s,"%d", VB);
        vB->value(s);
    }
}


void cb_vA(Fl_Widget *w, void *data) {
    sscanf(vA->value(), "%ld", &a);
    /*Fl_Button *button = dynamic_cast<Fl_Button *>(w); // Преобразование указателя к типу Fl_Button
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 32; i++) {
            A[j][i]->value(vA&&(1<<i)?1:0);
        }*/
}

void cb_vB(Fl_Widget *w, void *data) {
    sscanf(vB->value(), "%ld", &b);
    /*Fl_Button *button = dynamic_cast<Fl_Button *>(w); // Преобразование указателя к типу Fl_Button
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 32; i++) {
            B[j][i]->value(vB&&(1<<i)?1:0);
        }
    button->value();*/
}

int main(int argc, char **argv) {
    w = new Fl_Window(60 + 25 * 32, 250);
    w->resizable();

    if (w) {/* empty */}
    {
        R = new Fl_Button(25, 25, 80, 35, "Paзp=8");
        R->box(FL_NO_BOX);
        R->callback((Fl_Callback *)cb_R);
    }
    {
        S = new Fl_Button(125, 25, 80, 35, "syst==8");
        S->box(FL_NO_BOX);
        S->callback((Fl_Callback *)cb_S);
    }
    lA = new Fl_Button(5, 70, 25, 25, "A");
    lA->box(FL_NO_BOX);
    lB = new Fl_Button(5, 110, 25, 25, "B");
    lB->box(FL_NO_BOX);
    lC = new Fl_Button(5, 150, 25, 25, "C");
    lC->box(FL_NO_BOX);

    for (int i = 0; i < nops; i++) {
        Op[i] = new Fl_Button(30 + i * 40, 200, 40, 30, op[i]);
        Op[i]->callback((Fl_Callback *) cb_op);
    }

    Fl_Color color;
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 32; i++) {
            int J;
            J = (j == 2) ? 3 : j;
            A[j][i] = new Fl_Button(30 + i * (J * 25 + 25), 70, 25 + 25 * J, 20, "0");
            /*if ((i / 3) % 3)
                A[j][i]->color(color);*/
            B[j][i] = new Fl_Button(30 + i * (J * 25 + 25), 110, 25 + 25 * J, 20, "0");
            C[j][i] = new Fl_Button(30 + i * (J * 25 + 25), 150, 25 + 25 * J, 20, "0");
            if (j) {
                A[j][i]->hide();
                B[j][i]->hide();
                C[j][i]->hide();
            }
            A[j][i]->callback((Fl_Callback *)cb_a);
            B[j][i]->callback((Fl_Callback *)cb_b);
        }

    vA = new Fl_Input(300, 30, 100, 25, "A");
    vA->callback((Fl_Callback *)cb_vA);
    vA->when(FL_WHEN_CHANGED);
    vB = new Fl_Input(450, 30, 100, 25, "B");
    vB->callback((Fl_Callback *)cb_vB);
    vB->when(FL_WHEN_CHANGED);
    vC = new Fl_Input(600, 30, 100, 25, "C");

    w->end();
    w->show(argc, argv);
    return Fl::run();
}