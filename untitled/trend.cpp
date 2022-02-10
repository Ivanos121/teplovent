#include "trend.h"
#include "ui_trend.h"

#include "cmath"
#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

int position_2;

trend::trend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trend)
{
    ui->setupUi(this);
    ui->label->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));

    ui->svgWidget2->setStyleSheet("QSvgWidget {background-color: white; border: 1px; border-style: solid; border-color: #c4c8cc;}");

    QFile file("color_pr.svg");

    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc3.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    ui->svgWidget2->load(doc3.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget2->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
}



trend::~trend()
{
    delete ui;
}


void trend::on_horizontalSlider_sliderMoved(int position)
{
    int color = 235 - position / 100.0 * 220.0;
    ui->label->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color));

    QDomElement root = doc3.firstChildElement();

    QDomNodeList elemText = root.elementsByTagName("rect");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            if (e.attribute("id") == QString("rect1257"))
            {
               QColor col = QColor::fromHsl(color,255,140);
               QString col_text = QString("#%1%2%3").arg(col.red(),2,16).arg(col.green(),2,16).arg(col.blue(),2,16);
               e.setAttribute("style", QString("fill:") + col_text + QString(";fill-opacity:1;stroke:#000000;stroke-width:0.26379;stroke-miterlimit:4;stroke-dasharray:none;stroke-opacity:1"));
            }


        }
            ui->svgWidget2->load(doc3.toByteArray());
            QSvgRenderer *renderer = ui->svgWidget2->renderer();
            renderer->setAspectRatioMode(Qt::KeepAspectRatio);
        }

    position_2=position;
    //qDebug() << position_2;
}


void trend::on_pushButton_clicked()
{
    QDomElement root = doc3.firstChildElement();

    QDomNodeList elemText = root.elementsByTagName("text");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            if (e.attribute("id") == QString("text19208"))
            {
              e.setNodeValue(QString("%1").arg(position_2));
              qDebug() << "way 1" << e.nodeValue();
            }

        }
        ui->svgWidget2->load(doc3.toByteArray());
        QSvgRenderer *renderer = ui->svgWidget2->renderer();
        renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }
}

