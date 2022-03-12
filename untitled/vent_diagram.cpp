#include "vent_diagram.h"
#include "ui_vent_diagram.h"

vent_diagram::vent_diagram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_diagram)
{
    ui->setupUi(this);
}

vent_diagram::~vent_diagram()
{
    delete ui;
}
