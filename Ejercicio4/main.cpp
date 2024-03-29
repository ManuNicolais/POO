#include <QCoreApplication>
#include <QDebug>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<int> Num;
    srand(time(NULL));

    // Generar 30 números aleatorios y agregarlos
    for (int i = 0; i < 30; ++i) {
        int num = 1 + rand() % 15;
        Num.push_back(num);
    }

    // Imprimir el vector
    cout << "Números generados:" << endl;
    for (int num : Num) {
        cout << num << " ";
    }
    cout << endl;

    return a.exec();
}
