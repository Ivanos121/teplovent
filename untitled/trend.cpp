#include "trend.h"
#include "ui_trend.h"

#include "cmath"
#include "plot.h"
#include <math.h>
#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

int position_2;
double t_max;

trend::trend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trend),
    t(0.0)
{
    ui->setupUi(this);

    ui->plot->t_max = 10000;
    ui->plot->U_max = 200.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    ui->plot->addDataLine(QColor(255,0,0), 0);   //станина
    ui->plot->addDataLine(QColor(255,255,0), 0); //подшипниковый узел справа сзади
    ui->plot->addDataLine(QColor(0,255,0), 0);   //лобовая часть слева спереди
    ui->plot->addDataLine(QColor(0,0,255), 0);   //подшипниковый узел слева спереди
    ui->plot->addDataLine(QColor(255,102,0), 0); //лобовая часть слева сзади
    ui->plot->addDataLine(QColor(255,0,255), 0); //станина
    ui->plot->addDataLine(QColor(255,55,55), 0); //лобовая часть справа спереди
    ui->plot->addDataLine(QColor(255,0,0), 0);//лобовая часть справа сзади
    ui->plot->addDataLine(QColor(255,0,0), 0);//станина
    ui->plot->addDataLine(QColor(255,0,0), 0);//лобовая часть справа спереди
    ui->plot->addDataLine(QColor(255,0,0), 0);//лобовая часть справа сзади
    t=0;
    connect(&timer, &QTimer::timeout, this, &trend::on_pushButton_clicked);
    //timer.start(0);



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

    ui->tableWidget->setRowCount(12);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Сигнал" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->resizeColumnsToContents();


    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("станина"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("подшипниковый узел справа сзади"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("лобовая часть слева спереди"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("подшипниковый узел слева спереди"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Полная мошность фазы А, ВАР"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Коэффициент мощности фазы А"));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Ток фазы В, А"));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Напряжение фазы В, В"));
    ui->tableWidget->setItem(8, 0, new QTableWidgetItem("Активная мошность фазы В, Вт"));
    ui->tableWidget->setItem(9, 0, new QTableWidgetItem("Реактивная мошность фазы В, ВА"));
    ui->tableWidget->setItem(10, 0, new QTableWidgetItem("Полная мошность фазы В, ВАР"));
    ui->tableWidget->setItem(11, 0, new QTableWidgetItem("Коэффициент мощности фазы В"));
    ui->tableWidget->setItem(12, 0, new QTableWidgetItem("Ток фазы С, А"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

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

    root = doc3.firstChildElement();

    elemText = root.elementsByTagName("tspan");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.firstChild().nodeValue();
            e.firstChild().setNodeValue(QString("%1").arg(position*1.4));
            if (e.attribute("id") == QString("tspan7974"))
            {
              e.setAttribute("style", "");
              qDebug() << "way 1" << e.nodeValue();
            }

        }

    }
    ui->svgWidget2->load(doc3.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget2->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
}

void trend::on_pushButton_clicked()
{
    double y1=20*(1-exp(-t/2000))+ui->lineEdit->text().toDouble();
    double y2=120*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y3=220*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y4=320*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y5=420*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y6=520*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y7=620*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y8=820*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y9=920*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y10=1020*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();
    double y11=1120*(1-exp(-t/2500))+ui->lineEdit->text().toDouble();

    timer.start(0);
    ui->plot->addPoint(0, t, y1);
    ui->plot->addPoint(1, t, y2);
    ui->plot->addPoint(2, t, y3);
    ui->plot->addPoint(3, t, y4);
    ui->plot->addPoint(4, t, y5);
    ui->plot->addPoint(5, t, y6);
    ui->plot->addPoint(6, t, y7);
    ui->plot->addPoint(7, t, y8);
    ui->plot->addPoint(8, t, y9);
    ui->plot->addPoint(9, t, y10);
    ui->plot->addPoint(10, t, y11);


    t += 1.0 ;


    int color = 235 - y1 / 100.0 * 220.0;
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

    root = doc3.firstChildElement();

    elemText = root.elementsByTagName("tspan");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.firstChild().nodeValue();
            e.firstChild().setNodeValue(QString("%1").arg(y1));
            if (e.attribute("id") == QString("tspan7974"))
            {
              e.setAttribute("style", "");

            }

        }

    }
    ui->svgWidget2->load(doc3.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget2->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
//    if(t>t_max)
//    {
//        timer.stop();
//    }
}


void trend::on_pushButton_2_clicked()
{
    timer.stop();
}

