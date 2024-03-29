#include <iostream>

#include <cstdlib>

using namespace std;

int main()
{
    int numeros[10];

    // Inicializar la semilla aleatoria con el tiempo actual
    srand(time(nullptr));

    for (int i = 0; i < 10; ++i) {

        // Generar un número aleatorio en el intervalo [2, 20]
        numeros[i] = rand() % 19 + 2;
        cout << "Número aleatorio " << i+1 << ": " << numeros[i] << endl;
    }

    return 0;
}
