#pragma once

#include <QTreeWidgetItem>
#include <QWidget>
#include <Windows.h>

namespace Ui
{
class PeInfo;
}

class PeInfo : public QWidget
{
    Q_OBJECT

  public:
    ~PeInfo();
    static PeInfo *caidan_dianji(QWidget *parent);

  private:
    Ui::PeInfo *ui;
    QString wenjian_mingcheng;
    QByteArray wenjian_neicun;
    PIMAGE_DOS_HEADER dos_header;
    PIMAGE_NT_HEADERS nt_headers;

    PeInfo(QWidget *parent = nullptr);
    boolean jiexi_pe();
    void huizhi_pe();
    void zuoshu_dianji(QTreeWidgetItem *item, int column);
};
