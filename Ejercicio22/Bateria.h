#ifndef BATERIA_H
#define BATERIA_H

#include "instrumentos.h"

class Bateria : public Instrumento {
public:
    Bateria(int tambores = 5) : tambores_(tambores) {}

    void sonar() const override {
        std::cout << "Batería suena..." << std::endl;
    }

    int getTambores() const { return tambores_; }
    void setTambores(int tambores) { tambores_ = tambores; }

private:
    int tambores_;
};

#endif // BATERIA_H
