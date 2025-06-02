#ifndef RED_H
#define RED_H

#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include "router.h"
using namespace std;

const int INF = numeric_limits<int>::max();

class Red {
    map<string, Router> routers;
    map<string, map<string, int>> adyacencias;

public:
    void agregarRouter(const string& id);
    void eliminarRouter(const string& id);
    void conectar(const string& origen, const string& destino, int costo);
    void cargarDesdeArchivo(const string& archivo);
    void actualizarTablas();
    void dijkstra(const string& origen);
    void mostrarTablaRouter(const string& id);
    void consultarCosto(const string& a, const string& b);
    void mostrarRuta(const string& a, const string& b);
};

#endif
