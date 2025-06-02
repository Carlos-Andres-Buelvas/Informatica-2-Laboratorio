#include <iostream>
#include "red.h"
using namespace std;

void probarLecturaArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "[ERROR] No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    cout << "\nContenido del archivo '" << nombreArchivo << "':\n";
    string origen, destino;
    int costo;
    while (archivo >> origen >> destino >> costo) {
        cout << "  " << origen << " -> " << destino << " con costo " << costo << endl;
    }

    archivo.close();
    cout << "Archivo leído correctamente.\n";
}

int main() {
    Red red;
    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Cargar red desde archivo\n";
        cout << "2. Mostrar tabla de un router\n";
        cout << "3. Consultar costo entre routers\n";
        cout << "4. Mostrar ruta entre routers\n";
        cout << "5. Eliminar router\n";
        cout << "6. Modificar costo entre routers\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string archivo;
            cout << "Ingrese nombre de archivo: ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);
            probarLecturaArchivo(archivo);
        } else if (opcion == 2) {
            string router;
            cout << "Ingrese el nombre del router: ";
            cin >> router;
            red.mostrarTablaRouter(router);
        } else if (opcion == 3) {
            string origen, destino;
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            red.consultarCosto(origen, destino);
        } else if (opcion == 4) {
            string origen, destino;
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            red.mostrarRuta(origen, destino);
        } else if (opcion == 5) {
            string router;
            cout << "Nombre del router a eliminar: ";
            cin >> router;
            red.eliminarRouter(router);
        } else if (opcion == 6) {
            string a, b;
            int nuevoCosto;
            cout << "Router A: "; cin >> a;
            cout << "Router B: "; cin >> b;
            cout << "Nuevo costo: "; cin >> nuevoCosto;
            red.conectar(a, b, nuevoCosto);
        }
    } while (opcion != 0);

    return 0;
}

/*
    Dentro de la carpeta build\Desktop_Qt_6_8_1_MinGW_64_bit-Debug se encuentra
    los archivos de text 'red.txt' y 'red2.txt'.
*/
