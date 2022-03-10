#ifndef VENT_VAR_H
#define VENT_VAR_H

#include <QWidget>

namespace Ui {
class vent_var;
}

class vent_var : public QWidget
{
    Q_OBJECT

public:
    explicit vent_var(QWidget *parent = nullptr);
    ~vent_var();

public:
    Ui::vent_var *ui;
    void on_speed(int value);

    double speed;
};

#endif // VENT_VAR_H
