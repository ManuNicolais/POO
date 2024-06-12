#include "panser.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Panser w;
    w.show();
    return a.exec();
}
