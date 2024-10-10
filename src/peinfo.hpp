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
    PIMAGE_DOS_HEADER dos_header                = nullptr;
    PIMAGE_NT_HEADERS nt_headers                = nullptr;
    PIMAGE_FILE_HEADER file_header              = nullptr;
    PIMAGE_OPTIONAL_HEADER64 optional_header_64 = nullptr;
    PIMAGE_OPTIONAL_HEADER32 optional_header_32 = nullptr;

    PeInfo(QWidget *parent = nullptr);
    boolean jiexi_pe();
    void huizhi_pe();
    void zuoshu_dianji(QTreeWidgetItem *item, int column);
};
