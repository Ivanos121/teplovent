#include "draw_vent_tract.h"
#include "ui_draw_vent_tract.h"

draw_vent_tract::draw_vent_tract(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_vent_tract)
{
    ui->setupUi(this);
}

draw_vent_tract::~draw_vent_tract()
{
    delete ui;
}
