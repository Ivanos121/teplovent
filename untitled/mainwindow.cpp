#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_6->mw = this;
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

