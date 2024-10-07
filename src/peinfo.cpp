#include "peinfo.hpp"
#include "ui_peinfo.h"

PeInfo::PeInfo(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::PeInfo)
{
    ui->setupUi(this);
}

PeInfo::~PeInfo()
{
    delete ui;
    qDebug() << "PeInfo::~PeInfo()";
}

PeInfo *PeInfo::caidan_dianji()
{
    return new PeInfo();
}
