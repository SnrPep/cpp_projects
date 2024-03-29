#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Widget.H>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include <functional>
#include <FL/Fl_Button.H>

// создаются переменные
const int nops = 12; //константа
Fl_Window *w; //окно
Fl_Button *R, *S, *Op[nops],*lR,*lS;//кнопки

static void cb_op(Fl_Widget *w, void *data);

class Digit
{
public:
    enum class System{ //значения для переключения системы счисления
        OCT,
        DEC,
        HEX,
        MAX
    };
    enum class Capacity{ //значения для переключения разрядности
        INT8,
        INT16,
        INT32,
        INT64,
        MAX
    };
public: //создание класса
    Digit(Digit&& other) noexcept;//конструктор без значений
    Digit(Fl_Input* input, Fl_Button* label, int ypos);//конструктор со значениями
    ~Digit();//деструктор
    void SetSystem(System s);//функция смены системы
    void SetRazr(Capacity r);//функция смены разряда
    void SetValue(unsigned long long val);//функция для считывания значений
    unsigned long long GetValue();
private://создаются массивы кнопок
    std::vector<std::unique_ptr<Fl_Button>> _buttons;
    std::unique_ptr<Fl_Input> _input = nullptr;
    uint64_t _value = 0;
    std::unique_ptr<Fl_Button> _label = nullptr;
    System _sys = System::OCT;
    Capacity _razr = Capacity::INT64;
private://функции для обновления кнопок и окон ввода
    void OnInputChanged(Fl_Widget *w, void *data);
    void OnButtonPressed(Fl_Widget *w, void *data, int index);
    static void OnSmtHappens(Fl_Widget* w, void* data);
    static std::map<Fl_Widget*, std::function<void(Fl_Widget*, void*)>> _funcs;
    void InitSubs();
    void UpdateButtons();
    void UpdateInput();
};

std::map<Fl_Widget*, std::function<void(Fl_Widget*, void*)>> Digit::_funcs = {};

Digit::Digit(Fl_Input* input, Fl_Button* label, int ypos): _input(input), _label(label) { //код для конструктора
    _input->when(FL_WHEN_CHANGED);
    _buttons.resize(64);
    for (int64_t i = 0; i < sizeof(_value) * 8; i++) {
        _buttons[i] = std::make_unique<Fl_Button>(30 + i * (0 * 25 + 15), ypos, 15 + 25 * 0, 20, "0");
    }

    InitSubs();
}

Digit::~Digit() {//код для деструктора
    _funcs.erase(_input.get());

    for (auto& b : _buttons) {
        _funcs.erase(b.get());
    }
}

void Digit::OnInputChanged(Fl_Widget *w, void *data) {//код для обновления окна ввода при вводе в него значения
    _value = 0;
    switch(_sys){
        case System::OCT:
            sscanf(_input->value(), "%llo", &_value);
            break;
        case System::DEC:
            sscanf(_input->value(), "%lld", &_value);
            break;
        case System::HEX:
            sscanf(_input->value(), "%llx", &_value);
    }
    SetValue(_value);
    UpdateInput();
    UpdateButtons();
}

void Digit::OnButtonPressed(Fl_Widget *w, void *data, int index) {//код для переключения значения кнопок на 0 или 1
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

    UpdateInput();
}

void Digit::OnSmtHappens(Fl_Widget *w, void *data) {
    if (_funcs.count(w) == 0) {
        return;
    }
    _funcs[w](w, data);
}

Digit::Digit(Digit && other) noexcept{//код для конструктора без значений
    _buttons = std::move(other._buttons);
    _input = std::move(other._input);
    _value = other._value;
    other._value = 0;
    _label = std::move(other._label);
    InitSubs();
}

