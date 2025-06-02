#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <map>
#include <string>
using namespace std;

class Router {
public:
    string nombre;
    map<string, pair<int, string>> tablaEnrutamiento;

    Router();
    Router(string id);
    void mostrarTabla();
};

#endif
