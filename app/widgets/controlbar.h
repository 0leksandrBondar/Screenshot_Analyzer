#pragma once

#include <QElapsedTimer>
#include <QWidget>

#include <memory>

class QLabel;
class QTimer;
class QPushButton;

class ControlBar : public QWidget
{
    Q_OBJECT
public:
    ControlBar(const int width, const int height, QWidget *parent = nullptr);
    ~ControlBar();

    void setupUi();
    void updateTime();
signals:
    void onStartclicked();

private:
    const int _timeToUpdate{ 1000 };
    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<QLabel> _timerLabel;
    std::unique_ptr<QPushButton> _controlButton;

    QElapsedTimer _elapsedTimer;
};
