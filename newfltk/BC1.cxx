#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Widget.H>
#include <cstdio>
#include <bitset>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <FL/Fl_Button.H>

const int nops = 12;
uint64_t VA,VB,VC;
Fl_Window *w;
Fl_Button *R, *S, *lA, *lB, *lC, *Op[nops],*lR,*lS;
Fl_Button *A[3][64], *B[3][64], *C[3][64];
Fl_Input *vA, *vB, *vC;

int RAZR = 0;
int SYST = 0;

void cb_b(Fl_Button *w, void *data);
void cb_a(Fl_Button *w, void *data);
void cb_c(Fl_Button *w, void *data);
static void cb_op(Fl_Widget *w, void *data);

class Digit
{
public:
    Digit(Fl_Input* input, Fl_Button* label, int ypos);
private:
    std::vector<std::unique_ptr<Fl_Button>> _buttons;
    std::unique_ptr<Fl_Input> _input;
    uint64_t _value;
    std::unique_ptr<Fl_Button> _label;
private:
    void OnInputChanged(Fl_Widget *w, void *data);
    void OnButtonPresed(Fl_Widget *w, void *data, int index);
};

Digit::Digit(Fl_Input* input, Fl_Button* label, int ypos): _input(input), _label(label) {
    {
        std::function<void(Fl_Widget *, void *)> func = std::bind(&Digit::OnInputChanged, this, std::placeholders::_1, std::placeholders::_2);
        //auto cmp = *func.target<void(*)(Fl_Widget *, void *)>();
        _input->callback((Fl_Callback *)&func);
        _input->when(FL_WHEN_CHANGED);
    }

    _buttons.resize(sizeof(_value) * 8);
    for (int64_t i = 0; i < sizeof(_value) * 8; i++) {
        _buttons[i] = std::make_unique<Fl_Button>(30 + i * (0 * 25 + 15), ypos, 15 + 25 * 0, 20, "0");
        std::function<void(Fl_Widget*, void*)> func = std::bind(&Digit::OnButtonPresed, this, std::placeholders::_1, std::placeholders::_2, i);
        _buttons[i]->callback((Fl_Callback *)&func);
    }
}

void Digit::OnInputChanged(Fl_Widget *w, void *data) {
    sscanf(_input->value(), "%ld", &_value);
    for (int64_t i = 0; i < 64; i++) {
        auto bit = (_value & (static_cast<uint64_t>(1) << (63 - i))) == 1;
        _buttons[i]->label(bit ? "1" : "0");
    }
    _value=0;
}

void Digit::OnButtonPresed(Fl_Widget *w, void *data, int index) {
    auto& button = _buttons[index];
    if (!button)
    {
        return;
    }

    const char *currentText = button->label();
    if (strcmp(currentText, "1") == 0)
    {
        button->label("0");
        _value -= (int64_t)1 << index;
    }
    else
    {
        button->label("1");
        _value += (int64_t)1 << index;
    }
    char s[100];

    switch(SYST){
        case 0:
            sprintf(s,"%o", _value);
            break;
        case 2:
            sprintf(s,"%ld", _value);
            break;
        case 1:
            sprintf(s,"%x", _value);
            break;
    }
    _input->value(s);
}

std::vector<Digit> digits;

//std::vector<std::string> op = {"+", "-", "*", "/", "%", "<<", ">>", "~A", "~B", "&", "|", "^"};
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
    sscanf(vA->value(), "%ll", &VA);
    sscanf(vB->value(), "%ll", &VB);
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
            sprintf(s,"%ll", VC);
            break;
    }
    vC->value(s);
    for (int64_t i = 0; i < 64; i++) {
        auto setBit = [&](auto& digit, auto& button)
        {
            int64_t bit = (digit & (static_cast<uint64_t>(1) << (63 - i))) ? 1 : 0;
            button[i]->label(bit ? "1" : "0");
        };

        setBit(VA, A[0]);
        setBit(VB, B[0]);
        setBit(VC, C[0]);

        /*int64_t bit = (VA & (static_cast<uint64_t>(1) << (63 - i))) ? 1 : 0;
        A[0][i]->label(bit ? "1" : "0");

        int64_t bit2 = (VC & (static_cast<uint64_t>(1) << (63 - i))) ? 1 : 0;
        C[0][i]->label(bit2 ? "1" : "0");

        int64_t bit3 = (VB & (static_cast<uint64_t>(1) << (63 - i))) ? 1 : 0;
        B[0][i]->label(bit3 ? "1" : "0");*/
    }
}

