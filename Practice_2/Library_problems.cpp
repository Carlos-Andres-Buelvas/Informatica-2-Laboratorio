#include <iostream>
using namespace std;

void problema1(){ //Arduino
    int billetes[] = {50000, 20000, 10000, 5000, 2000, 1000};
    int monedas[] = {500, 200, 100, 50};
    int cantidad, faltante;

    cout << "Ingrese la cantidad de dinero: ";
    cin >> cantidad;

    faltante = cantidad;

    // Procesar billetes
    for (int i = 0; i < 6; i++) {
        int num = faltante / billetes[i];
        cout << billetes[i] << ": " << num << endl;
        faltante = faltante % billetes[i];
    }

    // Procesar monedas
    for (int i = 0; i < 4; i++) {
        int num = faltante / monedas[i];
        cout << monedas[i] << ": " << num << endl;
        faltante = faltante % monedas[i];
    }

    cout << "Faltante: " << faltante << endl;

}

// Función que compara dos cadenas
bool compararCadenas(char* cadena1, char* cadena2) {
    int i = 0;

    // Mientras los caracteres sean iguales y no se llegue al final
    while (cadena1[i] != '\0' && cadena2[i] != '\0') {
        if (cadena1[i] != cadena2[i]) {
            return false; // Si encontramos una diferencia, son distintas
        }
        i++;
    }

    if (cadena1[i] == '\0' && cadena2[i] == '\0') {
        return true;
    } else {
        return false;
    }
}
void problema3(){
    char palabra1[100];
    char palabra2[100];

    cout << "Ingrese la primera cadena: ";
    cin.ignore();
    cin.getline(palabra1, 100); // Leer toda la línea

    cout << "Ingrese la segunda cadena: ";
    cin.getline(palabra2, 100);

    if (compararCadenas(palabra1, palabra2)) {
        cout << "Las cadenas son iguales." << endl;
    } else {
        cout << "Las cadenas son diferentes." << endl;
    }
}

// Función que convierte un número entero a una cadena
void convertirAString(int numero, char* cadena) {
    int i = 0;
    int temp = numero;
    int longitud = 0;

    // Caso especial si el número es 0
    if (numero == 0) {
        cadena[0] = '0';
        cadena[1] = '\0';
        return;
    }

    // Primero contamos cuántos dígitos tiene el número
    while (temp > 0) {
        temp = temp / 10;
        longitud++;
    }

    cadena[longitud] = '\0';

    while (numero > 0) {
        longitud--;
        int digito = numero % 10;
        cadena[longitud] = '0' + digito;
        numero = numero / 10;
    }
}
void problema5(){
    int numero;
    char cadena[20];

    cout << "Ingrese un numero entero: ";
    cin >> numero;

    convertirAString(numero, cadena);

    cout << "La cadena es: " << cadena << endl;

}

// Función que elimina caracteres repetidos
void eliminarRepetidos(char* cadena, char* resultado) {
    int i = 0, j = 0;
    bool usados[256] = {false}; // Para marcar caracteres ya usados (ASCII)

    while (cadena[i] != '\0') {
        if (!usados[(unsigned char)cadena[i]]) {
            resultado[j] = cadena[i];
            usados[(unsigned char)cadena[i]] = true;
            j++;
        }
        i++;
    }
    resultado[j] = '\0'; // Finalizar la nueva cadena
}
void problema7(){
    char original[100];
    char sinRepetidos[100];

    cout << "Ingrese una cadena: ";
    cin.ignore();
    cin.getline(original, 100);

    eliminarRepetidos(original, sinRepetidos);

    cout << "Original: " << original << endl;
    cout << "Sin repetidos: " << sinRepetidos << endl;
}

