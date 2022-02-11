#ifndef TREND_H
#define TREND_H

#include <QWidget>
#include <QGraphicsTextItem>
#include <QDomDocument>
#include <QTimer>
#include <QTimer>
#include <QElapsedTimer>
#include "plot.h"

namespace Ui {
class trend;
}

class trend : public QWidget
{
    Q_OBJECT

public:
    explicit trend(QWidget *parent = nullptr);
    ~trend();

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_pushButton_clicked();

private:
    Ui::trend *ui;
    QDomDocument doc,doc3,doc4;
    QTimer timer;
     double t;
};

#endif // TREND_H
