#include <iostream>
#include <fstream>
#include <string>
//#include "Library_problems.h"
using namespace std;

int contarUnos(const string& bloque) {
    int contador = 0;
    for (char bit : bloque) {
        if (bit == '1') contador++;
    }
    return contador;
}

string codificarMetodo1(const string& binario, int n) {
    string codificado;
    int totalBloques = binario.length() / n;
    string bloqueAnterior = "";

    for (int i = 0; i < totalBloques; i++) {
        string bloque = binario.substr(i * n, n);
        string nuevoBloque = "";

        if (i == 0) {
            for (char bit : bloque) {
                nuevoBloque += (bit == '1') ? '0' : '1';
            }
        } else {
            int unos = contarUnos(bloqueAnterior);
            int ceros = n - unos;

            if (unos == ceros) {
                for (char bit : bloque) {
                    nuevoBloque += (bit == '1') ? '0' : '1';
                }
            } else if (ceros > unos) {
                for (int j = 0; j < n; j++) {
                    if ((j + 1) % 2 == 0) {
                        nuevoBloque += (bloque[j] == '1') ? '0' : '1';
                    } else {
                        nuevoBloque += bloque[j];
                    }
                }
            } else {
                for (int j = 0; j < n; j++) {
                    if ((j + 1) % 3 == 0) {
                        nuevoBloque += (bloque[j] == '1') ? '0' : '1';
                    } else {
                        nuevoBloque += bloque[j];
                    }
                }
            }
        }

        codificado += nuevoBloque;
        bloqueAnterior = bloque;
    }

    return codificado;
}

string codificarMetodo2(const string& binario, int n) {
    string codificado;
    for (size_t i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);
        string nuevoBloque = "";

        if (bloque.length() == 1) {
            nuevoBloque = bloque;
        } else {
            nuevoBloque += bloque[bloque.length() - 1];
            for (size_t j = 0; j < bloque.length() - 1; j++) {
                nuevoBloque += bloque[j];
            }
        }

        codificado += nuevoBloque;
    }

    return codificado;
}

void guardarComoBinario(const string& bits, const string& nombreSalida) {
    ofstream salida(nombreSalida, ios::binary);
    if (!salida) throw "No se pudo abrir el archivo de salida.";

    unsigned char byte = 0;
    int contador = 0;

    for (char bit : bits) {
        byte = byte << 1;
        if (bit == '1') byte |= 1;
        contador++;

        if (contador == 8) {
            salida.put(byte);
            byte = 0;
            contador = 0;
        }
    }

    if (contador > 0) {
        byte = byte << (8 - contador);
        salida.put(byte);
    }

    salida.close();
}

void codificar(){
    try {
        string nombreEntrada, nombreSalida;
        int n, metodo;

        cout << "Nombre del archivo de entrada: ";
        cin >> nombreEntrada;

        cout << "Nombre del archivo de salida (.bin): ";
        cin >> nombreSalida;

        cout << "Ingrese la semilla n: ";
        cin >> n;
        if (n <= 0) throw "La semilla debe ser un número mayor a 0.";

        cout << "Ingrese el metodo (1 o 2): ";
        cin >> metodo;
        if (metodo != 1 && metodo != 2) throw "Metodo inválido. Solo se permite 1 o 2.";

        ifstream entrada(nombreEntrada, ios::binary);
        if (!entrada) throw "No se pudo abrir el archivo de entrada.";

        string binario = "";
        char c;
        while (entrada.get(c)) {
            for (int i = 7; i >= 0; i--) {
                binario += ((c >> i) & 1) ? '1' : '0';
            }
        }
        entrada.close();

        while (binario.length() % n != 0) {
            binario += '0';
        }

        string codificado = (metodo == 1)
                                ? codificarMetodo1(binario, n)
                                : codificarMetodo2(binario, n);

        guardarComoBinario(codificado, nombreSalida);
        cout << "Archivo codificado correctamente (metodo " << metodo << ").\n";
    }
    catch (const char* error) {
        cerr << "Error: " << error << "\n";
    }
    catch (...) {
        cerr << "Error inesperado.\n";
    }

}

