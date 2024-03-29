#include <QCoreApplication>

#include <iostream>
#include <string>

#include <vector>
#include <algorithm>

using namespace std;

class Animales
{
private:
    string especie;
    int dieta; //1 carnivoro - 2 herbivoro - 3 omnivoro
public:
    Animales() {
        especie = "Perro";
        dieta = 3;
    }

    Animales(string especie, int dieta) {
        this->especie = especie;
        this->dieta = dieta;
    }

    void setEspecie(string especie){
        this->especie = especie;
    }

    string getEspecie() const{
        return especie;
    }

    void setDieta(int dieta) {
        this->dieta = dieta;
    }

    int getDieta(int dieta) const{
        return dieta;
    }

    string imprimirTipoDieta() const{
        if (dieta == 1)
            return "Carnivoro";
        else if (dieta == 2)
            return "Herbivoro";
        else if (dieta == 3)
            return "Omnivoro";
        else
            return "Tipo de dieta no reconocido";
    }


    void imprimirDetalles() const {
        cout << "Animal: " << especie << ", Dieta: " << imprimirTipoDieta() << endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<Animales> animales = {
        {"Perro", 3},
        {"Gato", 3},
        {"Leon", 1},
        {"Vaca", 2},
        {"Conejo", 2},
        {"Pato", 3}
    };

    cout << "Animales:" << endl;
    for (const Animales& animal : animales) {
        animal.imprimirDetalles();
    }



    return a.exec();
}