void cb_c(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VC = 0;
    char s[100];
    int64_t val1;
    for (int64_t i = 0; i < 64; i++) {
        val1 = (strcmp(C[0][63-i]->label(),"1")==0)?1:0;
        VC += val1 * (static_cast<uint64_t>(1) << i);
        switch(SYST){
            case 0:
                sprintf(s,"%o", VC);
                break;
            case 1:
                sprintf(s,"%x", VC);
                break;
            case 2:
                sprintf(s,"%ll", VC);
                break;
        }
        vC->value(s);
    }
}

void cb_a(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VA = 0;
    char s1[100];
    int64_t val1;
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for (int64_t i = 0; i < 64; i++) {
        val1 = (strcmp(A[0][63-i]->label(),"1")==0)?1:0;
        VA += val1 * (static_cast<uint64_t>(1) << i);
        switch(SYST){
            case 0:
                sprintf(s1,"%o", VA);
                break;
            case 1:
                sprintf(s1,"%x", VA);
                break;
            case 2:
                sprintf(s1,"%ll", VA);
                break;
        }
        vA->value(s1);
    }
}

void cb_b(Fl_Button *w, void *data) {
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    VB = 0;
    char s2[100];
    int64_t val2;
    if (button) {
        const char *currentText = button->label();
        if (strcmp(currentText, "1") == 0) {
            button->label("0");
        } else if (strcmp(currentText, "0") == 0) {
            button->label("1");
        }
    }
    for (int64_t i = 0; i < 64; i++) {
        val2 = (strcmp(B[0][63-i]->label(),"1")==0)?1:0;
        VB += val2 * (static_cast<uint64_t>(1) << i);
        switch(SYST){
            case 0:
                    sprintf(s2,"%o", VB);
                    break;
            case 1:
                    sprintf(s2,"%x", VB);
                    break;
            case 2:
                    sprintf(s2,"%ll", VB);
                    break;
        }
        vB->value(s2);
    }
}


void cb_vA(Fl_Widget *w, void *data) {
    sscanf(vA->value(), "%ll", &VA);
    int64_t bit = 0;
    for (int64_t i = 0; i < 64; i++) {
        //sscanf(vA->value(), "%ll", &VA);
        bit = (VA & (static_cast<uint64_t>(1) << (63 - i))) ? 1 : 0;
        A[0][i]->label(bit ? "1" : "0");
    }
    VA=0;
}

void cb_vB(Fl_Widget *w, void *data) {
    sscanf(vB->value(), "%ll", &VB);
    for (int64_t i = 0; i < 64; i++) {
        int64_t bit = (VB & (static_cast<uint64_t>(1) << (63 - i))) ? 1 : 0;
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

    {
        auto label = new Fl_Button(5, 70, 25, 25, "A");
        label->box(FL_NO_BOX);
        auto input = new Fl_Input(300, 30, 100, 25, "A");
        digits.emplace_back(input, label, 70);
    }

    {
        auto label = new Fl_Button(5, 110, 25, 25, "B");
        label->box(FL_NO_BOX);
        auto input = new Fl_Input(450, 30, 100, 25, "B");
        digits.emplace_back(input, label, 110);
    }

    {
        auto label = new Fl_Button(5, 150, 25, 25, "C");
        label->box(FL_NO_BOX);
        auto input = new Fl_Input(600, 30, 100, 25, "C");
        digits.emplace_back(input, label, 150);
    }

    for (int i = 0; i < nops; i++) {
        Op[i] = new Fl_Button(30 + i * 40, 200, 40, 30, op[i]);
        Op[i]->callback((Fl_Callback *) cb_op);
    }

    w->end();
    w->show(argc, argv);
    return Fl::run();
}