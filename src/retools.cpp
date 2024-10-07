#include "retools.h"
#include "iostream"

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
        std::cout << "pe_info" << std::endl;
    }
}
