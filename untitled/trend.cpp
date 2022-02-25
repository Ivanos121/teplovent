#include "trend.h"
#include "ui_trend.h"

#include "cmath"
#include "plot.h"
#include <math.h>
#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>
#include "ui_mainwindow.h"
#include "ui_draw_poper.h"
#include "ui_draw_line_new.h"
#include "ui_draw_poper_new.h"

int position_2;
double t_max;

double y_0,y_1,y_2,y_3,y_4,y_5,y_6,y_7,y_8,y_9,y_10,y_11;
double a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11;
double b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11;


trend::trend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trend),
    t(0.0)
{
    maxY2 = 0;
    minY2 = 200;

    count = 0;

    ui->setupUi(this);

    //Настройки виджета Plot
    ui->plot->t_max = 10;
    ui->plot->U_max = 20.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

//    //добавление графов в виджет plot
//    ui->plot->addDataLine(QColor(255,0,0), 0);   //Станина
//    ui->plot->addDataLine(QColor(255,255,0), 0); //Подшипниковый узел справа сзади
//    ui->plot->addDataLine(QColor(0,255,0), 0);   //Лобовая часть слева спереди
//    ui->plot->addDataLine(QColor(0,0,255), 0);   //Подшипниковый узел слева спереди
//    ui->plot->addDataLine(QColor(255,102,0), 0); //Лобовая часть слева сзади
//    ui->plot->addDataLine(QColor(255,0,255), 0); //Станина
//    ui->plot->addDataLine(QColor(255,55,55), 0); //Лобовая часть справа спереди
//    ui->plot->addDataLine(QColor(55,10,220), 0); //Лобовая часть справа сзади
//    ui->plot->addDataLine(QColor(25,155,0), 0); //Магнитопровод статора
//    ui->plot->addDataLine(QColor(255,0,0), 0); //Подшипниковый узел справа спереди
//    ui->plot->addDataLine(QColor(255,0,0), 0); //Подшипниковый узел слева сзади

    connect(&timer, &QTimer::timeout, this, &trend::on_timer_timeout);

    //Первоначальная цветовая настройка лейблов
    ui->label->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_4->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_5->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_6->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_7->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_8->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_9->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_10->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_11->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_12->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_13->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_14->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));

    ui->svgWidget2->setStyleSheet("QSvgWidget {background-color: white; border: 1px; border-style: solid; border-color: #c4c8cc;}");


    QFile file("../data/color_pr.svg");

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
    ui->tableWidget->setColumnCount(3);
    QStringList name;
    name << " № " << "Сигнал" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<12; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tableWidget->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tableWidget->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget->setItem(5,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget->setItem(6,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget->setItem(8,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget->setItem(9,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

    ui->tableWidget_2->setRowCount(12); //задание количества строк таблицы
    ui->tableWidget_2->setColumnCount(6); //задание количества столбцов
    QStringList name5; //объявление указателя на тип QStringList
    name5 << "№" << "Цвет" << "Свойство" << "Значение" << "Масштабирование" << "Смещение"; //перечисление заголовков
    ui->tableWidget_2->setHorizontalHeaderLabels(name5); //установка заголовков в таблицу
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->resizeColumnsToContents();
    // ui->tableWidget_5->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    ui->tableWidget_2->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<12; i++)
    {
        if (ui->tableWidget_2->item(i, 0) != 0)
        {
            ui->tableWidget_2->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_2->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(i, 3) != 0)
        {
            ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget_2->item(i, 4) != 0)
        {
            ui->tableWidget_2->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget_2->item(i, 5) != 0)
        {
            ui->tableWidget_2->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_2->item(0, 2)->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *item51 = new QTableWidgetItem("Item51");
    item51->setCheckState(Qt::Checked);
    item51->setText("Станина, °C:");
    ui->tableWidget_2->setItem(0, 2, item51);

    QTableWidgetItem *item52 = new QTableWidgetItem("Item52");
    item52->setCheckState(Qt::Checked);
    item52->setText("Подшипниковый узел справа сзади, °C:");
    ui->tableWidget_2->setItem(1, 2, item52);

    QTableWidgetItem *item53 = new QTableWidgetItem("Item53");
    item53->setCheckState(Qt::Checked);
    item53->setText("Лобовая часть слева спереди, °C:");
    ui->tableWidget_2->setItem(2, 2, item53);

    QTableWidgetItem *item54 = new QTableWidgetItem("Item54");
    item54->setCheckState(Qt::Checked);
    item54->setText("Подшипниковый узел слева спереди, °C:");
    ui->tableWidget_2->setItem(3, 2, item54);

    QTableWidgetItem *item55 = new QTableWidgetItem("Item55");
    item55->setCheckState(Qt::Checked);
    item55->setText("Лобовая часть слева спереди, °C:");
    ui->tableWidget_2->setItem(4, 2, item55);

    QTableWidgetItem *item56 = new QTableWidgetItem("Item56");
    item56->setCheckState(Qt::Checked);
    item56->setText("Лобовая часть слева сзади, °C:");
    ui->tableWidget_2->setItem(5, 2, item56);

    QTableWidgetItem *item57 = new QTableWidgetItem("Item57");
    item57->setCheckState(Qt::Checked);
    item57->setText("Станина, °C:");
    ui->tableWidget_2->setItem(6, 2, item57);

    QTableWidgetItem *item58 = new QTableWidgetItem("Item58");
    item58->setCheckState(Qt::Checked);
    item58->setText("Лобовая часть справа спереди, °C:");
    ui->tableWidget_2->setItem(7, 2, item58);

    QTableWidgetItem *item59 = new QTableWidgetItem("Item59");
    item59->setCheckState(Qt::Checked);
    item59->setText("Лобовая часть справа сзади, °C:");
    ui->tableWidget_2->setItem(8, 2, item59);

    QTableWidgetItem *item60 = new QTableWidgetItem("Item60");
    item60->setCheckState(Qt::Checked);
    item60->setText("Магнитопровод статора, °C:");
    ui->tableWidget_2->setItem(9, 2, item60);

    QTableWidgetItem *item61 = new QTableWidgetItem("Item61");
    item61->setCheckState(Qt::Checked);
    item61->setText("Подшипниковый узел справа спереди, °C:");
    ui->tableWidget_2->setItem(10, 2, item61);

    QTableWidgetItem *item62 = new QTableWidgetItem("Item62");
    item62->setCheckState(Qt::Checked);
    item62->setText("Подшипниковый узел слева сзади, °C:");
    ui->tableWidget_2->setItem(11, 2, item62);

    ui->tableWidget_2->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(0,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(0, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(0,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(1,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(1, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(1,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(2,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(2, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(2,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(3,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(3, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(3,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(4,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(4, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(4,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(5,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(5, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(5,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(6,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(6, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(6,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(7,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(7, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(7,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(8,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(8, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(8,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(9, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(9,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(9, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(9,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(10, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(10,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(10, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(10,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(11, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(11,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(11, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(11,5)->setTextAlignment(Qt::AlignCenter);

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::magenta);
    dataLineColors.append(Qt::blue);
    dataLineColors.append(Qt::darkGreen);
    dataLineColors.append(Qt::darkBlue);
    dataLineColors.append(Qt::darkYellow);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);
    dataLineColors.append(Qt::darkRed);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
    }

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget_2->item(i, 1)->setBackground(dataLineColors[i]);
    }
    connect(ui->tableWidget_2, &QTableWidget::cellClicked,this, &trend::setcolorincell);
 }

void trend::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget_2->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget_2->item(row, column)->setBackground(chosenColor);
        ui->plot->setDataLineColor(row, chosenColor);
        dataLineColors[row] = chosenColor;
        repaint();
    }
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

    root = doc3.firstChildElement();

    elemText = root.elementsByTagName("text");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
             e.firstChild().setNodeValue(QString("%1").arg(position*1.4));
            if (e.attribute("id") == QString("text1926"))
            {
              e.setAttribute("style", "");
            }
        }
    }
    ui->svgWidget2->load(doc3.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget2->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
}

void trend::on_pushButton_clicked()
{
    y_0=20*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//станина
    y_1=54*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа сзади
    y_2=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева спереди
    y_3=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева спереди
    y_4=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева спереди
    y_5=112*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева сзади
    y_6=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//станина
    y_7=99*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть справа спереди
    y_8=111*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть справа сзади
    y_9=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Магнитопровод статора
    y_10=60*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа спереди
    y_11=56*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева сзади

    ui->plot->addPoint(0, t, y_0);
    ui->plot->addPoint(1, t, y_1);
    ui->plot->addPoint(2, t, y_2);
    ui->plot->addPoint(3, t, y_3);
    ui->plot->addPoint(4, t, y_4);
    ui->plot->addPoint(5, t, y_5);
    ui->plot->addPoint(6, t, y_6);
    ui->plot->addPoint(7, t, y_7);
    ui->plot->addPoint(8, t, y_8);
    ui->plot->addPoint(9, t, y_9);
    ui->plot->addPoint(10, t, y_10);
    ui->plot->addPoint(11, t, y_11);

    timer.start(1000);

    t += 10.0;
}


void trend::on_pushButton_2_clicked()
{
    timer.stop();
}

void trend::on_timer_timeout()
{
    y_0=20*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_1=54*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_2=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_3=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_4=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_5=112*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_6=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_7=99*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_8=111*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_9=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_10=60*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_11=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();

    if (mw->ui->widget_7->ui->tableWidget->item(0, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(y_0,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(1, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(y_1,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(2, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(y_2,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(3, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(y_3,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(4, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(y_4,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(5, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(y_5,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(6, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(y_6,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(7, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(y_7,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(8, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(9, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(y_9,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(10, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(y_10,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_7->ui->tableWidget->item(11, 2) != 0)
    {
        mw->ui->widget_7->ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_7->ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

    //вывод температур в таблицу draw_poper_new
    if (mw->ui->widget_8->ui->tableWidget->item(0, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(1, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(2, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(3, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(4, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(5, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(6, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(7, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(8, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(9, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(10, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (mw->ui->widget_8->ui->tableWidget->item(11, 2) != 0)
    {
        mw->ui->widget_8->ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        mw->ui->widget_8->ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

    a0=ui->tableWidget_2->item(0,4)->text().toDouble();
    a1=ui->tableWidget_2->item(1,4)->text().toDouble();
    a2=ui->tableWidget_2->item(2,4)->text().toDouble();
    a3=ui->tableWidget_2->item(3,4)->text().toDouble();
    a4=ui->tableWidget_2->item(4,4)->text().toDouble();
    a5=ui->tableWidget_2->item(5,4)->text().toDouble();
    a6=ui->tableWidget_2->item(6,4)->text().toDouble();
    a7=ui->tableWidget_2->item(7,4)->text().toDouble();
    a8=ui->tableWidget_2->item(8,4)->text().toDouble();
    a9=ui->tableWidget_2->item(9,4)->text().toDouble();
    a10=ui->tableWidget_2->item(10,4)->text().toDouble();
    a11=ui->tableWidget_2->item(11,4)->text().toDouble();

    b0=ui->tableWidget_2->item(0,5)->text().toDouble();
    b1=ui->tableWidget_2->item(1,5)->text().toDouble();
    b2=ui->tableWidget_2->item(2,5)->text().toDouble();
    b3=ui->tableWidget_2->item(3,5)->text().toDouble();
    b4=ui->tableWidget_2->item(4,5)->text().toDouble();
    b5=ui->tableWidget_2->item(5,5)->text().toDouble();
    b6=ui->tableWidget_2->item(6,5)->text().toDouble();
    b7=ui->tableWidget_2->item(7,5)->text().toDouble();
    b8=ui->tableWidget_2->item(8,5)->text().toDouble();
    b9=ui->tableWidget_2->item(9,5)->text().toDouble();
    b10=ui->tableWidget_2->item(10,5)->text().toDouble();
    b11=ui->tableWidget_2->item(11,5)->text().toDouble();

    if(ui->tableWidget_2->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(0, t, b0+a0*y_0);
    }

    if(ui->tableWidget_2->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(1, t, b1+a1*y_1);
    }

    if(ui->tableWidget_2->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(2, t, b2+a2*y_2);
    }

    if(ui->tableWidget_2->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(3, t, b3+a3*y_3);
    }

    if(ui->tableWidget_2->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(4, t, b4+a4*y_4);
    }

    if(ui->tableWidget_2->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(5, t, b5+a5*y_5);
    }

    if(ui->tableWidget_2->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(6, t, b6+a6*y_6);
    }

    if(ui->tableWidget_2->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(7, t, b7+a7*y_7);
    }

    if(ui->tableWidget_2->model()->index(8,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(8, t, b8+a8*y_8);
    }

    if(ui->tableWidget_2->model()->index(9,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(9, t, b9+a9*y_9);
    }

    if(ui->tableWidget_2->model()->index(10,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(10, t, b10+a10*y_10);
    }

    if(ui->tableWidget_2->model()->index(10,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(11, t, b11+a11*y_11);
    }

    t += 1.0;


    if (ui->tableWidget_2->item(0, 3) != 0)
    {
        ui->tableWidget_2->item(0, 3)->setText(QString("%1").arg(QString::number(b0+a0*y_0,'f',1)));
    }

    if (ui->tableWidget_2->item(1, 3) != 0)
    {
        ui->tableWidget_2->item(1, 3)->setText(QString("%1").arg(QString::number(b1+a1*y_1,'f',1)));
    }

    if (ui->tableWidget_2->item(2, 3) != 0)
    {
        ui->tableWidget_2->item(2, 3)->setText(QString("%1").arg(QString::number(b2+a2*y_2,'f',1)));
    }

    if (ui->tableWidget_2->item(3, 3) != 0)
    {
        ui->tableWidget_2->item(3, 3)->setText(QString("%1").arg(QString::number(b3+a3*y_3,'f',1)));
    }

    if (ui->tableWidget_2->item(4, 3) != 0)
    {
        ui->tableWidget_2->item(4, 3)->setText(QString("%1").arg(QString::number(b4+a4*y_4,'f',1)));
    }

    if (ui->tableWidget_2->item(5, 3) != 0)
    {
        ui->tableWidget_2->item(5, 3)->setText(QString("%1").arg(QString::number(b5+a5*y_5,'f',1)));
    }

    if (ui->tableWidget_2->item(6, 3) != 0)
    {
        ui->tableWidget_2->item(6, 3)->setText(QString("%1").arg(QString::number(b6+a6*y_6,'f',1)));
    }

    if (ui->tableWidget_2->item(7, 3) != 0)
    {
        ui->tableWidget_2->item(7, 3)->setText(QString("%1").arg(QString::number(b7+a7*y_7,'f',1)));
    }

    if (ui->tableWidget_2->item(8, 3) != 0)
    {
        ui->tableWidget_2->item(8, 3)->setText(QString("%1").arg(QString::number(b8+a8*y_8,'f',1)));
    }

    if (ui->tableWidget_2->item(9, 3) != 0)
    {
        ui->tableWidget_2->item(9, 3)->setText(QString("%1").arg(QString::number(b9+a9*y_9,'f',1)));
    }

    if (ui->tableWidget_2->item(10, 3) != 0)
    {
        ui->tableWidget_2->item(10, 3)->setText(QString("%1").arg(QString::number(b10+a10*y_10,'f',1)));
    }

    if (ui->tableWidget_2->item(11, 3) != 0)
    {
        ui->tableWidget_2->item(11, 3)->setText(QString("%1").arg(QString::number(b11+a11*y_11,'f',1)));
    }



    if (ui->tableWidget->item(0, 2) != 0)
    {
        ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(b0+a0*y_0,'f',1)));
        ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(1, 2) != 0)
    {
        ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(b1+a1*y_1,'f',1)));
        ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(2, 2) != 0)
    {
        ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(b2+a2*y_2,'f',1)));
        ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(3, 2) != 0)
    {
        ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(b3+a3*y_3,'f',1)));
        ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(4, 2) != 0)
    {
        ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(b4+a4*y_4,'f',1)));
        ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(5, 2) != 0)
    {
        ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(b5+a5*y_5,'f',1)));
        ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(6, 2) != 0)
    {
        ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(b6+a6*y_6,'f',1)));
        ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(7, 2) != 0)
    {
        ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(b7+a7*y_7,'f',1)));
        ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(8, 2) != 0)
    {
        ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(b8+a8*y_8,'f',1)));
        ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(9, 2) != 0)
    {
        ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(b9+a9*y_9,'f',1)));
        ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(10, 2) != 0)
    {
        ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(b10+a10*y_10,'f',1)));
        ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(11, 2) != 0)
    {
        ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(b11+a11*y_11,'f',1)));
        ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

   // Расчет значений цветов

    int color = 235 - (y_0 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color));

    int color2 = 235 - (y_1 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_4->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color2));

    int color_2 = 225 - (y_2 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 225.0;
    ui->label_5->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_2));

    int color4 = 235 - (y_3 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_6->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color4));

    int color5 = 235 - (y_4 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_7->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color5));

    int color6 = 235 - (y_5 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_8->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color6));

    int color7 = 235 - (y_6 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_9->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color7));

    int color8 = 235 - (y_7 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_10->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color8));

    int color9 = 235 - (y_8 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_11->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color9));

    int color10 = 235 - (y_9 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_12->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color10));

    int color11 = 235 - (y_10 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_13->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color11));

    int color12 = 235 - (y_11 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_14->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color12));

    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1548\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_2));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1598\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color8));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1544\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color6));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1594\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color9));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#rect1539\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color10));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1588\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color10));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1558\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color4));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1560\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color4));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1562\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color4));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1564\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color4));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1566\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color4));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1628\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color12));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1620\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color12));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1622\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color12));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1624\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color12));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1626\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color12));










    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6\").text('%1 C');").arg(y_2, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-1\").text('%1 C');").arg(y_7, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-5\").text('%1 C');").arg(y_6, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-5-9\").text('%1 C');").arg(y_8, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2\").text('%1 C');").arg(y_9, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-8-3\").text('%1 C');").arg(y_9, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-3\").text('%1 C');").arg(y_9, 0, 'f', 1));
    mw->ui->widget_7->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-3-9\").text('%1 C');").arg(y_11, 0, 'f', 1));






//    double y0=20*(1-exp(-t/200))+ui->lineEdit->text().toDouble();//станина
//    double y1=54*(1-exp(-t/200))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа сзади
//    double y2=110*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Лобовая часть слева спереди
//    double y3=56*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева спереди
//    double y4=115*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Лобовая часть слева спереди
//    double y5=112*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Лобовая часть слева сзади
//    double y6=90*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//станина
//    double y7=99*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Лобовая часть справа спереди
//    double y8=111*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Лобовая часть справа сзади
//    double y9=90*(1-exp(-t/250))+ui->lineEdit->text().toDouble();//Магнитопровод статора
//    double y10=60*(1-exp(-t/200))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа спереди
//    double y11=56*(1-exp(-t/200))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева сзади

//    int color = 235 - (y0 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color2 = 235 - (y1 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color3 = 235 - (y2 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color4 = 235 - (y3 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color5 = 235 - (y4 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color6 = 235 - (y5 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color7 = 235 - (y6 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color8 = 235 - (y7 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color9 = 235 - (y8 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color10 = 235 - (y9 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color11 = 235 - (y10 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;
//    int color12 = 235 - (y11 - ui->lineEdit->text().toDouble()) / 140.0 * 220.0;


//Проверка условия окончания расчета

    if (y_2 > maxY2)
           {
               maxY2 = y_2;
           }

           if (y_2 < minY2)
           {
               minY2 = y_2;
           }

           count++;

   if (count == 3)
   {

       if ((maxY2 - minY2)/maxY2 < 0.005)
       {
            timer.stop();

            if(y_0>y_1)
            {
                max=y_1;
            }
            else max=y_0;

            if(max<y_2)
            {
                max=y_2;
            }
            if(max<y_3)
            {
                max=y_3;
            }
            if(max<y_4)
            {
                max=y_4;
            }
            if(max<y_5)
            {
                max=y_5;
            }
            if(max<y_6)
            {
               max=y_6;
            }
            if(max<y_7)
            {
                max=y_7;
            }
            if(max<y_8)
            {
                max=y_8;
            }
            if(max<y_9)
            {
                max=y_9;
            }
            if(max<y_10)
            {
                max=y_10;
            }
            if(max<y_11)
            {
                max=y_11;
            }

            double miny=ui->lineEdit->text().toDouble();
            double h=(max-miny)/9;
            double shag1=miny+h;
            double shag2=shag1+h;
            double shag3=shag2+h;
            double shag4=shag3+h;
            double shag5=shag4+h;
            double shag6=shag5+h;
            double shag7=shag6+h;
            double shag8=shag7+h;
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan901\").text('%1');").arg(max, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan865\").text('%1');").arg(miny, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan869\").text('%1');").arg(shag1, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan873\").text('%1');").arg(shag2, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan877\").text('%1');").arg(shag3, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan881\").text('%1');").arg(shag4, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan885\").text('%1');").arg(shag5, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan889\").text('%1');").arg(shag6, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan893\").text('%1');").arg(shag7, 0, 'f', 1));
            mw->ui->widget_7->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan897\").text('%1');").arg(shag8, 0, 'f', 1));
            QMessageBox::information(this, tr("Сообщение"), tr("Расчет окончен!"));
       }

       maxY2 = 0;
       minY2 = 200;

       count = 0;
   }
}
