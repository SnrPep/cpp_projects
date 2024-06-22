#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "drawwidget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    void InitLayout();
    void InitConnections();

private:
    DrawWidget* _canvas;
    QPushButton* _button;
    QPushButton* _system;
    QLineEdit* _edit;
    QLineEdit* _editsqe;
    QLineEdit* _alp;
    QTimer *_timer;

signals:
};

#endif // MAINWIDGET_H
