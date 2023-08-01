#pragma once

#include <QMainWindow>
#include <QPixmap>

#include <memory>

class AppController;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const int width, const int height);
    ~MainWindow();

private:
    std::unique_ptr<AppController> _appController;
};
