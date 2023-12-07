#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Widget.H>
#include <stdio.h>
#include <cinttypes>
#include <bitset>
#include <string.h>
#include <FL/Fl_Button.H>

const int nops = 12;
static char va, vb;
static long a, b, c;
unsigned long int VA,VB,VC;
Fl_Window *w;
Fl_Button *R, *S, *lA, *lB, *lC, *Op[nops],*lR,*lS;
Fl_Button *A[3][64], *B[3][64], *C[3][64];
Fl_Input *vA, *vB, *vC;

void cb_b(Fl_Button *w, void *data);
void cb_a(Fl_Button *w, void *data);
void cb_c(Fl_Button *w, void *data);
static void cb_op(Fl_Widget *w, void *data);

//int razr[4] = {8,16,32,64};
//int syst[4] = {8,16,10};
int RAZR = 0;
int SYST = 0;
const char *op[nops] = {"+", "-", "*", "/", "%", "<<", ">>", "~A", "~B", "&", "|", "^"};

void cb_R(Fl_Button *w, void *data) {
    RAZR++;
    RAZR %= 4;
    switch (RAZR) {
        case 0:
            for (int j = 0; j < 3; j++)
                for (int i = 0; i < 64; i++) {
                    A[j][i]->show();
                    B[j][i]->show();
                    C[j][i]->show();
                }
            VA = 0;
            VB = 0;
            VC = 0;
            break;
        case 1:
            for (int j = 0; j < 3; j++)
                for (int i = 0; i < 64; i++) {
                    if (i<56){
                        A[j][i]->hide();
                        B[j][i]->hide();
                        C[j][i]->hide();
                    }
                    else{
                        A[j][i]->show();
                        B[j][i]->show();
                        C[j][i]->show();
                    }
                }
            VA = 0;
            VB = 0;
            VC = 0;
            break;
        case 2:
            for (int j = 0; j < 3; j++)
                for (int i = 0; i < 64; i++) {
                    if (i<48){
                        A[j][i]->hide();
                        B[j][i]->hide();
                        C[j][i]->hide();
                    }
                    else{
                        A[j][i]->show();
                        B[j][i]->show();
                        C[j][i]->show();
                    }
                }
            VA = 0;
            VB = 0;
            VC = 0;
            break;
        case 3:
            for (int j = 0; j < 3; j++)
                for (int i = 0; i < 64; i++) {
                    if (i<31){
                        A[j][i]->hide();
                        B[j][i]->hide();
                        C[j][i]->hide();
                    }
                    else{
                        A[j][i]->show();
                        B[j][i]->show();
                        C[j][i]->show();
                    }

                }
            VA = 0;
            VB = 0;
            VC = 0;
            break;

    }
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "8") == 0) {
            button->label("16");
            //updateBitLabels(16);
        } else if (strcmp(currentText, "16") == 0) {
            button->label("32");
            //updateBitLabels(32);
        } else if (strcmp(currentText, "32") == 0) {
            button->label("64");
            //updateBitLabels(64);
        } else if (strcmp(currentText, "64") == 0) {
            button->label("8");
            //updateBitLabels(8);
        }
    }
}

void cb_S(Fl_Widget *w, void *data) {
    SYST++;
    SYST %= 3;
    cb_a(NULL, NULL);
    cb_b(NULL, NULL);
    cb_c(NULL,NULL);
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "8") == 0) {
            button->label("16");
        } else if (strcmp(currentText, "16") == 0) {
            button->label("10");
        } else if (strcmp(currentText, "10") == 0) {
            button->label("8");
        }
    }
}

static void cb_op(Fl_Widget *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    if (!button) return;
    const char *opLabel = button->label();
    char s[256];
    char s1[256];
    char s2[256];
    sscanf(vA->value(), "%ld", &VA);
    sscanf(vB->value(), "%ld", &VB);
    if (strcmp(opLabel, "+") == 0) {
        VC = VA + VB;
    } else if (strcmp(opLabel, "-") == 0) {
        VC = VA - VB;
    } else if (strcmp(opLabel, "*") == 0) {
        VC = VA * VB;
    } else if (strcmp(opLabel, "/") == 0) {
        if (VB != 0) {
            VC = VA / VB;
        } else {
            VC = 0;
            return;
        }
    } else if (strcmp(opLabel, "%") == 0) {
        if (VB != 0) {
            VC = VA % VB;
        } else {
            VC = 0;
            return;
        }
    } else if (strcmp(opLabel, "<<") == 0) {
        VC = VA << VB;
    } else if (strcmp(opLabel, ">>") == 0) {
        VC = VA >> VB;
    } else if (strcmp(opLabel, "~A") == 0) {
        VC = ~VA;
    } else if (strcmp(opLabel, "~B") == 0) {
        VC = ~VB;
    } else if (strcmp(opLabel, "&") == 0) {
        VC = VA & VB;
    } else if (strcmp(opLabel, "|") == 0) {
        VC = VA | VB;
    } else if (strcmp(opLabel, "^") == 0) {
        VC = VA ^ VB;
    }
    switch(SYST){
        case 0:
            sprintf(s,"%o", VC);
            break;
        case 1:
            sprintf(s,"%x", VC);
            break;
        case 2:
            sprintf(s,"%ld", VC);
            break;
    }
    vC->value(s);
    for (long int i = 0; i < 64; i++) {
        long int bit = (VA & (static_cast<unsigned long int>(1) << (63 - i))) ? 1 : 0;
        A[0][i]->label(bit ? "1" : "0");
    }
    for (long int i = 0; i < 64; i++) {
        long int bit = (VC & (static_cast<unsigned long int>(1) << (63 - i))) ? 1 : 0;
        C[0][i]->label(bit ? "1" : "0");
    }
    for (long int i = 0; i < 64; i++) {
        long int bit = (VB & (static_cast<unsigned long int>(1) << (63 - i))) ? 1 : 0;
        B[0][i]->label(bit ? "1" : "0");
    }
}