// --- Funciones auxiliares (sin cambios) ---
char binarioAChar(string bits) {
    char c = 0;
    for (int i = 0; i < 8; i++) {
        c = c << 1;
        if (bits[i] == '1') {
            c |= 1;
        }
    }
    return c;
}
/*
int contarUnos(const string& bloque) {
    int count = 0;
    for (char b : bloque) {
        if (b == '1') count++;
    }
    return count;
}
*/
// --- Método 1 ---
void decodificarMetodo1(string& binario, int n) {
    string original = "";
    size_t total = binario.length();

    for (size_t i = 0; i < total; i += n) {
        string bloqueCodificado = binario.substr(i, n);
        string bloqueDescodificado = "";

        if (i == 0) {
            for (char bit : bloqueCodificado) {
                bloqueDescodificado += (bit == '0') ? '1' : '0';
            }
        } else {
            string anterior = original.substr(i - n, n);
            int unos = contarUnos(anterior);
            int ceros = n - unos;

            if (unos == ceros) {
                for (char bit : bloqueCodificado) {
                    bloqueDescodificado += (bit == '0') ? '1' : '0';
                }
            } else if (ceros > unos) {
                for (int j = 0; j < n; j++) {
                    if ((j + 1) % 2 == 0) {
                        bloqueDescodificado += (bloqueCodificado[j] == '0') ? '1' : '0';
                    } else {
                        bloqueDescodificado += bloqueCodificado[j];
                    }
                }
            } else {
                for (int j = 0; j < n; j++) {
                    if ((j + 1) % 3 == 0) {
                        bloqueDescodificado += (bloqueCodificado[j] == '0') ? '1' : '0';
                    } else {
                        bloqueDescodificado += bloqueCodificado[j];
                    }
                }
            }
        }

        original += bloqueDescodificado;
    }

    binario = original;
}

// --- Método 2 ---
void decodificarMetodo2(string& binario, int n) {
    string resultado = "";

    for (size_t i = 0; i < binario.length(); i += n) {
        string bloque = binario.substr(i, n);
        string bloqueNuevo = "";

        if (bloque.length() == 1) {
            bloqueNuevo = bloque;
        } else {
            for (size_t j = 1; j < bloque.length(); j++) {
                bloqueNuevo += bloque[j];
            }
            bloqueNuevo += bloque[0];
        }

        resultado += bloqueNuevo;
    }

    binario = resultado;
}

void decodificar(){
    try {
        string archivoEntrada, archivoSalida;
        int metodo, n;

        cout << "Ingrese el nombre del archivo codificado: ";
        cin >> archivoEntrada;

        cout << "Ingrese el nombre del archivo de salida (decodificado): ";
        cin >> archivoSalida;

        cout << "Ingrese la semilla (n): ";
        if (!(cin >> n) || n <= 0) throw "La semilla debe ser un número entero positivo.";

        cout << "Ingrese el metodo (1 o 2): ";
        if (!(cin >> metodo) || (metodo != 1 && metodo != 2)) throw "Método inválido. Solo se permite 1 o 2.";

        ifstream entrada(archivoEntrada, ios::binary);
        if (!entrada) throw "No se pudo abrir el archivo de entrada.";

        string binario = "";
        char byte;
        while (entrada.get(byte)) {
            for (int i = 7; i >= 0; i--) {
                binario += ((byte >> i) & 1) + '0';
            }
        }
        entrada.close();

        if (metodo == 1) {
            decodificarMetodo1(binario, n);
        } else {
            decodificarMetodo2(binario, n);
        }

        ofstream salida(archivoSalida, ios::binary);
        if (!salida) throw "No se pudo abrir el archivo de salida.";

        for (size_t i = 0; i + 7 < binario.length(); i += 8) {
            string byteStr = binario.substr(i, 8);
            char c = binarioAChar(byteStr);
            salida.put(c);
        }

        salida.close();
        cout << "Archivo decodificado guardado exitosamente.\n";

    } catch (const char* error) {
        cerr << "Error: " << error << "\n";
    } catch (...) {
        cerr << "Ocurrió un error inesperado.\n";
    }

}

