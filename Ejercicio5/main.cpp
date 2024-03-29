#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <iostream>
#include <algorithm> // Para sort

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Palabrass
    vector<string> palabrasDisponibles = {"Pan", "Comida", "Auto", "Casa", "Perro", "Gato", "Arbol", "Computadora"};

    // contiene las palabras
    vector<string> palabrasIngresadas;

    // Ingresar palabras en el vector
    for (const string &palabra : palabrasDisponibles) {
        palabrasIngresadas.push_back(palabra);
    }

    // Ordenar el vector de palabras ingresadas en orden alfabético
    sort(palabrasIngresadas.begin(), palabrasIngresadas.end());

    // Imprimir el vector de palabras ordenadas alfabéticamente
    cout << "Palabras ingresadas (ordenadas alfabéticamente):" << endl;
    for (const string &palabra : palabrasIngresadas) {
        cout << palabra << " ";
    }
    cout << endl;

    return a.exec();
}
