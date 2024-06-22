#include "mainwidget.h"

#include <QHBoxLayout>
#include <QIntValidator>

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent},
    _canvas(new DrawWidget(this)),
    _button(new QPushButton(this)),
    _edit(new QLineEdit(this)),
    _editsqe(new QLineEdit(this)),
    _alp(new QLineEdit(this)),
    _timer(new QTimer(this)),
    _system(new QPushButton(this))
{
    InitLayout();
    InitConnections();
}

void MainWidget::InitLayout()
{
    auto layout = new QHBoxLayout(this);
    layout->addWidget(_canvas);
    layout->setContentsMargins(0, 0, 0, 0);

    _button->setText("Старт");

    _system->move(0, 40);
    _system->setText("Изменить систему");

    _edit->move(0, 80);
    _edit->setValidator(new QIntValidator(1, 15, this));
    _edit->setText("Масштаб");

    _editsqe->move(0, 120);
    _editsqe->setValidator(new QIntValidator(5, 50, this));
    _editsqe->setText("Квадрат");

    _alp->move(0, 160);
    _alp->setValidator(new QIntValidator(5, 100, this));
    _alp->setText("Коэффицент");

    setLayout(layout);
}

void MainWidget::InitConnections()
{
    connect(_edit, &QLineEdit::editingFinished, [this](){
        _canvas->SetA(_edit->text().toDouble());
        _canvas->update();
    });

    connect(_editsqe, &QLineEdit::editingFinished, [this](){
        _canvas->SetS(_editsqe->text().toDouble());
        _canvas->update();
    });

    connect(_timer, &QTimer::timeout, _canvas, &DrawWidget::MoveS);

    connect(_button, &QPushButton::clicked, [this]() {
        _canvas->ResetSquarePosition();
        _timer->start(1);
    });

    connect(_alp, &QLineEdit::editingFinished, [this](){
        _canvas->SetAlp(_alp->text().toDouble());
        _canvas->update();
    });

    connect(_system, &QPushButton::clicked, [this](){
        _canvas->SetSystem();
        _canvas->update();
    });
}
