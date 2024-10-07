#include "peinfo.h"
#include "ui_peinfo.h"

peinfo::peinfo(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::peinfo)
{
    ui->setupUi(this);
}

peinfo::~peinfo()
{
    delete ui;
}