void cb_c(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VC = 0;
    char s[100];
    long int val1;
    for (long int i = 0; i < 64; i++) {
        val1 = (strcmp(C[0][63-i]->label(),"1")==0)?1:0;
        VC += val1 * (static_cast<unsigned long int>(1) << i);
        switch(SYST){
            case 0:
                sprintf(s,"%o", VC);
                break;
            case 1:
                sprintf(s,"%x", VC);
                break;
            case 2:
                sprintf(s,"%ld", VC);
                break;
        }
        vC->value(s);
    }
}

void cb_a(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VA = 0;
    char s1[100];
    long int val1;
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for (long int i = 0; i < 64; i++) {
        val1 = (strcmp(A[0][63-i]->label(),"1")==0)?1:0;
        VA += val1 * (static_cast<unsigned long int>(1) << i);
        switch(SYST){
            case 0:
                sprintf(s1,"%o", VA);
                break;
            case 1:
                sprintf(s1,"%x", VA);
                break;
            case 2:
                sprintf(s1,"%ld", VA);
                break;
        }
        vA->value(s1);
    }
}

void cb_b(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VB = 0;
    char s2[100];
    long int val2;
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for (long int i = 0; i < 64; i++) {
        val2 = (strcmp(B[0][63-i]->label(),"1")==0)?1:0;
        VB += val2 * (static_cast<unsigned long int>(1) << i);
        switch(SYST){
            case 0:
                    sprintf(s2,"%o", VB);
                    break;
            case 1:
                    sprintf(s2,"%x", VB);
                    break;
            case 2:
                    sprintf(s2,"%ld", VB);
                    break;
        }
        vB->value(s2);
    }
}


void cb_vA(Fl_Widget *w, void *data) {
    sscanf(vA->value(), "%ld", &VA);
    long int bit = 0;
    for (long int i = 0; i < 64; i++) {
        //sscanf(vA->value(), "%ld", &VA);
        bit = (VA & (static_cast<unsigned long int>(1) << (63 - i))) ? 1 : 0;
        A[0][i]->label(bit ? "1" : "0");
    }
    VA=0;
}

void cb_vB(Fl_Widget *w, void *data) {
    sscanf(vB->value(), "%ld", &VB);
    for (long int i = 0; i < 64; i++) {
        long int bit = (VB & (static_cast<unsigned long int>(1) << (63 - i))) ? 1 : 0;
        B[0][i]->label(bit ? "1" : "0");
    }
    VB=0;
}

int main(int argc, char **argv) {
    w = new Fl_Window(1010, 250);
    w->resizable();
    if (w) {/* empty */}
    {
        R = new Fl_Button(25, 25, 80, 35, "64");
        R->box(FL_NO_BOX);
        R->callback((Fl_Callback *)cb_R);
    }
    {
        S = new Fl_Button(125, 25, 80, 35, "8");
        S->box(FL_NO_BOX);
        S->callback((Fl_Callback *)cb_S);
    }
    lR = new Fl_Button(25, 5, 80, 20, "Разряд");
    lR->box(FL_NO_BOX);
    lS = new Fl_Button(125, 5, 80, 20, "Система");
    lS->box(FL_NO_BOX);
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
    for (long j = 0; j < 3; j++)
        for (long i = 0; i < 64; i++) {
            int J;
            //J = (j == 2) ? 3 : j;
            A[j][i] = new Fl_Button(30 + i * (0 * 25 + 15), 70, 15 + 25 * 0, 20, "0");
            /*if ((i / 3) % 3)
             *
                A[j][i]->color(color);*/
            B[j][i] = new Fl_Button(30 + i * (0 * 25 + 15), 110, 15 + 25 * 0, 20, "0");
            C[j][i] = new Fl_Button(30 + i * (0 * 25 + 15), 150, 15 + 25 * 0, 20, "0");
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
    vC->when(FL_WHEN_CHANGED);
    w->end();
    w->show(argc, argv);
    return Fl::run();
}