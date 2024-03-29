#include <QCoreApplication>
#include <iostream>
#include <string>

using namespace std;

class Jugador{
private:
    int velocidad;
    int fuerza;
    string nombre;
public:
    Jugador() : velocidad(1), fuerza(5), nombre("Juan") {}
    Jugador(int v, int f, const string& n) : velocidad(v), fuerza(f), nombre(n) {}

    int getVelocidad() const { return velocidad; }
    void setVelocidad(int v) { velocidad = v; }

    int getFuerza() const { return fuerza; }
    void setFuerza(int f) { fuerza = f; }

    string getNombre() const { return nombre; }
    void setNombre(const string& n) { nombre = n; }

    ~Jugador() {}
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<Jugador> jugadores = {
        {2,6,"Matias"},
        {3,9,"Lucas"},
        {4,8,"Edgar"},
        {5,7,"Gaston"},
        {6,5,"Tomas"},
        {7,4,"Facu"},
        {8,3,"Gonza"},
        {9,2,"Martina"},
        {10,1,"Pedro"},
        {0,6,"Lucia"},
        };
    /*
    vector<Jugador> jugadores;

    // Insertar 10 jugadores distintos en el vector
    for (int i = 1; i <= 10; ++i) {
        Jugador jugador;
        jugador.setNombre("Jugador " + to_string(i));
        jugador.setVelocidad(i * 10);
        jugador.setFuerza(i * 5);
        jugadores.push_back(jugador);
    }
    */

    for (const Jugador& jugador : jugadores) {
        cout << "Nombre: " << jugador.getNombre() << ", Velocidad: " << jugador.getVelocidad()
                  << ", Fuerza: " << jugador.getFuerza() << endl;
    }

    return a.exec();
}
