#pragma once

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

    int hashSum() const;
    QPixmap makeScreenshot();
    float compareImages(QImage image1, QImage image2);

private:
    int _hashSum{ 0 };
    QImage _image;
    QPixmap _pixmap;
    std::unique_ptr<QScreen> _screen;
};
