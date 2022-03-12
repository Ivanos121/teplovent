#include "vent_tract.h"
#include "ui_vent_tract.h"

Vent_tract::Vent_tract(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vent_tract)
{
    ui->setupUi(this);
}

Vent_tract::~Vent_tract()
{
    delete ui;
}
