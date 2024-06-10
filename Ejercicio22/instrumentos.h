#ifndef INSTRUMENTOS_H
#define INSTRUMENTOS_H

#include <QString>
#include <iostream>

class Instrumento {
public:
    Instrumento(const QString& marca = "Yamaha") : marca_(marca) {}  //marca por defecto de los instrumentos
    virtual ~Instrumento() = default;

    virtual void sonar() const = 0; //funcion virtual sonar
    virtual void verlo() const { //mermite ver la marca del instrumento
        std::cout << "Marca: " << marca_.toStdString() << std::endl;
    }

    void setMarca(const QString& marca) { marca_ = marca; }
    QString getMarca() const { return marca_; }

private:
    QString marca_;
};

#endif // INSTRUMENTOS_H
