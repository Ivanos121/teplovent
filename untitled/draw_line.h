#ifndef DRAW_LINE_H
#define DRAW_LINE_H

#include <QWidget>
#include <QWidget>
#include <QGraphicsTextItem>
#include <QDomDocument>

namespace Ui {
class draw_line;
}

class draw_line : public QWidget
{
    Q_OBJECT

public:
    explicit draw_line(QWidget *parent = nullptr);
    ~draw_line();

private:
    Ui::draw_line *ui;
    QDomDocument doc, doc2;
};

#endif // DRAW_LINE_H
