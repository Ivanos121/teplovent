#include "draw_poper.h"
#include "ui_draw_poper.h"

#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

draw_poper::draw_poper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_poper)
{
    ui->setupUi(this);

    ui->widget_2->setStyleSheet("QSvgWidget {background-color: white; border: 1px; border-style: solid; border-color: #c4c8cc;}");

    QFile file("../data/rad_var.svg");

    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    ui->widget_2->load(doc.toByteArray());
    QSvgRenderer *renderer = ui->widget_2->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);

    ui->widget->setStyleSheet("QSvgWidget {background-color: white; border: 1px; border-style: solid; border-color: #c4c8cc;}");

    QFile file2("grad_line.svg");

    if (!file2.open(QIODevice::ReadOnly))
        return;
    if (!doc2.setContent(&file2))
    {
        file2.close();
        return;
    }
    file2.close();

    ui->widget->load(doc2.toByteArray());
    QSvgRenderer *renderer2 = ui->widget->renderer();
    renderer2->setAspectRatioMode(Qt::KeepAspectRatio);
}

draw_poper::~draw_poper()
{
    delete ui;
}
