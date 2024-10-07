#pragma once

#include <QWidget>

namespace Ui
{
class Demo;
}

class Demo : public QWidget
{
    Q_OBJECT

  public:
    explicit Demo(QWidget *parent = nullptr);
    ~Demo();

  private:
    Ui::Demo *ui;
};

