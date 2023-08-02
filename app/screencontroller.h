#pragma once

#include <QCryptographicHash>
#include <QObject>
#include <QPixmap>

#include <memory>

class QImage;
class QScreen;

class ScreenshotController : public QObject
{
    Q_OBJECT
public:
    ScreenshotController();
    ~ScreenshotController();

    QByteArray hashSum() const;
    QPixmap makeScreenshot();
    float compareImages(QImage image1, QImage image2);
    QByteArray makeHashSum(const QPixmap &image, QCryptographicHash::Algorithm hashAlgorithm);

    void initHashSum(const QPixmap &currnetScreen);

private:
    QByteArray _hashSum{ 0 };
    QPixmap _pixmap;
    std::unique_ptr<QScreen> _screen;
};