const string CLAVE_SECRETA = "MiClave123";

// ========================= FUNCIONES DE CIFRADO =========================

string charABinario(char c) {
    string bin = "";
    for (int i = 7; i >= 0; i--) {
        bin += ((c >> i) & 1) + '0';
    }
    return bin;
}

string xorConClave(const string& texto, const string& clave) {
    string resultado = texto;
    for (size_t i = 0; i < texto.length(); ++i) {
        resultado[i] = resultado[i] ^ clave[i % clave.length()];
    }
    return resultado;
}

string textoABinario(string texto) {
    texto = xorConClave(texto, CLAVE_SECRETA);
    string bin = "";
    for (size_t i = 0; i < texto.length(); i++) {
        bin += charABinario(texto[i]);
    }

    return bin;
}
/*
char binarioAChar(string bits) {
    char c = 0;
    for (int i = 0; i < 8; i++) {
        c = (c << 1) | (bits[i] - '0');
    }
    return c;
}
*/
string binarioATexto(string binario) {
    string texto = "";
    for (size_t i = 0; i + 7 < binario.length(); i += 8) {
        texto += binarioAChar(binario.substr(i, 8));
    }
    return xorConClave(texto, CLAVE_SECRETA);
}

// ========================= FUNCIONES DE VALIDACION =========================

