#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Widget.H>
#include <stdio.h>
#include <bitset>
#include <string.h>
#include <FL/Fl_Button.H>

const int nops = 12;
int64_t VA,VB,VC;
Fl_Window *w;
Fl_Button *R, *S, *lA, *lB, *lC, *Op[nops],*lR,*lS;
Fl_Button *A[3][64], *B[3][64], *C[3][64];
Fl_Input *vA, *vB, *vC;

void cb_b(Fl_Button *w, void *data);
void cb_a(Fl_Button *w, void *data);
void cb_c(Fl_Button *w, void *data);
static void cb_op(Fl_Widget *w, void *data);

int Razr=64;
int RAZR = 0;
int SYST = 0;
const char *op[nops] = {"+", "-", "*", "/", "%", "<<", ">>", "~A", "~B", "&", "|", "^"};

void cb_R(Fl_Button *w, void *data) {
    RAZR++;
    RAZR %= 4;

    switch (RAZR) {
        case 0:
            Razr=64;
            for (int j = 0; j < 3; j++)
                for (int i = 0; i < 50; i++) {
                    A[j][i]->show();
                    B[j][i]->show();
                    C[j][i]->show();
                }
            break;
        case 1:
            Razr=8;
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 64; i++) {
                    if (i < 56) {
                        A[j][i]->hide();
                        B[j][i]->hide();
                        C[j][i]->hide();
                        A[j][i]->label("0");
                        B[j][i]->label("0");
                        C[j][i]->label("0");
                    }
                }
            }
            cb_a(NULL, NULL);
            cb_b(NULL, NULL);
            cb_c(NULL, NULL);
            break;
        case 2:
            Razr=16;
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 64; i++) {
                    if (i < 48) {
                        A[j][i]->hide();
                        B[j][i]->hide();
                        C[j][i]->hide();
                        A[j][i]->label("0");
                        B[j][i]->label("0");
                        C[j][i]->label("0");
                    }
                    else if (i > 48 && i < 56){
                        A[j][i]->show();
                        B[j][i]->show();
                        C[j][i]->show();
                    }
                }
            }
            cb_a(NULL, NULL);
            cb_b(NULL, NULL);
            cb_c(NULL, NULL);
            break;
        case 3:
            Razr=32;
            for (int j = 0; j < 3; j++) {
                for (int i = 0; i < 64; i++) {
                    if (i < 31) {
                        A[j][i]->hide();
                        B[j][i]->hide();
                        C[j][i]->hide();
                        A[j][i]->label("0");
                        B[j][i]->label("0");
                        C[j][i]->label("0");
                    }
                    else if (i > 31 && i < 49) {
                        A[j][i]->show();
                        B[j][i]->show();
                        C[j][i]->show();
                    }
                }
            }
            cb_a(NULL, NULL);
            cb_b(NULL, NULL);
            cb_c(NULL, NULL);
    }
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "8") == 0) {
            button->label("16");
        } else if (strcmp(currentText, "16") == 0) {
            button->label("32");
        } else if (strcmp(currentText, "32") == 0) {
            button->label("64");
        } else if (strcmp(currentText, "64") == 0) {
            button->label("8");
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
    switch(SYST){
        case 0:
            sscanf(vA->value(), "%llo", &VA);
            sscanf(vB->value(), "%llo", &VB);
            break;
        case 1:
            sscanf(vA->value(), "%llx", &VA);
            sscanf(vB->value(), "%llx", &VB);
            break;
        case 2:
            sscanf(vA->value(), "%lld", &VA);
            sscanf(vB->value(), "%lld", &VB);
            break;
    }
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
            sprintf(s,"%llo", VC);
            break;
        case 1:
            sprintf(s,"%llx", VC);
            break;
        case 2:
            sprintf(s,"%lld", VC);
            break;
    }
    vC->value(s);
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < Razr; i++) {
            int64_t bit = (VC & (static_cast<int64_t>(1) << (Razr - 1 - i))) ? 1 : 0;
            C[0][i + 64 - Razr]->label(bit ? "1" : "0");
        }
    }
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < Razr; i++) {
            int64_t bit = (VA & (static_cast<int64_t>(1) << (Razr - 1 - i))) ? 1 : 0;
            A[0][i + 64 - Razr]->label(bit ? "1" : "0");
        }
    }
    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < Razr; i++) {
            int64_t bit = (VB & (static_cast<int64_t>(1) << (Razr - 1 - i))) ? 1 : 0;
            B[0][i + 64 - Razr]->label(bit ? "1" : "0");
        }
    }
}

