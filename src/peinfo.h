#pragma once

#include <QWidget>

namespace Ui
{
class peinfo;
}

class peinfo : public QWidget
{
    Q_OBJECT

  public:
    explicit peinfo(QWidget *parent = nullptr);
    ~peinfo();

  private:
    Ui::peinfo *ui;
};
