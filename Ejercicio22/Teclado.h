#ifndef TECLADO_H
#define TECLADO_H

#include "instrumentos.h"
#include "electrico.h"

class Teclado : public Instrumento, public Electrico {
public:
    Teclado(int teclas = 61) : teclas_(teclas) {}

    void sonar() const override {
        std::cout << "Teclado suena..." << std::endl;
    }

    int getTeclas() const { return teclas_; }
    void setTeclas(int teclas) { teclas_ = teclas; }

private:
    int teclas_;
};

#endif // TECLADO_H
