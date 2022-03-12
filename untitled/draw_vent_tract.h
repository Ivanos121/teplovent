#ifndef DRAW_VENT_TRACT_H
#define DRAW_VENT_TRACT_H

#include <QWidget>

namespace Ui {
class draw_vent_tract;
}

class draw_vent_tract : public QWidget
{
    Q_OBJECT

public:
    explicit draw_vent_tract(QWidget *parent = nullptr);
    ~draw_vent_tract();

private:
    Ui::draw_vent_tract *ui;
};

#endif // DRAW_VENT_TRACT_H
