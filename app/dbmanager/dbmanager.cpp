#include "dbmanager.h"

#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

DBManager::DBManager() : _db{ QSqlDatabase::addDatabase(QStringLiteral("QSQLITE")) }
{
    _db.setDatabaseName(QStringLiteral("dataBase.db"));
    QSqlQuery query(_db);

    if (!_db.open())
    {
        qWarning() << QStringLiteral("Database not open. Error: ") << _db.lastError().text();
    }
    else
    {
        query.exec(QStringLiteral(
            "CREATE TABLE IF NOT EXISTS images (id INTEGER PRIMARY KEY, image, hash_sum BLOB"
            "BLOB, similarity REAL)"));
    }
}

DBManager::~DBManager()
{
    if (_db.isOpen())
    {
        _db.close();
    }
}

int DBManager::newId() const
{
    QSqlQuery maxIdQuery("SELECT MAX(id) FROM images", _db);

    if (maxIdQuery.exec() && maxIdQuery.next())
    {
        auto maxId = maxIdQuery.value(0).toInt();
        return ++maxId;
    }

    return 0;
}

void DBManager::insertImageInToDataBase(QPixmap pixmap)
{
    QSqlQuery query(_db);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);

    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG");

    const int nextId = newId();

    query.prepare(
        QStringLiteral("INSERT INTO images (id, image)"
                       "VALUES (:id, :image)"));

    query.bindValue(":id", nextId);
    query.bindValue(":image", byteArray);

    if (query.exec())
    {
        qDebug() << "Insertion in image is successful";
    }
    else
    {
        qDebug("Insertion image is unsuccessful");
        qDebug() << "Query error: " << query.lastError().text();
    }
}

void DBManager::insertHashSumInToDataBase(const QByteArray &hashSum, const int id)
{
    QSqlQuery query(_db);

    query.prepare(QStringLiteral("UPDATE images SET hash_sum = :hash_sum WHERE id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":hash_sum", hashSum);

    if (query.exec())
    {
        qDebug("Update hash_sum is successful");
    }
    else
    {
        qDebug("Update hash_sum  is unsuccessful");
        qDebug() << "Query error: " << query.lastError().text();
    }
}

void DBManager::insertSimilarityBetweenImages(const float similarity, const int id) const
{
    QSqlQuery query(_db);

    query.prepare(QStringLiteral("UPDATE images SET similarity = :similarity WHERE id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":similarity", similarity);

    if (query.exec())
    {
        qDebug("Update similarity is successful");
    }
    else
    {
        qDebug("Update similarity is unsuccessful");
        qDebug() << "Query error: " << query.lastError().text();
    }
}

DBManager::ImageData DBManager::imageData(const int id) const
{
    QSqlQuery query(_db);
    ImageData tmpImageData;

    query.prepare("SELECT id, image, hash_sum, similarity FROM images WHERE id = :id");
    query.bindValue(QStringLiteral(":id"), id);

    if (query.exec() && query.next())
    {
        tmpImageData.currentId = query.value(0).toInt();

        QByteArray byteArray = query.value(1).toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(byteArray);
        tmpImageData.image = pixmap.toImage();

        tmpImageData.hashSum = query.value(2).toByteArray();
        tmpImageData.similarity = query.value(3).toFloat();
    }
    else
    {
        qDebug("Reading latest image from database is unsuccessful");
    }

    return tmpImageData;
}

std::vector<DBManager::ImageData> DBManager::loadData() const
{
    std::vector<ImageData> data;

    QSqlQuery query(QStringLiteral("SELECT id, image, hash_sum, similarity FROM images"), _db);

    while (query.next())
    {
        ImageData imageData;
        const QByteArray byteArray = query.value(1).toByteArray();
        QPixmap pixmap;

        pixmap.loadFromData(byteArray);

        imageData.currentId = query.value(0).toInt();
        imageData.image = pixmap.toImage();
        imageData.hashSum = query.value(2).toByteArray();
        imageData.similarity = query.value(3).toFloat();

        data.push_back(imageData);
    }

    return data;
}

int DBManager::lastId() const
{
    QSqlQuery maxIdQuery(QStringLiteral("SELECT MAX(id) FROM images"), _db);

    if (maxIdQuery.exec() && maxIdQuery.next())
    {
        return maxIdQuery.value(0).toInt();
    }

    return 0;
}