bool cedulaEsValida(const string& cedula) {
    if (cedula.empty()) return false;
    for (char c : cedula) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool cedulaYaRegistrada(const string& cedula) {
    ifstream file("usuarios.txt");
    if (!file) return false;

    string linea;
    string binCedula = textoABinario(cedula);
    while (getline(file, linea)) {
        size_t pos = linea.find(",");
        if (linea.substr(0, pos) == binCedula) {
            return true;
        }
    }
    return false;
}

// ========================= FUNCIONES DE ADMINISTRADOR =========================

bool validarAdmin() {
    string clave;
    cout << "Ingrese la clave del administrador: ";
    cin >> clave;

    ifstream file("C:/Users/buelv/Downloads/sudo.txt");
    if (!file) {
        cerr << "Error: No se pudo abrir el archivo sudo.txt\n";
        return false;
    }

    string claveBin;
    getline(file, claveBin);
    file.close();

    return textoABinario(clave) == claveBin;
}

void registrarUsuario() {
    try {
        string cedula, clave;
        int saldo;

        cout << "Cedula: ";
        cin >> cedula;
        if (!cedulaEsValida(cedula)) throw "La cedula debe contener solo digitos.";

        if (cedulaYaRegistrada(cedula)) throw "Cedula ya registrada.";

        cout << "Clave: ";
        cin >> clave;

        cout << "Saldo inicial (COP): ";
        if (!(cin >> saldo)) throw "Ingrese un numero valido para el saldo.";
        if (saldo < 0) throw "El saldo no puede ser negativo.";

        ofstream file("usuarios.txt", ios::app);
        if (!file) throw "No se pudo abrir el archivo usuarios.txt para escribir.";

        string registro = textoABinario(cedula) + "," +
                          textoABinario(clave) + "," +
                          textoABinario(to_string(saldo)) + "\n";

        file << registro;
        file.close();

        cout << "Usuario registrado exitosamente.\n";

    } catch (const char* msg) {
        cerr << "Error: " << msg << "\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

// ========================= FUNCIONES DE USUARIO =========================

bool buscarUsuario(string cedula, string clave, string& saldoBin, int& posInicio) {
    ifstream file("usuarios.txt");
    if (!file) {
        cerr << "Error: No se pudo abrir usuarios.txt.\n";
        return false;
    }

    string linea;
    int pos = 0;
    string binCedula = textoABinario(cedula);
    string binClave = textoABinario(clave);

    while (getline(file, linea)) {
        size_t p1 = linea.find(",");
        size_t p2 = linea.find(",", p1 + 1);

        if (linea.substr(0, p1) == binCedula &&
            linea.substr(p1 + 1, p2 - p1 - 1) == binClave) {
            saldoBin = linea.substr(p2 + 1);
            posInicio = pos;
            file.close();
            return true;
        }
        pos += linea.length() + 1;
    }

    file.close();
    return false;
}

void actualizarSaldo(string cedula, string clave, int nuevoSaldo) {
    ifstream file("usuarios.txt");
    ofstream temp("temp.txt");
    if (!file || !temp) {
        cerr << "Error: No se pudo abrir archivos para actualizar el saldo.\n";
        return;
    }

    string linea;
    while (getline(file, linea)) {
        size_t p1 = linea.find(",");
        size_t p2 = linea.find(",", p1 + 1);

        if (linea.substr(0, p1) == textoABinario(cedula) &&
            linea.substr(p1 + 1, p2 - p1 - 1) == textoABinario(clave)) {
            string nuevaLinea = textoABinario(cedula) + "," +
                                textoABinario(clave) + "," +
                                textoABinario(to_string(nuevoSaldo));
            temp << nuevaLinea << "\n";
        } else {
            temp << linea << "\n";
        }
    }

    file.close();
    temp.close();
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
}

void menuUsuario(string cedula, string clave) {
    try {
        string saldoBin;
        int pos;
        if (!buscarUsuario(cedula, clave, saldoBin, pos)) {
            throw "Usuario o clave incorrectos.";
        }

        string saldoTexto = binarioATexto(saldoBin);
        int saldo = atoi(saldoTexto.c_str()) - 1000;
        if (saldo < 0) throw "Saldo insuficiente para cubrir la tarifa.";

        int opcion;
        cout << "1. Consultar saldo\n2. Retirar dinero\nOpcion: ";
        if (!(cin >> opcion)) throw "Debe ingresar un numero.";

        if (opcion == 1) {
            cout << "Saldo disponible: " << saldo << " COP\n";
        } else if (opcion == 2) {
            int retiro;
            cout << "Cantidad a retirar: ";
            if (!(cin >> retiro)) throw "Debe ingresar una cantidad valida.";
            if (retiro > saldo) throw "Saldo insuficiente para el retiro.";
            saldo -= retiro;
            cout << "Retiro exitoso. Nuevo saldo: " << saldo << " COP\n";
        } else {
            throw "Opcion invalida.";
        }

        actualizarSaldo(cedula, clave, saldo);

    } catch (const char* msg) {
        cerr << "Error: " << msg << "\n";
        cin.clear();
        cin.ignore(1000, '\n');
    } catch (...) {
        cerr << "Ocurrio un error inesperado.\n";
    }
}

void aplicacion(){
    try {
        int tipo;
        cout << "1. Acceder como administrador\n2. Acceder como usuario\nOpcion: ";
        if (!(cin >> tipo)) throw "Debe ingresar un numero.";

        if (tipo == 1) {
            if (validarAdmin()) {
                cout << "--- Administrador autenticado ---\n";
                registrarUsuario();
            } else {
                cerr << "Clave incorrecta.\n";
            }
        } else if (tipo == 2) {
            string cedula, clave;
            cout << "Cedula: ";
            cin >> cedula;
            cout << "Clave: ";
            cin >> clave;
            menuUsuario(cedula, clave);
        } else {
            throw "Opcion invalida.";
        }

    } catch (const char* msg) {
        cerr << "Error: " << msg << "\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
