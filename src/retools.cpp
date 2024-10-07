#include "retools.h"
#include "iostream"
#include "peinfo.h"

retools::retools(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_retools)
{
    ui->setupUi(this);

    this->connect(ui->menubar, &QMenuBar::triggered, this, &retools::caidan_dianji);
}

retools::~retools()
{
    delete ui;
}

void retools::caidan_dianji(QAction *action)
{
    if (action == ui->action_pe_info)
    {
        auto peinfo1 = new peinfo(this);
        ui->centralwidget->layout()->addWidget(peinfo1);
    }
}
