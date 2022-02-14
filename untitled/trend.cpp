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

    ui->plot->t_max = 10;
    ui->plot->U_max = 20.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    ui->plot->addDataLine(QColor(255,0,0), 0);   //Станина
    ui->plot->addDataLine(QColor(255,255,0), 0); //Подшипниковый узел справа сзади
    ui->plot->addDataLine(QColor(0,255,0), 0);   //Лобовая часть слева спереди
    ui->plot->addDataLine(QColor(0,0,255), 0);   //Подшипниковый узел слева спереди
    ui->plot->addDataLine(QColor(255,102,0), 0); //Лобовая часть слева сзади
    ui->plot->addDataLine(QColor(255,0,255), 0); //Станина
    ui->plot->addDataLine(QColor(255,55,55), 0); //Лобовая часть справа спереди
    ui->plot->addDataLine(QColor(55,10,220), 0); //Лобовая часть справа сзади
    ui->plot->addDataLine(QColor(25,155,0), 0); //Магнитопровод статора
    ui->plot->addDataLine(QColor(255,0,0), 0); //Подшипниковый узел справа спереди
    ui->plot->addDataLine(QColor(255,0,0), 0); //Подшипниковый узел слева сзади

    connect(&timer, &QTimer::timeout, this, &trend::on_timer_timeout);
    //timer.start(0);



    ui->label->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));

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


    ui->tableWidget->setItem(0,  0, new QTableWidgetItem("Станина"));
    ui->tableWidget->setItem(1,  0, new QTableWidgetItem("Подшипниковый узел справа сзади"));
    ui->tableWidget->setItem(2,  0, new QTableWidgetItem("Лобовая часть слева спереди"));
    ui->tableWidget->setItem(3,  0, new QTableWidgetItem("Подшипниковый узел слева спереди"));
    ui->tableWidget->setItem(4,  0, new QTableWidgetItem("Лобовая часть слева спереди"));
    ui->tableWidget->setItem(5,  0, new QTableWidgetItem("Лобовая часть слева сзади"));
    ui->tableWidget->setItem(6,  0, new QTableWidgetItem("Станина"));
    ui->tableWidget->setItem(7,  0, new QTableWidgetItem("Лобовая часть справа спереди"));
    ui->tableWidget->setItem(8,  0, new QTableWidgetItem("Лобовая часть справа сзади"));
    ui->tableWidget->setItem(9,  0, new QTableWidgetItem("Магнитопровод статора"));
    ui->tableWidget->setItem(10, 0, new QTableWidgetItem("Подшипниковый узел справа спереди"));
    ui->tableWidget->setItem(11, 0, new QTableWidgetItem("Подшипниковый узел слева сзади"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

    ui->tableWidget_2->setRowCount(11); //задание количества строк таблицы
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

    for (int i=0; i<11; i++)
    {
        if (ui->tableWidget_2->item(i, 3) != 0)
        {
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


    QTableWidgetItem *item51 = new QTableWidgetItem("Item51");
    item51->setCheckState(Qt::Checked);
    item51->setText("Станина:");
    ui->tableWidget_2->setItem(0, 2, item51);

    QTableWidgetItem *item52 = new QTableWidgetItem("Item52");
    item52->setCheckState(Qt::Checked);
    item52->setText("Подшипниковый узел справа сзади:");
    ui->tableWidget_2->setItem(1, 2, item52);

    QTableWidgetItem *item53 = new QTableWidgetItem("Item53");
    item53->setCheckState(Qt::Checked);
    item53->setText("Лобовая часть слева спереди:");
    ui->tableWidget_2->setItem(2, 2, item53);

    QTableWidgetItem *item54 = new QTableWidgetItem("Item54");
    item54->setCheckState(Qt::Checked);
    item54->setText("Подшипниковый узел слева спереди:");
    ui->tableWidget_2->setItem(3, 2, item54);

    QTableWidgetItem *item55 = new QTableWidgetItem("Item55");
    item55->setCheckState(Qt::Checked);
    item55->setText("Лобовая часть слева спереди:");
    ui->tableWidget_2->setItem(4, 2, item55);

    QTableWidgetItem *item56 = new QTableWidgetItem("Item56");
    item56->setCheckState(Qt::Checked);
    item56->setText("Лобовая часть слева сзади:");
    ui->tableWidget_2->setItem(5, 2, item56);

    QTableWidgetItem *item57 = new QTableWidgetItem("Item57");
    item57->setCheckState(Qt::Checked);
    item57->setText("Станина:");
    ui->tableWidget_2->setItem(6, 2, item57);

    QTableWidgetItem *item58 = new QTableWidgetItem("Item58");
    item58->setCheckState(Qt::Checked);
    item58->setText("Лобовая часть справа спереди:");
    ui->tableWidget_2->setItem(7, 2, item58);

    QTableWidgetItem *item59 = new QTableWidgetItem("Item59");
    item59->setCheckState(Qt::Checked);
    item59->setText("Лобовая часть справа сзади:");
    ui->tableWidget_2->setItem(8, 2, item59);

    QTableWidgetItem *item60 = new QTableWidgetItem("Item60");
    item60->setCheckState(Qt::Checked);
    item60->setText("Магнитопровод статора:");
    ui->tableWidget_2->setItem(9, 2, item60);

    QTableWidgetItem *item61 = new QTableWidgetItem("Item61");
    item61->setCheckState(Qt::Checked);
    item61->setText("Подшипниковый узел справа спереди:");
    ui->tableWidget_2->setItem(10, 2, item61);

    QTableWidgetItem *item62 = new QTableWidgetItem("Item62");
    item62->setCheckState(Qt::Checked);
    item62->setText("Подшипниковый узел слева сзади:");
    ui->tableWidget_2->setItem(11, 2, item62);

    ui->tableWidget_2->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(0, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(1, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(2, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(3, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(4, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(5, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(6, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(7, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(8, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(9, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(9, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(10, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(10, 5, new QTableWidgetItem(QString("%1").arg(0)));

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);

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
    //qDebug() << position_2;

    root = doc3.firstChildElement();

    elemText = root.elementsByTagName("text");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.firstChild().nodeValue();
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

    timer.start(100);

    t += 1.0;
}


void trend::on_pushButton_2_clicked()
{
    timer.stop();
}

void trend::on_timer_timeout()
{
    double a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11;
    double b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11;
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

    a1=ui->tableWidget_2->item(0,4)->text().toDouble();
    a2=ui->tableWidget_2->item(1,4)->text().toDouble();
    a3=ui->tableWidget_2->item(2,4)->text().toDouble();
    a4=ui->tableWidget_2->item(3,4)->text().toDouble();
    a5=ui->tableWidget_2->item(4,4)->text().toDouble();
    a6=ui->tableWidget_2->item(5,4)->text().toDouble();
    a7=ui->tableWidget_2->item(6,4)->text().toDouble();
    a8=ui->tableWidget_2->item(7,4)->text().toDouble();
    a9=ui->tableWidget_2->item(8,4)->text().toDouble();
    a10=ui->tableWidget_2->item(9,4)->text().toDouble();
    a11=ui->tableWidget_2->item(10,4)->text().toDouble();

    b1=ui->tableWidget_2->item(0,5)->text().toDouble();
    b2=ui->tableWidget_2->item(1,5)->text().toDouble();
    b3=ui->tableWidget_2->item(2,5)->text().toDouble();
    b4=ui->tableWidget_2->item(3,5)->text().toDouble();
    b5=ui->tableWidget_2->item(4,5)->text().toDouble();
    b6=ui->tableWidget_2->item(5,5)->text().toDouble();
    b7=ui->tableWidget_2->item(6,5)->text().toDouble();
    b8=ui->tableWidget_2->item(7,5)->text().toDouble();
    b9=ui->tableWidget_2->item(8,5)->text().toDouble();
    b10=ui->tableWidget_2->item(9,5)->text().toDouble();
    b11=ui->tableWidget_2->item(10,5)->text().toDouble();

    if(ui->tableWidget_2->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(0, t, b1+a1*y1);
    }

    if(ui->tableWidget_2->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(1, t, b2+a2*y2);
    }

    if(ui->tableWidget_2->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(2, t, b3+a3*y3);
    }

    if(ui->tableWidget_2->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(3, t, b4+a4*y4);
    }

    if(ui->tableWidget_2->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(4, t, b5+a5*y5);
    }

    if(ui->tableWidget_2->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(5, t, b6+a6*y6);
    }

    if(ui->tableWidget_2->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(6, t, b7+a7*y7);
    }

    if(ui->tableWidget_2->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(7, t, b8+a8*y8);
    }

    if(ui->tableWidget_2->model()->index(8,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(8, t, b9+a9*y9);
    }

    if(ui->tableWidget_2->model()->index(9,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(9, t, b10+a10*y10);
    }

    if(ui->tableWidget_2->model()->index(10,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(10, t, b11+a11*y11);
    }

//    ui->plot->addPoint(0, t, y1);
//    ui->plot->addPoint(1, t, y2);
//    ui->plot->addPoint(2, t, y3);
//    ui->plot->addPoint(3, t, y4);
//    ui->plot->addPoint(4, t, y5);
//    ui->plot->addPoint(5, t, y6);
//    ui->plot->addPoint(6, t, y7);
//    ui->plot->addPoint(7, t, y8);
//    ui->plot->addPoint(8, t, y9);
//    ui->plot->addPoint(9, t, y10);
//    ui->plot->addPoint(10, t, y11);

    t += 1.0;


    if (ui->tableWidget->item(0, 2) != 0)
    {
        ui->tableWidget->item(0, 2)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(0, 3) != 0)
    {
        ui->tableWidget_2->item(0, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(1, 3) != 0)
    {
        ui->tableWidget_2->item(1, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(2, 3) != 0)
    {
        ui->tableWidget_2->item(2, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(3, 3) != 0)
    {
        ui->tableWidget_2->item(3, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(3, 3) != 0)
    {
        ui->tableWidget_2->item(3, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(4, 3) != 0)
    {
        ui->tableWidget_2->item(4, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(5, 3) != 0)
    {
        ui->tableWidget_2->item(5, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(6, 3) != 0)
    {
        ui->tableWidget_2->item(6, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(7, 3) != 0)
    {
        ui->tableWidget_2->item(7, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(8, 3) != 0)
    {
        ui->tableWidget_2->item(8, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(9, 3) != 0)
    {
        ui->tableWidget_2->item(9, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    if (ui->tableWidget_2->item(10, 3) != 0)
    {
        ui->tableWidget_2->item(10, 3)->setText(QString("%1").arg(b1+a1*y1));
    }

    int color = 235 - (y2 - ui->lineEdit->text().toDouble()) / 120.0 * 220.0;
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

    elemText = root.elementsByTagName("text");
    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            qDebug() << e.firstChild().nodeValue();
            e.firstChild().setNodeValue(QString("%1").arg(y1));
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
