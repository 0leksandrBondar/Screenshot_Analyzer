#include "controlbar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>

ControlBar::ControlBar(const int width, const int height, QWidget *parent)
    : QWidget(parent),
      _timer{ std::make_unique<QTimer>() },
      _timerLabel{ std::make_unique<QLabel>(QStringLiteral("Timer: 0.0")) },
      _controlButton(std::make_unique<QPushButton>(QStringLiteral("Start/Stop"), this))
{
    setGeometry(0, height * 0.8, width, height * 0.2);

    _timer->setInterval(_timeToUpdate / 7);
    _elapsedTimer.start();
    _timer->start();

    connect(_timer.get(), &QTimer::timeout, this, &ControlBar::updateTime);
    connect(_controlButton.get(), &QPushButton::clicked, this, &ControlBar::onStartclicked);

    setupUi();
}

ControlBar::~ControlBar() {}

void ControlBar::setupUi()
{
    _controlButton->setFixedSize(100, 50);

    QFont labelFont = _timerLabel->font();
    labelFont.setPointSize(20);
    _timerLabel->setFont(labelFont);

    auto layout = new QHBoxLayout(this);
    auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    layout->addItem(spacer);
    layout->addWidget(_controlButton.get(), 0, Qt::AlignRight);
    layout->addItem(spacer);
    layout->addWidget(_timerLabel.get(), 0, Qt::AlignCenter);
    layout->addItem(spacer);
}

void ControlBar::updateTime()
{
    qint64 elapsedMilliseconds = _elapsedTimer.elapsed();

    int minutes = elapsedMilliseconds / 60000;
    int seconds = (elapsedMilliseconds % 60000) / 1000;

    QString formattedTime
        = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));

    _timerLabel->setText("Timer: " + formattedTime);

    if (elapsedMilliseconds >= 59999)
    {
        _elapsedTimer.restart();
    }
}
