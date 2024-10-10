#include "peinfo.hpp"
#include "ui_peinfo.h"
#include <QFileDialog>
#include <QMessageBox>

PeInfo::PeInfo(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::PeInfo)
{
    ui->setupUi(this);
    ui->zuoshu->expandAll();

    connect(ui->zuoshu, &QTreeWidget::itemClicked, this, &PeInfo::zuoshu_dianji);
}

boolean PeInfo::jiexi_pe()
{
    this->dos_header = (PIMAGE_DOS_HEADER)(this->wenjian_neicun.data());
    if (this->dos_header->e_magic != IMAGE_DOS_SIGNATURE) return false;

    this->nt_headers = (PIMAGE_NT_HEADERS)((char *)this->dos_header + this->dos_header->e_lfanew);
    if (this->nt_headers->Signature != IMAGE_NT_SIGNATURE) return false;

    this->file_header = &this->nt_headers->FileHeader;

    if (this->file_header->Machine == IMAGE_FILE_MACHINE_I386)
        this->optional_header_32 = (PIMAGE_OPTIONAL_HEADER32) & this->nt_headers->OptionalHeader;
    else if (this->file_header->Machine == IMAGE_FILE_MACHINE_AMD64)
        this->optional_header_64 = (PIMAGE_OPTIONAL_HEADER64) & this->nt_headers->OptionalHeader;
    else return false;

    return true;
}

