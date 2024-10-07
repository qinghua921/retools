#include "retools.hpp"
#include "iostream"
#include "peinfo.hpp"

ReTools::ReTools(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_retools)
{
    ui->setupUi(this);

    this->connect(ui->menubar, &QMenuBar::triggered, this, &ReTools::caidan_dianji);
}

ReTools::~ReTools()
{
    delete ui;
}

void ReTools::caidan_dianji(QAction *action)
{
    if (action == ui->action_pe_info)
    {
        auto peinfo = new PeInfo(this);
        ui->verticalLayout->addWidget(peinfo);
    }
}
