#include "screencontroller.h"
#include "qscreen.h"

#include <QBuffer>
#include <QDir>
#include <QGuiApplication>

ScreenshotController::ScreenshotController()
    : QObject(), _screen{ QGuiApplication::primaryScreen() }
{
}

ScreenshotController::~ScreenshotController() {}

/*!
 * \brief ScreenshotController::makeScreenshot takes a screenshot of the screen and returns it
 * \return QImage
 */
QPixmap ScreenshotController::makeScreenshot()
{
    const auto geometry = _screen->geometry();
    _pixmap = _screen->grabWindow(0, geometry.x(), geometry.y(), geometry.width(),
                                  geometry.height());
    return _pixmap;
}

/*!
 * \brief ScreenshotController::compareImages compares and calculates the number of distinct pixels
 * between two images
 */
float ScreenshotController::compareImages(QImage image1, QImage image2)
{
    if (image2.isNull() || image1.isNull())
        return 100.00;

    const int width = image1.width();
    const int height = image1.height();
    const double totalPixels = width * height;

    double differentPixels = 0;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            const QRgb pixel1 = image1.pixel(x, y);
            const QRgb pixel2 = image2.pixel(x, y);

            if (pixel1 != pixel2)
                ++differentPixels;
        }
    }

    const double differencePercentage = (differentPixels / totalPixels) * 100.0;

    const double similarityPercentage = 100.0 - differencePercentage;
    return qRound(similarityPercentage * 100) / 100;
}

QByteArray ScreenshotController::makeHashSum(const QPixmap &currnetScreen,
                                             QCryptographicHash::Algorithm hashAlgorithm)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);

    buffer.open(QIODevice::WriteOnly);
    currnetScreen.save(&buffer, "PNG");

    QCryptographicHash hash(hashAlgorithm);
    hash.addData(byteArray);
    return hash.result();
}

void ScreenshotController::initHashSum(const QPixmap &currnetScreen)
{
    _hashSum = makeHashSum(currnetScreen, QCryptographicHash::Algorithm::Md5);
}

QByteArray ScreenshotController::hashSum() const { return _hashSum; }
