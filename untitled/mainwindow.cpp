#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>

#include "ui_draw_poper_new.h"
#include "ui_draw_line_new.h"
#include "ui_vent_var.h"
#include "ui_vent_tract.h"
#include "ui_draw_vent_tract.h"
#include "ui_vent_tract.h"
#include "ui_vent_izm.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_6->mw = this;

    ui->widget_8->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_7->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_4->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_9->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_tract/vent_tract.html").absoluteFilePath()));

    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_anExit_triggered()
{
    close();
}


void MainWindow::on_anAbout_triggered()
{
//    QScreen *screen = QGuiApplication::primaryScreen();
//        rsc= new AboutDialog(this);
//        rsc->exec();
//        rsc->setGeometry(
//            QStyle::alignedRect(
//            Qt::LeftToRight,
//            Qt::AlignCenter,
//            rsc->size(),
//            screen->geometry()));
}

