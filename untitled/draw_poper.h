#ifndef DRAW_POPER_H
#define DRAW_POPER_H

#include <QWidget>
#include <QGraphicsTextItem>
#include <QDomDocument>

namespace Ui {
class draw_poper;
}

class draw_poper : public QWidget
{
    Q_OBJECT

public:
    explicit draw_poper(QWidget *parent = nullptr);
    ~draw_poper();

private:
    Ui::draw_poper *ui;
    QDomDocument doc;
};

#endif // DRAW_POPER_H
