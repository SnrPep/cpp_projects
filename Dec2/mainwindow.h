#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainWidget* _mainWidget;
};
#endif // MAINWINDOW_H
