#pragma once

#include "ui_retools.h"
#include <QMainWindow>

class ReTools : public QMainWindow
{
    Q_OBJECT

  public:
    ReTools(QWidget *parent = nullptr);
    ~ReTools();

  private:
    Ui_retools *ui;
    void caidan_dianji(QAction *action);
};