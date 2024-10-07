#pragma once
#include "ui_retools.h"
#include <QMainWindow>

class retools : public QMainWindow
{
    Q_OBJECT

  public:
    retools(QWidget *parent = nullptr);
    ~retools();

  private:
    Ui_retools *ui;
    void caidan_dianji(QAction *action);
};