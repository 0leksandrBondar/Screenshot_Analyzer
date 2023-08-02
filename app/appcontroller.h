#pragma once

#include "dbmanager/dbmanager.h"

#include <QObject>

#include <memory>

class TableView;
class ControlBar;
class ScreenshotController;

class QTimer;

class AppController : public QObject
{
    Q_OBJECT
public:
    AppController(const int width, const int height, QWidget *parent = nullptr);
    ~AppController();

    void startTimer();
    void loadDataFromDb();
    void addLatestImageToTable(const int id);

public slots:
    void updateAndSaveScreenshot();

private:
    void updateDatabase(QPixmap currentScreenshot);
    void compareAndSaveSimilarity(QImage currentScreenshot);

private:
    void setupUi(QWidget *parent);

    bool _isTimerRunning{ false };
    const int _timeToScreen{ 60000 };
    std::unique_ptr<QTimer> _timer;
    std::unique_ptr<DBManager> _dbManager;
    std::unique_ptr<TableView> _tableView;
    std::unique_ptr<ControlBar> _controlBar;
    std::unique_ptr<ScreenshotController> _screenController;
};