void PeInfo::huizhi_pe()
{

    // 绘制 Dos Header 表格
    auto row                    = 0;
    auto huizhi_hang_dos_header = [&](const char *name, LONG value)
    {
        this->ui->dos_header_biaoge->setRowCount(row + 1);
        this->ui->dos_header_biaoge->setItem(row, 0, new QTableWidgetItem(name));
        this->ui->dos_header_biaoge->setItem(row, 1, new QTableWidgetItem(QString::number(value, 16).toUpper()));
        row++;
    };

    huizhi_hang_dos_header("e_magic", this->dos_header->e_magic);
    huizhi_hang_dos_header("e_cblp", this->dos_header->e_cblp);
    huizhi_hang_dos_header("e_cp", this->dos_header->e_cp);
    huizhi_hang_dos_header("e_crlc", this->dos_header->e_crlc);
    huizhi_hang_dos_header("e_cparhdr", this->dos_header->e_cparhdr);
    huizhi_hang_dos_header("e_minalloc", this->dos_header->e_minalloc);
    huizhi_hang_dos_header("e_maxalloc", this->dos_header->e_maxalloc);
    huizhi_hang_dos_header("e_ss", this->dos_header->e_ss);
    huizhi_hang_dos_header("e_sp", this->dos_header->e_sp);
    huizhi_hang_dos_header("e_csum", this->dos_header->e_csum);
    huizhi_hang_dos_header("e_ip", this->dos_header->e_ip);
    huizhi_hang_dos_header("e_cs", this->dos_header->e_cs);
    huizhi_hang_dos_header("e_lfarlc", this->dos_header->e_lfarlc);
    huizhi_hang_dos_header("e_ovno", this->dos_header->e_ovno);

    ui->dos_header_biaoge->setRowCount(row + 1);
    ui->dos_header_biaoge->setItem(row, 0, new QTableWidgetItem("e_res"));
    ui->dos_header_biaoge->setItem(
        row,
        1,
        new QTableWidgetItem(
            QString("[%1,%2,%3,%4]")
                .arg(this->dos_header->e_res[0], 0, 16)
                .arg(this->dos_header->e_res[1], 0, 16)
                .arg(this->dos_header->e_res[2], 0, 16)
                .arg(this->dos_header->e_res[3], 0, 16)
                .toUpper()
        )
    );
    row++;

    huizhi_hang_dos_header("e_oemid", this->dos_header->e_oemid);
    huizhi_hang_dos_header("e_oeminfo", this->dos_header->e_oeminfo);

    ui->dos_header_biaoge->setRowCount(row + 1);
    ui->dos_header_biaoge->setItem(row, 0, new QTableWidgetItem("e_res2"));
    ui->dos_header_biaoge->setItem(
        row,
        1,
        new QTableWidgetItem(
            QString("[%1,%2,%3,%4,%5,%6,%7,%8,%9,%10]")
                .arg(this->dos_header->e_res2[0], 0, 16)
                .arg(this->dos_header->e_res2[1], 0, 16)
                .arg(this->dos_header->e_res2[2], 0, 16)
                .arg(this->dos_header->e_res2[3], 0, 16)
                .arg(this->dos_header->e_res2[4], 0, 16)
                .arg(this->dos_header->e_res2[5], 0, 16)
                .arg(this->dos_header->e_res2[6], 0, 16)
                .arg(this->dos_header->e_res2[7], 0, 16)
                .arg(this->dos_header->e_res2[8], 0, 16)
                .arg(this->dos_header->e_res2[9], 0, 16)
                .toUpper()
        )
    );
    row++;

    huizhi_hang_dos_header("e_lfanew", this->dos_header->e_lfanew);

    ui->dos_header_biaoge->resizeColumnsToContents();

    // 绘制 File Header 表格
    row                          = 0;
    auto huizhi_hang_file_header = [&](const char *name, LONG value)
    {
        this->ui->file_header_biaoge->setRowCount(row + 1);
        this->ui->file_header_biaoge->setItem(row, 0, new QTableWidgetItem(name));
        this->ui->file_header_biaoge->setItem(row, 1, new QTableWidgetItem(QString::number(value, 16).toUpper()));
        row++;
    };

    huizhi_hang_file_header("Machine", this->file_header->Machine);
    huizhi_hang_file_header("NumberOfSections", this->file_header->NumberOfSections);
    huizhi_hang_file_header("TimeDateStamp", this->file_header->TimeDateStamp);
    huizhi_hang_file_header("PointerToSymbolTable", this->file_header->PointerToSymbolTable);
    huizhi_hang_file_header("NumberOfSymbols", this->file_header->NumberOfSymbols);
    huizhi_hang_file_header("SizeOfOptionalHeader", this->file_header->SizeOfOptionalHeader);
    huizhi_hang_file_header("Characteristics", this->file_header->Characteristics);

    ui->file_header_biaoge->resizeColumnsToContents();

    // 绘制 Optional Header 表格
    if (this->optional_header_32)
    {
        row                              = 0;
        auto huizhi_hang_optional_header = [&](const char *name, LONG value)
        {
            this->ui->optional_header_biaoge->setRowCount(row + 1);
            this->ui->optional_header_biaoge->setItem(row, 0, new QTableWidgetItem(name));
            this->ui->optional_header_biaoge->setItem(row, 1, new QTableWidgetItem(QString::number(value, 16).toUpper()));
            row++;
        };

        huizhi_hang_optional_header("Magic", this->optional_header_32->Magic);
        huizhi_hang_optional_header("MajorLinkerVersion", this->optional_header_32->MajorLinkerVersion);
        huizhi_hang_optional_header("MinorLinkerVersion", this->optional_header_32->MinorLinkerVersion);
        huizhi_hang_optional_header("SizeOfCode", this->optional_header_32->SizeOfCode);
        huizhi_hang_optional_header("SizeOfInitializedData", this->optional_header_32->SizeOfInitializedData);
        huizhi_hang_optional_header("SizeOfUninitializedData", this->optional_header_32->SizeOfUninitializedData);
        huizhi_hang_optional_header("AddressOfEntryPoint", this->optional_header_32->AddressOfEntryPoint);
        huizhi_hang_optional_header("BaseOfCode", this->optional_header_32->BaseOfCode);
        huizhi_hang_optional_header("BaseOfData", this->optional_header_32->BaseOfData);
        huizhi_hang_optional_header("ImageBase", this->optional_header_32->ImageBase);
        huizhi_hang_optional_header("SectionAlignment", this->optional_header_32->SectionAlignment);
        huizhi_hang_optional_header("FileAlignment", this->optional_header_32->FileAlignment);
        huizhi_hang_optional_header("MajorOperatingSystemVersion", this->optional_header_32->MajorOperatingSystemVersion);
        huizhi_hang_optional_header("MinorOperatingSystemVersion", this->optional_header_32->MinorOperatingSystemVersion);
        huizhi_hang_optional_header("MajorImageVersion", this->optional_header_32->MajorImageVersion);
        huizhi_hang_optional_header("MinorImageVersion", this->optional_header_32->MinorImageVersion);
        huizhi_hang_optional_header("MajorSubsystemVersion", this->optional_header_32->MajorSubsystemVersion);
        huizhi_hang_optional_header("MinorSubsystemVersion", this->optional_header_32->MinorSubsystemVersion);
        huizhi_hang_optional_header("Win32VersionValue", this->optional_header_32->Win32VersionValue);
        huizhi_hang_optional_header("SizeOfImage", this->optional_header_32->SizeOfImage);
        huizhi_hang_optional_header("SizeOfHeaders", this->optional_header_32->SizeOfHeaders);
        huizhi_hang_optional_header("CheckSum", this->optional_header_32->CheckSum);
        huizhi_hang_optional_header("Subsystem", this->optional_header_32->Subsystem);
        huizhi_hang_optional_header("DllCharacteristics", this->optional_header_32->DllCharacteristics);
        huizhi_hang_optional_header("SizeOfStackReserve", this->optional_header_32->SizeOfStackReserve);
        huizhi_hang_optional_header("SizeOfStackCommit", this->optional_header_32->SizeOfStackCommit);
        huizhi_hang_optional_header("SizeOfHeapReserve", this->optional_header_32->SizeOfHeapReserve);
        huizhi_hang_optional_header("SizeOfHeapCommit", this->optional_header_32->SizeOfHeapCommit);
        huizhi_hang_optional_header("LoaderFlags", this->optional_header_32->LoaderFlags);
        huizhi_hang_optional_header("NumberOfRvaAndSizes", this->optional_header_32->NumberOfRvaAndSizes);

        ui->optional_header_biaoge->resizeColumnsToContents();
    }
    
    if (this->optional_header_64)
    {
        row                              = 0;
        auto huizhi_hang_optional_header = [&](const char *name, LONG value)
        {
            this->ui->optional_header_biaoge->setRowCount(row + 1);
            this->ui->optional_header_biaoge->setItem(row, 0, new QTableWidgetItem(name));
            this->ui->optional_header_biaoge->setItem(row, 1, new QTableWidgetItem(QString::number(value, 16).toUpper()));
            row++;
        };

        huizhi_hang_optional_header("Magic", this->optional_header_64->Magic);
        huizhi_hang_optional_header("MajorLinkerVersion", this->optional_header_64->MajorLinkerVersion);
        huizhi_hang_optional_header("MinorLinkerVersion", this->optional_header_64->MinorLinkerVersion);
        huizhi_hang_optional_header("SizeOfCode", this->optional_header_64->SizeOfCode);
        huizhi_hang_optional_header("SizeOfInitializedData", this->optional_header_64->SizeOfInitializedData);
        huizhi_hang_optional_header("SizeOfUninitializedData", this->optional_header_64->SizeOfUninitializedData);
        huizhi_hang_optional_header("AddressOfEntryPoint", this->optional_header_64->AddressOfEntryPoint);
        huizhi_hang_optional_header("BaseOfCode", this->optional_header_64->BaseOfCode);
        huizhi_hang_optional_header("ImageBase", this->optional_header_64->ImageBase);
        huizhi_hang_optional_header("SectionAlignment", this->optional_header_64->SectionAlignment);
        huizhi_hang_optional_header("FileAlignment", this->optional_header_64->FileAlignment);
        huizhi_hang_optional_header("MajorOperatingSystemVersion", this->optional_header_64->MajorOperatingSystemVersion);
        huizhi_hang_optional_header("MinorOperatingSystemVersion", this->optional_header_64->MinorOperatingSystemVersion);
        huizhi_hang_optional_header("MajorImageVersion", this->optional_header_64->MajorImageVersion);
        huizhi_hang_optional_header("MinorImageVersion", this->optional_header_64->MinorImageVersion);
        huizhi_hang_optional_header("MajorSubsystemVersion", this->optional_header_64->MajorSubsystemVersion);
        huizhi_hang_optional_header("MinorSubsystemVersion", this->optional_header_64->MinorSubsystemVersion);
        huizhi_hang_optional_header("Win32VersionValue", this->optional_header_64->Win32VersionValue);
        huizhi_hang_optional_header("SizeOfImage", this->optional_header_64->SizeOfImage);
        huizhi_hang_optional_header("SizeOfHeaders", this->optional_header_64->SizeOfHeaders);
        huizhi_hang_optional_header("CheckSum", this->optional_header_64->CheckSum);
        huizhi_hang_optional_header("Subsystem", this->optional_header_64->Subsystem);
        huizhi_hang_optional_header("DllCharacteristics", this->optional_header_64->DllCharacteristics);
        huizhi_hang_optional_header("SizeOfStackReserve", this->optional_header_64->SizeOfStackReserve);
        huizhi_hang_optional_header("SizeOfStackCommit", this->optional_header_64->SizeOfStackCommit);
        huizhi_hang_optional_header("SizeOfHeapReserve", this->optional_header_64->SizeOfHeapReserve);
        huizhi_hang_optional_header("SizeOfHeapCommit", this->optional_header_64->SizeOfHeapCommit);
        huizhi_hang_optional_header("LoaderFlags", this->optional_header_64->LoaderFlags);
        huizhi_hang_optional_header("NumberOfRvaAndSizes", this->optional_header_64->NumberOfRvaAndSizes);

        ui->optional_header_biaoge->resizeColumnsToContents();
    }
}

