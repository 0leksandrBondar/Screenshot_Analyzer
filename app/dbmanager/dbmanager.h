#pragma once

#include <QImage>
#include <QObject>
#include <QSqlDatabase>

class DBManager : public QObject
{
    Q_OBJECT
public:
    struct ImageData
    {
        int currentId;
        int hashSum;
        QImage image;
        float similarity;
    };

    DBManager();
    ~DBManager();

    int newId() const;
    int lastId() const;
    ImageData imageData(const int id) const;
    std::vector<ImageData> loadData() const;

    void insertImageInToDataBase(QPixmap pixmap);
    void insertHashSumInToDataBase(const int hashSum, const int id);
    void insertSimilarityBetweenImages(const float similarity, const int id) const;

private:
    QSqlDatabase _db;
};
