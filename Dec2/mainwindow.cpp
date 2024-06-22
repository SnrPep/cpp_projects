#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _mainWidget(new MainWidget)
{
    setCentralWidget(_mainWidget);
}

MainWindow::~MainWindow() {}
