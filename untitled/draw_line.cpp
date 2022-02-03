#include "draw_line.h"
#include "ui_draw_line.h"

#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

draw_line::draw_line(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_line)
{
    ui->setupUi(this);

    ui->widget->setStyleSheet("QSvgWidget {background-color: white; border: 1px; border-style: solid; border-color: #c4c8cc;}");

    QFile file("bbb2.svg");

    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    ui->widget->load(doc.toByteArray());
    QSvgRenderer *renderer = ui->widget->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
}

draw_line::~draw_line()
{
    delete ui;
}
