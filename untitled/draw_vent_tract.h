#ifndef DRAW_VENT_TRACT_H
#define DRAW_VENT_TRACT_H

#include <QWidget>
#include <QDomDocument>
#include <QTimer>

namespace Ui {
class draw_vent_tract;
}

class draw_vent_tract : public QWidget
{
    Q_OBJECT

public:
    explicit draw_vent_tract(QWidget *parent = nullptr);
    ~draw_vent_tract();

private slots:
    void setcolorincell(int row, int column);

private:
    Ui::draw_vent_tract *ui;
    QDomDocument doc,doc3,doc4;
    QTimer timer;
    double t;
    QVector<QColor> dataLineColors;

    double maxY2;
    double minY2;

    double count;
    double max;
};

#endif // DRAW_VENT_TRACT_H