// Función que calcula la longitud de la cadena manualmente
int calcularLongitud(char* cadena) {
    int longitud = 0;
    while (cadena[longitud] != '\0') {
        longitud++;
    }
    return longitud;
}
// Función que realiza la suma de grupos de n cifras
int sumarGrupos(char* cadena, int n) {
    int longitud = calcularLongitud(cadena);
    int suma = 0;
    int valor = 0;
    int contador = 0;

    // Calcular cuántos ceros hacen falta
    int faltan = (n - (longitud % n)) % n;

    // Sumamos ceros virtuales (no hay que modificar la cadena)
    contador = faltan;

    for (int i = 0; i < longitud; i++) {
        valor = valor * 10 + (cadena[i] - '0');
        contador++;

        if (contador == n) {
            suma += valor;
            valor = 0;
            contador = 0;
        }
    }

    return suma;
}
void problema9(){
    int n;
    char cadena[100];

    cout << "Ingrese el valor de n: ";
    cin >> n;

    cout << "Ingrese la cadena numerica: ";
    cin.ignore(); // Limpiar el buffer
    cin.getline(cadena, 100);

    cout << "Original: " << cadena << endl;

    int resultado = sumarGrupos(cadena, n);

    cout << "Suma: " << resultado << endl;
}

const int FILAS = 15;
const int COLUMNAS = 20;
// Función para mostrar la sala
void mostrarSala(char sala[FILAS][COLUMNAS]) {
    cout << "    ";
    for (int i = 1; i <= COLUMNAS; i++) {
        if (i < 10) cout << " " << i << " "; // Alinear números pequeños
        else cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < FILAS; i++) {
        cout << (char)('A' + i) << "  "; // Mostrar letras A-O

        for (int j = 0; j < COLUMNAS; j++) {
            cout << " " << sala[i][j] << " ";
        }
        cout << endl;
    }
}
// Función para reservar asiento
void reservarAsiento(char sala[FILAS][COLUMNAS], char filaLetra, int asiento) {
    if (filaLetra >= 'a' && filaLetra <= 'o') {
        filaLetra = filaLetra - ('a' - 'A'); // Convertir a mayúscula
    }

    int fila = filaLetra - 'A'; // Convertir letra a número
    int columna = asiento - 1;  // Porque empieza desde 0

    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        if (sala[fila][columna] == '-') {
            sala[fila][columna] = '+';
            cout << "Reserva exitosa." << endl;
        } else {
            cout << "Asiento ya reservado." << endl;
        }
    } else {
        cout << "Fila o asiento invalido." << endl;
    }
}
// Función para cancelar reserva
void cancelarReserva(char sala[FILAS][COLUMNAS], char filaLetra, int asiento) {
    if (filaLetra >= 'a' && filaLetra <= 'o') {
        filaLetra = filaLetra - ('a' - 'A'); // Convertir a mayúscula
    }

    int fila = filaLetra - 'A';
    int columna = asiento - 1;

    if (fila >= 0 && fila < FILAS && columna >= 0 && columna < COLUMNAS) {
        if (sala[fila][columna] == '+') {
            sala[fila][columna] = '-';
            cout << "Cancelacion exitosa." << endl;
        } else {
            cout << "El asiento ya estaba disponible." << endl;
        }
    } else {
        cout << "Fila o asiento invalido." << endl;
    }
}
void problema11(){
    char sala[FILAS][COLUMNAS];

    // Inicializar sala toda disponible
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            sala[i][j] = '-';
        }
    }

    int opcion;
    char fila;
    int asiento;

    do {
        cout << "\n----- MENU -----\n";
        cout << "1. Mostrar sala\n";
        cout << "2. Reservar asiento\n";
        cout << "3. Cancelar reserva\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            mostrarSala(sala);
            break;
        case 2:
            cout << "Ingrese fila (A-O): ";
            cin >> fila;
            cout << "Ingrese numero de asiento (1-20): ";
            cin >> asiento;
            reservarAsiento(sala, fila, asiento);
            break;
        case 3:
            cout << "Ingrese fila (A-O): ";
            cin >> fila;
            cout << "Ingrese numero de asiento (1-20): ";
            cin >> asiento;
            cancelarReserva(sala, fila, asiento);
            break;
        case 4:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}