void cb_c(Fl_Button *w, void *data) {
    VC = 0;
    char s[100];
    int64_t val1;
    for (int i = 0; i < Razr; i++) {
        val1 = (strcmp(C[0][64 - 1 - i]->label(),"1")==0)?1:0;
        VC += val1 * (static_cast<int64_t>(1) << i);
        switch(SYST){
            case 0:
                sprintf(s,"%llo", VC);
                break;
            case 1:
                sprintf(s,"%llx", VC);
                break;
            case 2:
                sprintf(s,"%lld", VC);
                break;
        }
        vC->value(s);
    }
}

void cb_a(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VA = 0;
    char s1[100]= "0";
    int64_t val1;
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for(int j = 0; j<3;j++)
        for (int i = 0; i < Razr; i++) {
            val1 = (strcmp(A[j][63 - i]->label(),"1")==0)?1:0;
            VA += val1 * (static_cast<int64_t>(1) << i);
            switch(SYST){
                case 0:
                    sprintf(s1,"%llo", VA);
                    break;
                case 1:
                    sprintf(s1,"%llx", VA);
                    break;
                case 2:
                    sprintf(s1,"%lld", VA);
            }
            vA->value(s1);
        }
}

void cb_b(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VB = 0;
    char s2[100] = "0";
    int64_t val2;
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for(int j = 0; j<3;j++)
        for (int i = 0; i < Razr; i++) {
            val2 = (strcmp(B[j][64 - 1 - i]->label(),"1")==0)?1:0;
            VB += val2 * (static_cast<int64_t>(1) << i);
            switch(SYST){
                case 0:
                    sprintf(s2,"%llo", VB);
                    break;
                case 1:
                    sprintf(s2,"%llx", VB);
                    break;
                case 2:
                    sprintf(s2,"%lld", VB);
            }
            vB->value(s2);
        }
}


void cb_vA(Fl_Widget *w, void *data) {
    VA=0;
    switch(SYST){
        case 0:
            sscanf(vA->value(), "%llo", &VA);
            break;
        case 1:
            sscanf(vA->value(), "%llx", &VA);
            break;
        case 2:
            sscanf(vA->value(), "%lld", &VA);
            break;
    }
    int64_t bit = 0;

    for (int i = 0; i < Razr; i++) {
        bit = (VA & (static_cast<int64_t>(1) << (Razr - 1 - i))) ? 1 : 0;
        A[0][i + 64 - Razr]->label(bit ? "1" : "0");
    }

}

void cb_vB(Fl_Widget *w, void *data) {
    VB=0;
    switch(SYST){
        case 0:
            sscanf(vB->value(), "%llo", &VB);
            break;
        case 1:
            sscanf(vB->value(), "%llx", &VB);
            break;
        case 2:
            sscanf(vB->value(), "%lld", &VB);
            break;
    }
    for (int i = 0; i < Razr; i++) {
        int64_t bit = (VB & (static_cast<int64_t>(1) << (Razr - 1 - i))) ? 1 : 0;
        B[0][i + 64 - Razr]->label(bit ? "1" : "0");
    }

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
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 64; i++) {
            int J;
            //J = (j == 2) ? 3 : j;
            A[j][i] = new Fl_Button(30 + i * (0 * 25 + 15), 70, 15 + 25 * 0, 20, "0");
            /*if ((i / 3) %ll 3)
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

    vA = new Fl_Input(300, 30, 200, 25, "A");
    vA->callback((Fl_Callback *)cb_vA);
    vA->when(FL_WHEN_CHANGED);
    vB = new Fl_Input(550, 30, 200, 25, "B");
    vB->callback((Fl_Callback *)cb_vB);
    vB->when(FL_WHEN_CHANGED);
    vC = new Fl_Input(800, 30, 200, 25, "C");
    vC->when(FL_WHEN_CHANGED);
    w->end();
    w->show(argc, argv);
    return Fl::run();
}