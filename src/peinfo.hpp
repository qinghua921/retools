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
    explicit PeInfo(QWidget *parent = nullptr);
    ~PeInfo();

  private:
    Ui::PeInfo *ui;
};