// Función que cuenta las estrellas en la matriz
int contarEstrellas(int* matriz, int filas, int columnas) {
    int contador = 0;

    // Recorremos la matriz, pero ignoramos los bordes
    for (int i = 1; i < filas - 1; i++) {
        for (int j = 1; j < columnas - 1; j++) {
            // Acceder a los elementos usando punteros
            int centro = *((matriz + i * columnas) + j);
            int izquierda = *((matriz + i * columnas) + (j - 1));
            int derecha = *((matriz + i * columnas) + (j + 1));
            int arriba = *((matriz + (i - 1) * columnas) + j);
            int abajo = *((matriz + (i + 1) * columnas) + j);

            int promedio = (centro + izquierda + derecha + arriba + abajo) / 5;

            if (promedio > 6) {
                contador++;
            }
        }
    }

    return contador;
}
void problema13(){
    int galaxia[6][8] = {
        {0, 3, 4, 0, 0, 0, 6, 8},
        {5, 13, 6, 0, 0, 0, 2, 3},
        {2, 6, 2, 7, 3, 0, 10, 0},
        {0, 0, 4, 15, 4, 1, 6, 0},
        {0, 0, 7, 12, 6, 9, 10, 4},
        {5, 0, 6, 10, 6, 4, 8, 0}
    };

    int filas = 6;
    int columnas = 8;

    int numeroEstrellas = contarEstrellas((int*)galaxia, filas, columnas);

    cout << "Numero de estrellas encontradas: " << numeroEstrellas << endl;
}

// Función que calcula la intersección de dos rectángulos SIN usar max/min
void interseccionRectangulos(int A[4], int B[4], int C[4]) {
    int A_x1 = A[0];
    int A_y1 = A[1];
    int A_x2 = A[0] + A[2];
    int A_y2 = A[1] + A[3];

    int B_x1 = B[0];
    int B_y1 = B[1];
    int B_x2 = B[0] + B[2];
    int B_y2 = B[1] + B[3];

    int C_x1, C_y1, C_x2, C_y2;

    // Calcular C_x1
    if (A_x1 > B_x1) {
        C_x1 = A_x1;
    } else {
        C_x1 = B_x1;
    }

    // Calcular C_y1
    if (A_y1 > B_y1) {
        C_y1 = A_y1;
    } else {
        C_y1 = B_y1;
    }

    // Calcular C_x2
    if (A_x2 < B_x2) {
        C_x2 = A_x2;
    } else {
        C_x2 = B_x2;
    }

    // Calcular C_y2
    if (A_y2 < B_y2) {
        C_y2 = A_y2;
    } else {
        C_y2 = B_y2;
    }

    // Verificar si realmente hay intersección
    if (C_x1 < C_x2 && C_y1 < C_y2) {
        C[0] = C_x1;
        C[1] = C_y1;
        C[2] = C_x2 - C_x1; // Ancho
        C[3] = C_y2 - C_y1; // Alto
    } else {
        // No hay intersección
        C[0] = C[1] = C[2] = C[3] = 0;
    }
}
void problema15(){
    int A[4], B[4], C[4];

    cout << "Ingrese los datos del rectangulo A (x, y, ancho, alto): " << endl;
    for (int i = 0; i < 4; i++) {
        cin >> A[i];
    }

    cout << "Ingrese los datos del rectangulo B (x, y, ancho, alto): " << endl;
    for (int i = 0; i < 4; i++) {
        cin >> B[i];
    }

    interseccionRectangulos(A, B, C);

    cout << "Rectangulo interseccion C: {";
    cout << C[0] << ", " << C[1] << ", " << C[2] << ", " << C[3] << "}" << endl;
}

// Función que calcula la suma de divisores propios
int sumaDivisores(int num) {
    int suma = 0;
    for (int i = 1; i <= num/2; i++) {
        if (num % i == 0) {
            suma += i;
        }
    }
    return suma;
}
void problema17(){ //Arduino
    int limite;
    int sumaAmigables = 0;

    cout << "Ingrese un numero: ";
    cin >> limite;

    for (int a = 2; a < limite; a++) {
        int b = sumaDivisores(a);

        if (b != a && b > a && sumaDivisores(b) == a) {
            // b > a para no contar dos veces (solo sumar el primero)
            sumaAmigables += a;
            if (b < limite) { // Si b también es menor al límite, lo sumamos
                sumaAmigables += b;
            }
        }
    }

    cout << "El resultado de la suma es: " << sumaAmigables << endl;
}
