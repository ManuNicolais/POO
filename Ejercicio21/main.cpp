#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;

    w.setModo(login::Sqlite /*| login::Temp | login::ImagenFondo */); //si se comenta funciona admin 1234

    w.show();
    return a.exec();
}