void Digit::InitSubs() {//обновление кнопок при вводе значения в окно ввода
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

void Digit::UpdateInput() {//код для обновления окна ввода при нажатии кнопок
    char s[100];

    switch(_sys){
        case System::OCT:
            sprintf(s,"%llo", _value);
            break;
        case System::DEC:
            sprintf(s,"%lld", _value);
            break;
        case System::HEX:
            sprintf(s,"%llx", _value);
    }
    _input->value(s);
}

void Digit::UpdateButtons() {//код для обновления кнопок при переключении системы или разрядности
    static std::map<Capacity, int> size = {
            {Capacity::INT8, 8},
            {Capacity::INT16, 16},
            {Capacity::INT32, 32},
            {Capacity::INT64, 64}
    };
    for (int64_t i = 0; i < 64; i++) {
        if (i < 64 - size[_razr])
        {
            _buttons[i]->hide();
            continue;
        }
        _buttons[i]->show();
        auto bit = (_value & (static_cast<uint64_t>(1) << (63 - i))) != 0;
        _buttons[i]->label(bit ? "1" : "0");
    }
}

void Digit::SetSystem(System s) {//код для переключения системы
    _sys = s;
    UpdateButtons();
    UpdateInput();
}

void Digit::SetRazr(Capacity r) {//код для переключения разряда
    _razr = r;
    SetValue(_value);
}

void Digit::SetValue(unsigned long long int val) {
    unsigned long long max_val = 0;
    switch (_razr) {
        case Capacity::INT8:
            max_val = std::numeric_limits<uint8_t>::max();
            break;
        case Capacity::INT16:
            max_val = std::numeric_limits<uint16_t>::max();
            break;
        case Capacity::INT32:
            max_val = std::numeric_limits<uint32_t>::max();
            break;
        case Capacity::INT64:
            max_val = std::numeric_limits<uint64_t>::max();
            break;
    }
    _value = std::clamp(val, (unsigned long long)(0), max_val);
    UpdateInput();
    UpdateButtons();
}

unsigned long long Digit::GetValue() {
    return _value;
}

std::vector<Digit> digits;
Digit::System SYST = Digit::System::OCT;
Digit::Capacity RAZR = Digit::Capacity::INT64;

const char *op[nops] = {"+", "-", "*", "/", "%", "<<", ">>", "~A", "~B", "&", "|", "^"};

void cb_R(Fl_Button *w, void *data) {//переключение системы
    RAZR = Digit::Capacity((int(RAZR) + 1) % int(Digit::Capacity::MAX));

    if (auto button = dynamic_cast<Fl_Button *>(w)) {
        if (RAZR == Digit::Capacity::INT8) {
            button->label("8");
        } else if (RAZR == Digit::Capacity::INT16) {
            button->label("16");
        } else if (RAZR == Digit::Capacity::INT32) {
            button->label("32");
        } else if (RAZR == Digit::Capacity::INT64) {
            button->label("64");
        }
    }

    for (auto& d : digits) {
        d.SetRazr(RAZR);
    }
}

void cb_S(Fl_Widget *w, void *data) {//переключение разряда
    SYST = Digit::System((int(SYST) + 1) % int(Digit::System::MAX));
    if (auto button = dynamic_cast<Fl_Button *>(w)) {
        if (SYST == Digit::System::DEC) {
            button->label("10");
        } else if (SYST == Digit::System::HEX) {
            button->label("16");
        } else if (SYST == Digit::System::OCT) {
            button->label("8");
        }
    }

    for (auto& d : digits) {
        d.SetSystem(SYST);
    }
}

static void cb_op(Fl_Widget *w, void *data) {//код для операций
    Fl_Button *button = dynamic_cast<Fl_Button *>(w);
    if (!button) return;
    const char *opLabel = button->label();

    if (strcmp(opLabel, "+") == 0) {
        digits[2].SetValue(digits[0].GetValue() + digits[1].GetValue());
    } else if (strcmp(opLabel, "-") == 0) {
        digits[2].SetValue(digits[0].GetValue() - digits[1].GetValue());
    } else if (strcmp(opLabel, "*") == 0) {
        digits[2].SetValue(digits[0].GetValue() * digits[1].GetValue());
    } else if (strcmp(opLabel, "/") == 0) {
        if (digits[1].GetValue() != 0) {
            digits[2].SetValue(digits[0].GetValue() / digits[1].GetValue());
        } else {
            digits[2].SetValue(0);
            return;
        }
    } else if (strcmp(opLabel, "%") == 0) {
        if (digits[1].GetValue() != 0) {
            digits[2].SetValue(digits[0].GetValue() % digits[1].GetValue());
        } else {
            digits[2].SetValue(0);
            return;
        }
    } else if (strcmp(opLabel, "<<") == 0) {
        digits[2].SetValue(digits[0].GetValue() << digits[1].GetValue());
    } else if (strcmp(opLabel, ">>") == 0) {
        digits[2].SetValue(digits[0].GetValue() >> digits[1].GetValue());
    } else if (strcmp(opLabel, "~A") == 0) {
        digits[2].SetValue(~digits[0].GetValue());
    } else if (strcmp(opLabel, "~B") == 0) {
        digits[2].SetValue(~digits[1].GetValue());
    } else if (strcmp(opLabel, "&") == 0) {
        digits[2].SetValue(digits[0].GetValue() & digits[1].GetValue());
    } else if (strcmp(opLabel, "|") == 0) {
        digits[2].SetValue(digits[0].GetValue() | digits[1].GetValue());
    } else if (strcmp(opLabel, "^") == 0) {
        digits[2].SetValue(digits[0].GetValue() ^ digits[1].GetValue());
    }
}

int main(int argc, char **argv) {
    w = new Fl_Window(1010, 250); //создается окно 1010 на 250
    w->resizable();
    if (w) {}
    {
        R = new Fl_Button(25, 25, 80, 35, "64"); //создается кнопка для переключения рязряда
        R->box(FL_NO_BOX);
        R->callback((Fl_Callback *)cb_R); //при нажатии кнопки разряда срабатывает ф-ия cb_R
    }
    {
        S = new Fl_Button(125, 25, 80, 35, "8"); //создается кнопка для переключения системы счисления
        S->box(FL_NO_BOX);
        S->callback((Fl_Callback *)cb_S);//при нажатии кнопки системы счисления срабатывает ф-ия cb_S
    }
    lR = new Fl_Button(25, 5, 80, 20, "Разряд"); //создается подпись для рязряда
    lR->box(FL_NO_BOX);
    lS = new Fl_Button(125, 5, 80, 20, "Система"); //создается подпись для системы счисления
    lS->box(FL_NO_BOX);

    {
        auto label = new Fl_Button(5, 70, 25, 25, "A"); //создается подпись для кнопок А
        label->box(FL_NO_BOX);
        auto input = new Fl_Input(300, 30, 100, 25, "A"); //создается окно для записи А
        digits.emplace_back(input, label, 70); //создается класс А при помощи подписи и окна ввода и указывается y координата
    }

    {
        auto label = new Fl_Button(5, 110, 25, 25, "B"); //создается подпись для кнопок В
        label->box(FL_NO_BOX);
        auto input = new Fl_Input(450, 30, 100, 25, "B"); //создается окно для записи В
        digits.emplace_back(input, label, 110); //создается класс В при помощи подписи и окна ввода и указывается y координата
    }

    {
        auto label = new Fl_Button(5, 150, 25, 25, "C"); //создается подпись для кнопок С
        label->box(FL_NO_BOX);
        auto inp = new Fl_Input(600, 30, 100, 25, "C"); //создается окно для записи С
        inp->readonly(true); //делает так чтобы в окно С нельзя было вводить значения
        digits.emplace_back(inp, label, 150); //создается класс С при помощи подписи и окна ввода и указывается y координата
    }

    for (int i = 0; i < nops; i++) {
        Op[i] = new Fl_Button(30 + i * 40, 200, 40, 30, op[i]); //создаются кнопки операций
        Op[i]->callback((Fl_Callback *) cb_op); //при нажатии кнопки операции срабатывает ф-ия cb_op
    }

    w->end();
    w->show(argc, argv);
    return Fl::run();
}