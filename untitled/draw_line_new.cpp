#include "draw_line_new.h"
#include "ui_draw_line_new.h"

#include <QFileInfo>
#include <QIcon>

double y_0,y_1,y_2,y_3,y_4,y_5,y_6,y_7,y_8,y_9,y_10,y_11;

draw_line_new::draw_line_new(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_line_new)
{
    ui->setupUi(this);  
    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var.html").absoluteFilePath()));
    ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line.html").absoluteFilePath()));

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

    ui->tableWidget->setItem(0,  1, new QTableWidgetItem("Станина"));
    ui->tableWidget->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади"));
    ui->tableWidget->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
    ui->tableWidget->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди"));
    ui->tableWidget->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
    ui->tableWidget->setItem(5,  1, new QTableWidgetItem("Лобовая часть слева сзади"));
    ui->tableWidget->setItem(6,  1, new QTableWidgetItem("Станина"));
    ui->tableWidget->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа спереди"));
    ui->tableWidget->setItem(8,  1, new QTableWidgetItem("Лобовая часть справа сзади"));
    ui->tableWidget->setItem(9,  1, new QTableWidgetItem("Магнитопровод статора"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел справа спереди"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Подшипниковый узел слева сзади"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

    if (ui->tableWidget->item(0, 2) != 0)
    {
        ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(y_0,'f',3)));
        ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(1, 2) != 0)
    {
        ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(y_1,'f',3)));
        ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(2, 2) != 0)
    {
        ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(y_2,'f',3)));
        ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(3, 2) != 0)
    {
        ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(y_3,'f',3)));
        ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(4, 2) != 0)
    {
        ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(y_4,'f',3)));
        ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(5, 2) != 0)
    {
        ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(y_5,'f',3)));
        ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(6, 2) != 0)
    {
        ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(y_6,'f',3)));
        ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(7, 2) != 0)
    {
        ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(y_7,'f',3)));
        ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(8, 2) != 0)
    {
        ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(y_8,'f',3)));
        ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(9, 2) != 0)
    {
        ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(y_9,'f',3)));
        ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(10, 2) != 0)
    {
        ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(y_10,'f',3)));
        ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(11, 2) != 0)
    {
        ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(y_11,'f',3)));
        ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }
}

draw_line_new::~draw_line_new()
{
    delete ui;
}
