#include "tableview.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QVBoxLayout>

TableView::TableView(const int width, const int height, QWidget *parent)
    : QWidget(parent), _tableWidget{ std::make_unique<QTableWidget>() }
{
    const int widgetWidth = qMin(width, maximumWidth());
    const int widgetHeight = qMin(height * 0.8, maximumHeight() * 0.8);

    resize(widgetWidth, widgetHeight);

    setupTableUi(widgetWidth, widgetHeight);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(_tableWidget.get());
    setLayout(layout);
}

void TableView::initRow(const QImage &image, const int hashSum, const float similarity)
{
    const int rowCount = _tableWidget->rowCount();
    const auto imageItem = new QTableWidgetItem();

    const auto similarityItem = new QTableWidgetItem(QString::number(similarity));
    const auto hashItem = new QTableWidgetItem(QString::number(hashSum));
    similarityItem->setTextAlignment(Qt::AlignCenter);
    hashItem->setTextAlignment(Qt::AlignCenter);

    _tableWidget->insertRow(rowCount);

    QPixmap pixmap = QPixmap::fromImage(image)
                         .scaled(_tableWidget->columnWidth(0),
                                 _tableWidget->verticalHeader()->defaultSectionSize(),
                                 Qt::KeepAspectRatioByExpanding);

    imageItem->setData(Qt::DecorationRole, pixmap);

    _tableWidget->setItem(rowCount, 0, imageItem);
    _tableWidget->setItem(rowCount, 1, hashItem);
    _tableWidget->setItem(rowCount, 2, similarityItem);
}

void TableView::setupTableUi(const int width, const int height)
{
    const int imageColumnWidth = width / 3;
    const int imageRowHeight = height / 4;
    const QStringList headersLabels = { QStringLiteral("Last screenshot"),
                                        QStringLiteral("hash sum"), QStringLiteral("similarity") };
    _tableWidget->setColumnCount(3);
    _tableWidget->setHorizontalHeaderLabels(headersLabels);
    _tableWidget->setContentsMargins(0, 0, 0, 0);
    _tableWidget->setFrameShape(QFrame::NoFrame);
    _tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _tableWidget->verticalHeader()->setDefaultSectionSize(imageRowHeight);

    for (int i = 0; i < _tableWidget->columnCount(); ++i)
    {
        _tableWidget->setColumnWidth(i, imageColumnWidth);
    }
}