void PeInfo::zuoshu_dianji(QTreeWidgetItem *item, int column)
{
    auto text = item->text(column);
    qDebug() << "PeInfo::zuoshu_dianji()" << item->text(column) << column;

    if (text == "Dos Header") ui->yemian->setCurrentWidget(ui->dos_header_ye);
    else if (text == "Nt Header") {}
    else if (text == "File Header") ui->yemian->setCurrentWidget(ui->file_header_ye);
    else if (text == "Optional Header") ui->yemian->setCurrentWidget(ui->optional_header_ye);
    else QMessageBox::warning(this, "Error", "Unknown item");
}

PeInfo::~PeInfo()
{
    delete ui;
    qDebug() << "PeInfo::~PeInfo()";
}

PeInfo *PeInfo::caidan_dianji(QWidget *parent)
{
    // 选取文件
    auto wenjian_mingcheng = QFileDialog::getOpenFileName(nullptr, "Select PE File", "", "All Files (*)");
    if (wenjian_mingcheng.isEmpty()) return nullptr;

    // 读取文件内容
    QFile file(wenjian_mingcheng);
    if (!file.open(QIODevice::ReadOnly)) return nullptr;
    QByteArray data = file.readAll();
    file.close();

    auto ret               = new PeInfo(parent);
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
