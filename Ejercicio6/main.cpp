#include <QCoreApplication>

#include <iostream>
#include <string>
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

    string getEspecie() {
        return especie;
    }

    void setDieta(int dieta) {
        this->dieta = dieta;
    }

    int getDieta(int dieta) {
        return dieta;
    }

    void imprimirTipoDieta() {
        if (dieta == 1)
            cout << "Carnivoro" << endl;
        else if (dieta == 2)
            cout << "Herbivoro" << endl;
        else if (dieta == 3)
            cout << "Omnivoro" << endl;
        else
            cout << "Tipo de dieta no reconocido" << endl;
    }

    void imprimirDetalles() {
        cout << "Animal: " << especie << endl;
        cout << "Dieta: " << dieta << endl;
        imprimirTipoDieta();
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Animales animal1; // Constructor por defecto
    Animales animal2("Gato", 3); // Constructor con parámetros

    cout << "Detalles del animal 1:" << endl;
    animal1.imprimirDetalles();
    cout << endl;

    // establecer atributos
    animal1.setEspecie("Leon");
    animal1.setDieta(1);

    // Imprimir detalles de las personas
    cout << "Detalles del animal 1:" << endl;
    animal1.imprimirDetalles();
    cout << endl;

    cout << "Detalles del animal 2:" << endl;
    animal2.imprimirDetalles();
    cout << endl;

    return a.exec();
}
