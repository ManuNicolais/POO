#include <QApplication>
#include "login.h"

int main(int argc, char ** argv )
{
    QApplication a(argc, argv);

    Login login;
    login.show();

    return a.exec();
}

/*
#include <iostream>
using namespace std;

int main()
{


    int a = 10, b = 100, c = 30, d = 1, e = 54;
    int m[ 10 ] = { 10, 9, 80, 7, 60, 5, 40, 3, 20, 1 };
    int *p = &m[ 3 ], *q = &m[ 6 ];

    ++q;

    cout << a + m[ d / c ] + b-- / *q + 10 + e-- << endl;
    //10 + 0,33= 10 + 100 / 3 + 10 + 54
    // e-- = 54 le resta el valor luego de usarlo e = 53
    // b-- = 100 le resta el valor luego de usarlo b = 99

    p = m;
    cout << e + *p + m[ 9 ]++ << endl;
    //53 + 10 + 1

    return 0;
}
*/
