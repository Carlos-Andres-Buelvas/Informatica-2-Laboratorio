#include "router.h"

Router::Router() : nombre("") {}
Router::Router(string id) : nombre(id) {}

void Router::mostrarTabla() {
    cout << "\nTabla de enrutamiento para router " << nombre << ":\n";
    for (auto& [destino, info] : tablaEnrutamiento) {
        cout << "  Destino: " << destino << ", Costo: " << info.first
             << ", Siguiente salto: " << info.second << endl;
    }
}
