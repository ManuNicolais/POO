#include "login.h"
#include "vnt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    vnt v;

    w.show();
    return a.exec();
}
