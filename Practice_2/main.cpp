#include <iostream>
#include "Library_problems.h"
using namespace std;

int main(){

    int opcion;
    cout << "Ingrese el numero del problema que desea ver: ";
    cin >> opcion ;

    switch (opcion) {
    case 1:
        problema1();
        break;
    case 3:
        problema3();
        break;
    case 5:
        problema5();
        break;
    case 7:
        problema7();
        break;
    case 9:
        problema9();
        break;
    case 11:
        problema11();
        break;
    case 13:
        problema13();
        break;
    case 15:
        problema15();
        break;
    case 17:
        problema17();
        break;
    default:
        cout << "El numero tiene que ser impar" << endl;
        break;
    }

    return 0;
}
