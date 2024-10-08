#include "peinfo.hpp"
#include "ui_peinfo.h"
#include <QFileDialog>

PeInfo::PeInfo(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::PeInfo)
{
    ui->setupUi(this);
}

boolean PeInfo::jiexi_pe()
{
    // 解析PE文件
    this->dos_header = (PIMAGE_DOS_HEADER)(this->wenjian_neicun.data());
    if (this->dos_header->e_magic != IMAGE_DOS_SIGNATURE) return false;

    this->nt_headers = (PIMAGE_NT_HEADERS)((char *)this->dos_header + this->dos_header->e_lfanew);
    if (this->nt_headers->Signature != IMAGE_NT_SIGNATURE) return false;

    return true;
}

void PeInfo::huizhi_pe()
{
    // 绘制 Dos Header 表格
    auto biaoge      = ui->dos_header_biaoge;
    auto row         = -1;

    auto huizhi_hang = [&biaoge, &row](const char *name, LONG offset)
    {
        row++;
        biaoge->setRowCount(row + 1);
        biaoge->setItem(row, 0, new QTableWidgetItem(name));
        biaoge->setItem(row, 1, new QTableWidgetItem(QString::number(offset, 16)));
    };

    huizhi_hang("e_magic", this->dos_header->e_magic);
    huizhi_hang("e_cblp", this->dos_header->e_cblp);
    huizhi_hang("e_cp", this->dos_header->e_cp);
    huizhi_hang("e_crlc", this->dos_header->e_crlc);
    huizhi_hang("e_cparhdr", this->dos_header->e_cparhdr);
    huizhi_hang("e_minalloc", this->dos_header->e_minalloc);
    huizhi_hang("e_maxalloc", this->dos_header->e_maxalloc);
    huizhi_hang("e_ss", this->dos_header->e_ss);
    huizhi_hang("e_sp", this->dos_header->e_sp);
    huizhi_hang("e_csum", this->dos_header->e_csum);
    huizhi_hang("e_ip", this->dos_header->e_ip);
    huizhi_hang("e_cs", this->dos_header->e_cs);
    huizhi_hang("e_lfarlc", this->dos_header->e_lfarlc);
    huizhi_hang("e_ovno", this->dos_header->e_ovno);
    huizhi_hang("e_res", this->dos_header->e_res[0]);
    huizhi_hang("e_oemid", this->dos_header->e_oemid);
    huizhi_hang("e_oeminfo", this->dos_header->e_oeminfo);
    huizhi_hang("e_res2", this->dos_header->e_res2[0]);
    huizhi_hang("e_lfanew", this->dos_header->e_lfanew);
}

PeInfo::~PeInfo()
{
    delete ui;
    qDebug() << "PeInfo::~PeInfo()";
}

PeInfo *PeInfo::caidan_dianji()
{
    // 选取文件
    auto wenjian_mingcheng = QFileDialog::getOpenFileName(nullptr, "Select PE File", "", "All Files (*)");
    if (wenjian_mingcheng.isEmpty()) return nullptr;

    // 读取文件内容
    QFile file(wenjian_mingcheng);
    if (!file.open(QIODevice::ReadOnly)) return nullptr;
    QByteArray data = file.readAll();
    file.close();

    auto ret               = new PeInfo();
    ret->wenjian_mingcheng = wenjian_mingcheng;
    ret->wenjian_neicun    = data;
    if (!ret->jiexi_pe())
    {
        delete ret;
        return nullptr;
    }
    ret->huizhi_pe();

    return ret;
}
