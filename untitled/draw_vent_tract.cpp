#include "draw_vent_tract.h"
#include "ui_draw_vent_tract.h"
#include "plot.h"
#include <QColor>
#include <QColorDialog>

draw_vent_tract::draw_vent_tract(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_vent_tract),
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

    //Настройки таблицы результатов расчетов

    ui->tableWidget->setRowCount(17);
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

    for (int i=0; i<17; i++)
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
    ui->tableWidget->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tableWidget->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tableWidget->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

    //настройки таблицы параметров графиков
    ui->tableWidget_2->setRowCount(17); //задание количества строк таблицы
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

    for (int i=0; i<17; i++)
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
    item55->setText("Лобовая часть слева сзади, °C:");
    ui->tableWidget_2->setItem(4, 2, item55);

    QTableWidgetItem *item56 = new QTableWidgetItem("Item56");
    item56->setCheckState(Qt::Checked);
    item56->setText("Станина, °C:");
    ui->tableWidget_2->setItem(5, 2, item56);

    QTableWidgetItem *item57 = new QTableWidgetItem("Item57");
    item57->setCheckState(Qt::Checked);
    item57->setText("Лобовая часть справа спереди, °C:");
    ui->tableWidget_2->setItem(6, 2, item57);

    QTableWidgetItem *item58 = new QTableWidgetItem("Item58");
    item58->setCheckState(Qt::Checked);
    item58->setText("Лобовая часть справа сзади, °C:");
    ui->tableWidget_2->setItem(7, 2, item58);

    QTableWidgetItem *item59 = new QTableWidgetItem("Item59");
    item59->setCheckState(Qt::Checked);
    item59->setText("Магнитопровод статора, °C:");
    ui->tableWidget_2->setItem(8, 2, item59);

    QTableWidgetItem *item60 = new QTableWidgetItem("Item60");
    item60->setCheckState(Qt::Checked);
    item60->setText("Подшипниковый узел справа спереди, °C:");
    ui->tableWidget_2->setItem(9, 2, item60);

    QTableWidgetItem *item61 = new QTableWidgetItem("Item61");
    item61->setCheckState(Qt::Checked);
    item61->setText("Подшипниковый узел слева сзади, °C:");
    ui->tableWidget_2->setItem(10, 2, item61);

    QTableWidgetItem *item62 = new QTableWidgetItem("Item62");
    item62->setCheckState(Qt::Checked);
    item62->setText("Ротор сверху, °C:");
    ui->tableWidget_2->setItem(11, 2, item62);

    QTableWidgetItem *item63 = new QTableWidgetItem("Item63");
    item63->setCheckState(Qt::Checked);
    item63->setText("Ротор снизу, °C:");
    ui->tableWidget_2->setItem(12, 2, item63);

    QTableWidgetItem *item64 = new QTableWidgetItem("Item64");
    item64->setCheckState(Qt::Checked);
    item64->setText("Станина слева, °C:");
    ui->tableWidget_2->setItem(13, 2, item64);

    QTableWidgetItem *item65 = new QTableWidgetItem("Item65");
    item65->setCheckState(Qt::Checked);
    item65->setText("Станина справа, °C:");
    ui->tableWidget_2->setItem(14, 2, item65);

    QTableWidgetItem *item66 = new QTableWidgetItem("Item66");
    item66->setCheckState(Qt::Checked);
    item66->setText("Станина справа, °C:");
    ui->tableWidget_2->setItem(15, 2, item66);

    QTableWidgetItem *item67 = new QTableWidgetItem("Item67");
    item67->setCheckState(Qt::Checked);
    item67->setText("Клеммная коробка, °C:");
    ui->tableWidget_2->setItem(16, 2, item67);

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
    ui->tableWidget_2->setItem(12, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(12,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(12, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(12,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(13, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(13,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(13, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(13,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(14, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(14,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(14, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(14,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(15, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(15,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(15, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(15,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(16, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(16,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(16, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(16,5)->setTextAlignment(Qt::AlignCenter);

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
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
    }

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget_2->item(i, 1)->setBackground(dataLineColors[i]);
    }
    connect(ui->tableWidget_2, &QTableWidget::cellClicked,this, &draw_vent_tract::setcolorincell);
}

draw_vent_tract::~draw_vent_tract()
{
    delete ui;
}

void draw_vent_tract::setcolorincell(int row, int column)
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
