#include "bittools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BitTools w;
    w.show();
    return a.exec();
}
