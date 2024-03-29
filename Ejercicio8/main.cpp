#include <QCoreApplication>

#include <iostream>
#include <string>

using namespace std;

class Persona {
private:
    string nombre;

public:
    Persona(const string& nombre) : nombre(nombre) {}

    string getDescripcion() const {
        return "Persona con nombre " + nombre;
    }

    void setNombre(const string& nuevoNombre) {
        nombre = nuevoNombre;
    }
};

class Poste {
private:
    int altura;
    int diametro;

public:
    Poste(int altura, int diametro) : altura(altura), diametro(diametro) {}

    string getDescripcion() const {
        return "Poste con altura de " + to_string(altura) + " metros y " + to_string(diametro) + " cm de diametro";
    }

    void setDatos(int nuevaAltura, int nuevoDiametro) {
        altura = nuevaAltura;
        diametro = nuevoDiametro;
    }
};

// Función genérica para imprimir descripción
template<typename T>
void imprimirDescripcion(const T& objeto) {
    cout << objeto.getDescripcion() << endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Persona persona1("Lucrecia");
    Persona persona2("Juan");
    Poste poste1(8, 15);
    Poste poste2(10, 2);

    // Imprimir descripción de los objetos
    imprimirDescripcion(persona1);
    imprimirDescripcion(persona2);
    imprimirDescripcion(poste1);
    imprimirDescripcion(poste2);

    return a.exec();
}

