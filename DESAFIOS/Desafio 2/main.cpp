#include "boton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Boton w;
    w.setTexto("holasaasasa");
    w.setColor(Boton::Azul);
    w.show();
    return a.exec();
}
