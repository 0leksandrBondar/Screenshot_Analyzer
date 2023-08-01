#include "mainwindow.h"
#include "appcontroller.h"

#include <QVBoxLayout>

MainWindow::MainWindow(const int width, const int height)
    : QMainWindow(), _appController{ std::make_unique<AppController>(width, height, this) }
{
    setFixedSize(width, height);
}

MainWindow::~MainWindow() {}
