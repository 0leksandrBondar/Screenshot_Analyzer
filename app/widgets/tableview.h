#pragma once

#include <QWidget>

#include <memory>

class QTableWidget;

class TableView : public QWidget
{
    Q_OBJECT
public:
    TableView(const int width, const int height, QWidget *parent = nullptr);

    void initRow(const QImage &image, const int hashSum, const float similarity);

private:
    void setupTableUi(const int width, const int height);
    std::unique_ptr<QTableWidget> _tableWidget;
};
