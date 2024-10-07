#pragma once

#include <QWidget>

namespace Ui
{
class PeInfo;
}

class PeInfo : public QWidget
{
    Q_OBJECT

  public:
    ~PeInfo();
    static PeInfo *caidan_dianji();

  private:
    PeInfo(QWidget *parent = nullptr);
    Ui::PeInfo *ui;
};
