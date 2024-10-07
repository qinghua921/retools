#include "retools.h"

retools::retools(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_retools)
{
    ui->setupUi(this);
}

retools::~retools()
{
    delete ui;
}