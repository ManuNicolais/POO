#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    w.show();
    return a.exec();
}


/* USUARIOS
    1|cgomez|1234|Carlos|Gomez|cgomez@gmail.com
    2|mgomez|4679|Marti|Gomez|mgomez@gmail.com
    3|dabril|2345|David|Abril|dabril@gmail.com
    4|fmanuel|1111|Manuel|Nicolais|fnicolais@gmail.com
*/
