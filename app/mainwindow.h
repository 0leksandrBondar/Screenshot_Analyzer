#pragma once

#include <QMainWindow>

class AppController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const int width, const int height);
    ~MainWindow();

};
