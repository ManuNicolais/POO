/*
En un Empty qmake Project
Crear una función genérica que imprima por consola sus valores ordenados
Es decir, se le pasa un array con sus valores en cualquier orden, y la función genérica los imprime ordenados
Que el prototipo sea: template < class T > void imprimir( T * v, int cantidad, bool mayor_a_menor );
Utilizar el método de ordenamiento por inserción
Probar esta función en main utilizando dos arrays (int y float) y ordenar de mayor a menor y el otro al revés
*/

#include <QCoreApplication>
#include <iostream>

using namespace std;

template<class T>
void imprimir(T* v, int cantidad, bool mayor_a_menor) {
    // Ordenamiento por inserción
    for (int i = 1; i < cantidad; ++i) {
        T key = v[i];
        int j = i - 1;

        // Si es de mayor a menor, ordenar en reversa
        if (mayor_a_menor) {
            while (j >= 0 && v[j] < key) {
                v[j + 1] = v[j];
                j = j - 1;
            }
        } else {
            while (j >= 0 && v[j] > key) {
                v[j + 1] = v[j];
                j = j - 1;
            }
        }
        v[j + 1] = key;
    }

    cout << "Array ordenado: ";
    for (int i = 0; i < cantidad; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Array de enteros
    int arr_int[] = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int n_int = sizeof(arr_int) / sizeof(arr_int[0]);

    cout << "Ordenado de mayor a menor:" << endl;
    imprimir(arr_int, n_int, true);

    float arr_float[] = {3.14, 2.71, 1.618, 0.577, 2.718, 1.414};
    int n_float = sizeof(arr_float) / sizeof(arr_float[0]);

    // Imprimir el array de floats ordenado de menor a mayor
    cout << "Ordenado de menor a mayor:" << endl;
    imprimir(arr_float, n_float, false);

    return a.exec();
}




