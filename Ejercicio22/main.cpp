#include <QCoreApplication>

#include <vector>
#include <memory>
#include "guitarra.h"
#include "bateria.h"
#include "teclado.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Crear los instrumentos
    std::vector<std::shared_ptr<Instrumento>> instrumentos;
    instrumentos.push_back(std::make_shared<Guitarra>());
    instrumentos.push_back(std::make_shared<Bateria>());
    instrumentos.push_back(std::make_shared<Teclado>());
    instrumentos.push_back(std::make_shared<Guitarra>(12));  // Guitarra con 12 cuerdas
    instrumentos.push_back(std::make_shared<Bateria>(7));   // Batería con 7 tambores

    // Publicar la marca de cada instrumento
    for (const auto& instrumento : instrumentos) {
        instrumento->verlo();
    }

    // Hacer sonar cada instrumento
    for (const auto& instrumento : instrumentos) {
        instrumento->sonar();
    }


    return a.exec();
}
