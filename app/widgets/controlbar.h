#pragma once

#include <QElapsedTimer>
#include <QWidget>

#include <memory>

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
    void onStartClicked();

private:
    bool _isRecording{ false };
    void startCliked();
    std::unique_ptr<QPushButton> _controlButton;
};
