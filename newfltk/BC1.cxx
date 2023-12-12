//Создать функцию UpdateInput учитыват разрядность и систему счисления
//Создать функцию UpdateButtons учитыват разрядность и систему счисления
//Поправить работу системы счисления (просто меняем параметр SYST и вызываем updateInput и UpdateButtons)
//Поправить работут разрядности (просто меняем параметр разрядности и вызываем updateInput и UpdateButtons)
//Поправить операции (просто делаем операцию с прараметром value a и b, устанавливаем результат в c и вызываем updateInput и UpdateButtons)

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Widget.H>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <FL/Fl_Button.H>

const int nops = 12;
uint64_t VA,VB,VC;
Fl_Window *w;
Fl_Button *R, *S, *Op[nops],*lR,*lS;
Fl_Button *A[3][64], *B[3][64], *C[3][64];
Fl_Input *vA, *vB, *vC;

int RAZR = 0;
int SYST = 0;

static void cb_op(Fl_Widget *w, void *data);

class Digit
{
public:
    Digit(Digit&& other) noexcept;
    Digit(Fl_Input* input, Fl_Button* label, int ypos);
    ~Digit();
private:
    std::vector<std::unique_ptr<Fl_Button>> _buttons;
    std::unique_ptr<Fl_Input> _input = nullptr;
    uint64_t _value = 0;
    std::unique_ptr<Fl_Button> _label = nullptr;
private:
    void OnInputChanged(Fl_Widget *w, void *data);
    void OnButtonPressed(Fl_Widget *w, void *data, int index);
    static void OnSmtHappens(Fl_Widget* w, void* data);
    static std::map<Fl_Widget*, std::function<void(Fl_Widget*, void*)>> _funcs;
    void InitSubs();
};

std::map<Fl_Widget*, std::function<void(Fl_Widget*, void*)>> Digit::_funcs = {};

Digit::Digit(Fl_Input* input, Fl_Button* label, int ypos): _input(input), _label(label) {
    _input->when(FL_WHEN_CHANGED);
    _buttons.resize(64);
    for (int64_t i = 0; i < sizeof(_value) * 8; i++) {
        _buttons[i] = std::make_unique<Fl_Button>(30 + i * (0 * 25 + 15), ypos, 15 + 25 * 0, 20, "0");
    }

    InitSubs();
}

Digit::~Digit() {
    _funcs.erase(_input.get());

    for (auto& b : _buttons) {
        _funcs.erase(b.get());
    }
}

void Digit::OnInputChanged(Fl_Widget *w, void *data) {
    _value = 0;
    sscanf(_input->value(), "%ld", &_value);
    for (int64_t i = 0; i < 64; i++) {
        auto bit = (_value & (static_cast<uint64_t>(1) << (63 - i))) != 0;
        _buttons[i]->label(bit ? "1" : "0");
    }
}

void Digit::OnButtonPressed(Fl_Widget *w, void *data, int index) {
    auto& button = _buttons[index];
    if (!button)
    {
        return;
    }

    const char *currentText = button->label();
    if (strcmp(currentText, "1") == 0)
    {
        button->label("0");
        _value -= (int64_t)1 << (_buttons.size() - index - 1);
    }
    else
    {
        button->label("1");
        _value += (int64_t)1 << (_buttons.size() - index - 1);
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

void Digit::OnSmtHappens(Fl_Widget *w, void *data) {
    if (_funcs.count(w) == 0) {
        return;
    }

    _funcs[w](w, data);
}

Digit::Digit(Digit && other) noexcept{
    _buttons = std::move(other._buttons);
    _input = std::move(other._input);
    _value = other._value;
    other._value = 0;
    _label = std::move(other._label);
    InitSubs();
}

void Digit::InitSubs() {
    {
        _funcs[_input.get()] = [this](Fl_Widget* w, void* d){
            _input->value();
            OnInputChanged(w, d);
        };
        _input->callback(Digit::OnSmtHappens);
    }

    for (int64_t i = 0; i < _buttons.size(); i++) {
        _funcs[_buttons[i].get()] = [this, i](Fl_Widget* w, void* d){
            OnButtonPressed(w, d, i);
        };
        _buttons[i]->callback(Digit::OnSmtHappens);
    }
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