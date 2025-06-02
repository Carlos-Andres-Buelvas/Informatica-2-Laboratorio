#include "red.h"

void Red::agregarRouter(const string& id) {
    if (routers.count(id) == 0) {
        routers[id] = Router(id);
        cout << "Router '" << id << "' agregado.\n";
    }
}

void Red::eliminarRouter(const string& id) {
    if (routers.count(id) == 0) {
        cout << "Router no encontrado.\n";
        return;
    }
    routers.erase(id);
    adyacencias.erase(id);
    for (auto& [r, vecinos] : adyacencias) {
        vecinos.erase(id);
    }
    cout << "Router '" << id << "' eliminado correctamente.\n";
    actualizarTablas();
}

void Red::conectar(const string& origen, const string& destino, int costo) {
    if (routers.count(origen) == 0 || routers.count(destino) == 0) {
        cout << "Uno de los routers no existe.\n";
        return;
    }
    adyacencias[origen][destino] = costo;
    adyacencias[destino][origen] = costo;
    cout << "Conexion actualizada entre " << origen << " y " << destino << " con costo " << costo << ".\n";
    actualizarTablas();
}

void Red::cargarDesdeArchivo(const string& archivo) {
    ifstream file(archivo);
    string a, b;
    int costo;
    while (file >> a >> b >> costo) {
        agregarRouter(a);
        agregarRouter(b);
        conectar(a, b, costo);
    }
    file.close();
    actualizarTablas();
}

void Red::actualizarTablas() {
    for (auto& [nombre, _] : routers) {
        dijkstra(nombre);
    }
}

void Red::dijkstra(const string& origen) {
    map<string, int> dist;
    map<string, string> previo;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    for (auto& [nombre, _] : routers) {
        dist[nombre] = INF;
    }

    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [costo, actual] = pq.top(); pq.pop();

        for (auto& [vecino, peso] : adyacencias[actual]) {
            if (dist[actual] + peso < dist[vecino]) {
                dist[vecino] = dist[actual] + peso;
                previo[vecino] = actual;
                pq.push({dist[vecino], vecino});
            }
        }
    }

    routers[origen].tablaEnrutamiento.clear();
    for (auto& [destino, costo] : dist) {
        if (destino == origen || costo == INF) continue;
        string salto = destino;
        while (previo[salto] != origen) {
            salto = previo[salto];
        }
        routers[origen].tablaEnrutamiento[destino] = {costo, salto};
    }
}

void Red::mostrarTablaRouter(const string& id) {
    if (routers.count(id)) {
        routers[id].mostrarTabla();
    } else {
        cout << "Router no encontrado.\n";
    }
}

void Red::consultarCosto(const string& a, const string& b) {
    if (routers.count(a) && routers[a].tablaEnrutamiento.count(b)) {
        cout << "Costo de " << a << " a " << b << ": " << routers[a].tablaEnrutamiento[b].first << endl;
    } else {
        cout << "Ruta no encontrada.\n";
    }
}

void Red::mostrarRuta(const string& a, const string& b) {
    if (!routers.count(a) || !routers[a].tablaEnrutamiento.count(b)) {
        cout << "Ruta no encontrada.\n";
        return;
    }
    cout << "Ruta de " << a << " a " << b << ": ";
    cout << a << " -> ";
    string actual = a;
    while (actual != b) {
        actual = routers[actual].tablaEnrutamiento[b].second;
        cout << actual;
        if (actual != b) cout << " -> ";
    }
    cout << endl;
}
