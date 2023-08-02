#include "controlbar.h"

#include <QHBoxLayout>
#include <QPushButton>

ControlBar::ControlBar(const int width, const int height, QWidget *parent)
    : QWidget(parent), _controlButton(std::make_unique<QPushButton>(QStringLiteral("Start"), this))
{
    setGeometry(0, height * 0.8, width, height * 0.2);

    connect(_controlButton.get(), &QPushButton::clicked, this, &ControlBar::startCliked);

    setupUi();
}

ControlBar::~ControlBar() {}

void ControlBar::setupUi()
{
    _controlButton->setFixedSize(100, 50);

    auto layout = new QHBoxLayout(this);
    layout->addWidget(_controlButton.get(), 0, Qt::AlignCenter);
}

void ControlBar::startCliked()
{
    _isRecording = !_isRecording;
    _controlButton->setText(_isRecording ? QStringLiteral("Stop") : QStringLiteral("Start"));
    emit onStartClicked();
}
