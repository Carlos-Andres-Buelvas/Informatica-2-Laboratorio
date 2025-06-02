#include <iostream>
#include <fstream>
#include <string>
#include "Library_problems.h"
using namespace std;

int main(){

    int opcion;
    cout << "Ingrese el numero del problema que desea ver(1. Codificación, 2. Decodifcación, 3. Aplicación): ";
    cin >> opcion ;

    switch (opcion) {
    case 1:
        codificar();
        break;
    case 2:
        decodificar();
        break;
    case 3:
        aplicacion();
        break;
    default:
        cout << "Opción invalida" << endl;
        break;
    }

    return 0;
}
