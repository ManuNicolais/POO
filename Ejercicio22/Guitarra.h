#ifndef GUITARRA_H
#define GUITARRA_H

#include "instrumentos.h"

class Guitarra : public Instrumento {
public:
    Guitarra(int cuerdas = 6) : cuerdas_(cuerdas) {}

    void sonar() const override {
        std::cout << "Guitarra suena..." << std::endl;
    }

    int getCuerdas() const { return cuerdas_; }
    void setCuerdas(int cuerdas) { cuerdas_ = cuerdas; }

private:
    int cuerdas_;
};

#endif // GUITARRA_H
