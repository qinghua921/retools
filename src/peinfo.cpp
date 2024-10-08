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

    return ret;
}
