#ifndef ELECTRICO_H
#define ELECTRICO_H

class Electrico {
public:
    Electrico(int voltaje = 220) : voltaje_(voltaje) {}
    virtual ~Electrico() {
        std::cout << "Desenchufado" << std::endl;
    }

    int getVoltaje() const { return voltaje_; }
    void setVoltaje(int voltaje) { voltaje_ = voltaje; }

private:
    int voltaje_;
};


#endif // ELECTRICO_H
