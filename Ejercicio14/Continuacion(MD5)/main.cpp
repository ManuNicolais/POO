#include <QApplication>

#include "admin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Admin::getInstance()->iniciar();
    return a.exec();
}

//usuario admin
//clave 1234

//usuario manu
//clave 1111
