#include "appcontroller.h"
#include "screencontroller.h"
#include "widgets/controlbar.h"
#include "widgets/tableview.h"

#include <thread>

#include <QBuffer>
#include <QTimer>
#include <QVBoxLayout>

AppController::AppController(const int width, const int height, QWidget *parent)
    : _timer{ std::make_unique<QTimer>() },
      _dbManager{ std::make_unique<DBManager>() },
      _tableView{ std::make_unique<TableView>(width, height, parent) },
      _controlBar{ std::make_unique<ControlBar>(width, height, parent) },
      _screenController{ std::make_unique<ScreenshotController>() }

{
    setupUi(parent);
    loadDataFromDb();

    connect(_timer.get(), &QTimer::timeout, this, &AppController::updateAndSaveScreenshot);
    connect(_controlBar.get(), &ControlBar::onStartclicked, this, &AppController::startTimer);
}

AppController::~AppController() {}

void AppController::startTimer()
{
    if (_isTimerRunning)
    {
        _timer->stop();
        _isTimerRunning = false;
    }
    else
    {
        _timer->start(_timeToScreen);
        _isTimerRunning = true;
    }
}

/*!
 * \brief AppController::addLatestImageToTable updates the user table after updating the database
 */
void AppController::addLatestImageToTable(const int id)
{
    const DBManager::ImageData imageData = _dbManager->imageData(id);
    _tableView->initRow(imageData.image, imageData.hashSum, imageData.similarity);
}

/*!
 * \brief AppController::updateAndSaveScreenshot creates a new screenshot
 * and writes this screenshot to the database, calculates the similarity to the previous screenshot
 */
void AppController::updateAndSaveScreenshot()
{
    const QPixmap currentScreenshot = _screenController->makeScreenshot();

    insertLastScreenToDb(currentScreenshot);

    std::thread compareThread([=]() {
        const QImage currentScreen = currentScreenshot.toImage();
        compareAndSaveSimilarity(currentScreen);
        calcAndWriteHashSum(currentScreenshot);
        addLatestImageToTable(_dbManager->lastId());
    });

    compareThread.detach();
}

void AppController::insertLastScreenToDb(const QPixmap &currentScreenshot)
{
    _dbManager->insertImageInToDataBase(currentScreenshot);
}

void AppController::compareAndSaveSimilarity(QImage currentScreenshot)
{
    const DBManager::ImageData imageData = _dbManager->imageData(_dbManager->lastId() - 1);
    const QImage prevImage = imageData.image;

    const float similarityPercentage = _screenController->compareImages(std::move(
                                                                            currentScreenshot),
                                                                        std::move(prevImage));

    _dbManager->insertSimilarityBetweenImages(similarityPercentage, _dbManager->lastId());
}

void AppController::calcAndWriteHashSum(const QPixmap &currentScreenshot)
{
    _screenController->initHashSum(currentScreenshot);
    _dbManager->insertHashSumInToDataBase(_screenController->hashSum(), _dbManager->lastId());
}

void AppController::setupUi(QWidget *parent)
{
    QVBoxLayout *layout = new QVBoxLayout(parent);

    layout->addWidget(_tableView.get());
    layout->addWidget(_controlBar.get());
}

/*!
 * \brief AppController::loadDataFromDb during loading the app takes current data from the database
 */
void AppController::loadDataFromDb()
{
    const auto imagesData{ _dbManager->loadData() };
    for (const auto &imageData : imagesData)
    {
        _tableView->initRow(imageData.image, imageData.hashSum, imageData.similarity);
    }
}
