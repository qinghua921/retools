#include "retools.hpp"

#include <QApplication>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ReTools retools;
    retools.show();
    return app.exec();
}