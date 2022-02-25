#ifndef DRAW_POPER_NEW_H
#define DRAW_POPER_NEW_H

#include <QWidget>

namespace Ui {
class draw_poper_new;
}

class draw_poper_new : public QWidget
{
    Q_OBJECT

public:
    explicit draw_poper_new(QWidget *parent = nullptr);
    ~draw_poper_new();

public:
    Ui::draw_poper_new *ui;
};

#endif // DRAW_POPER_NEW_H
