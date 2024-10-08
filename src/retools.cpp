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
    QWidget *widget = nullptr;

    if (action == ui->pe_info_dianji) widget = PeInfo::caidan_dianji(this);

    if (widget)
    {
        for (int i = 0; i < ui->zhuwutai->count(); ++i)
        {
            auto item = ui->zhuwutai->itemAt(i);
            item->widget()->deleteLater();
        }
        ui->zhuwutai->addWidget(widget);
    }
}
