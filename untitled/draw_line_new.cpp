#include "draw_line_new.h"
#include "ui_draw_line_new.h"

#include <QFileInfo>
#include <QIcon>

draw_line_new::draw_line_new(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_line_new)
{
    ui->setupUi(this);  
    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var.html").absoluteFilePath()));
    //connect(view, &QWebEngineView::loadFinished, this, &draw_line_new::loadFinished );
}

draw_line_new::~draw_line_new()
{
    delete ui;
}
