#include <iostream>
using namespace std;

void problema1(){
    char caracter;

    cout << "Ingrese un caracter: ";
    //caracter = cin.get();
    cin >> caracter;

    // Convertir a minuscula si es una letra mayuscula
    if (caracter >= 'A' && caracter <= 'Z') {
        caracter += 32;
    }

    // Verificar si es una letra minuscula
    if (caracter >= 'a' && caracter <= 'z') {
        if (caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u') {
            cout << "El caracter " << caracter << " es una vocal." << endl;
        } else {
            cout << "El caracter " << caracter << " es una consonante." << endl;
        }
    } else {
        cout << "El caracter ingresado no es una letra del alfabeto." << endl;
    }

}
void problema3(){
    int mes, dia;

    cout << "Ingrese el mes: " << endl;
    cin >> mes;
    cout << "Ingrese el dia: " << endl;
    cin >> dia;

    if (mes > 12 || mes < 1) {
        cout << mes << " es un mes invalido." << endl;
    } else {
        int diasEnMes;

        // Usar switch para determinar la cantidad de dias en el mes
        switch (mes) {
        case 2:
            diasEnMes = 29;  // Febrero tiene 28 dias, 29 en bisiesto
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            diasEnMes = 30;
            break;
        default:
            diasEnMes = 31;
        }

        // Validar el dia
        if (dia < 1 || dia > diasEnMes) {
            cout << dia << "/" << mes << " es una fecha invalida." << endl;
        } else if (mes == 2 && dia == 29) {
            cout << dia << "/" << mes << " es valida en bisiesto." << endl; // Casos especiales para el 29 de febrero
        } else {
            cout << dia << "/" << mes << " es una fecha valida." << endl;
        }
    }

}
void problema5(){
    int n;

    cout << "Ingrese un numero impar: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "ERROR! El numero debe ser impar" << endl;
        return;
    }

    // Parte superior del patron
    for (int i = 1; i <= n; i += 2) {
        // Imprimir espacios en blanco antes de los asteriscos
        for (int j = 0; j < (n - i) / 2; j++) {
            cout << " ";
        }
        // Imprimir los asteriscos
        for (int j = 0; j < i; j++) {
            cout << "*";
        }
        cout << endl;
    }

    // Parte inferior del patron
    for (int i = n - 2; i >= 1; i -= 2) {
        // Imprimir espacios en blanco antes de los asteriscos
        for (int j = 0; j < (n - i) / 2; j++) {
            cout << " ";
        }
        // Imprimir los asteriscos
        for (int j = 0; j < i; j++) {
            cout << "*";
        }
        cout << endl;
    }
}
void problema7(){
    int n;
    cout << "Ingrese un numero: ";
    cin >> n;

    int a = 1, b = 1, suma = 0;

    // Generar la serie de Fibonacci y sumar los numeros pares menores que n
    while (b < n) {
        if (b % 2 == 0) {
            suma += b;
        }
        int temp = a + b;
        a = b;
        b = temp;
    }

    cout << "El resultado de la suma es: " << suma << endl;
}
void problema9(){
    int n, suma = 0;
    cout << "Ingrese un numero entero: ";
    cin >> n;

    if (n < 0) {
        n = -n;
    }

    while (n > 0) {
        int digito = n % 10;

        // Calcular el digito elevado a si mismo
        int potencia = 1;
        for (int i = 0; i < digito; i++) {
            potencia *= digito;
        }

        suma += potencia;
        n /= 10;
    }

    cout << "El resultado de la suma es: " << suma << endl;
}
void problema11(){
    int n;
    cout << "Ingresa un numero entero: ";
    cin >> n;

    int resultado = 1;

    for (int i = 1; i <= n; ++i){

        int a = resultado;
        int b = i;

        while (b !=0){
            int temp = b;
            b = a % b;
            a = temp;

        }

        int mcd = a;

        resultado = (resultado*i)/mcd;
    }

    cout << "El minimo comun multiplo es " << resultado << endl;
}
void problema13(){
    int n, suma = 0;
    cout << "Ingrese un numero: ";
    cin >> n;

    // Funcion simple para verificar si un numero es primo
    for (int i = 2; i < n; i++) {
        bool esPrimo = true;
        for (int j = 2; j * j <= i; j++) {  //También funciona j < i
            if (i % j == 0) {
                esPrimo = false;
                break;
            }
        }
        if (esPrimo) {
            suma += i;
        }
    }

    cout << "El resultado de la suma es: " << suma << endl;

}
void problema15(){
    int n;
    cout << "Ingrese un numero impar: ";
    cin >> n;

    if (n % 2 == 0) {
        cout << "Error: El numero debe ser impar." << endl;
        return;
    }

    int suma = 1; // La suma empieza en 1, que es el centro de la espiral
    int numero_actual = 1;


    for (int i = 2; i < n; i += 2) {
        for (int j = 0; j < 4; j++) { // 4 esquinas en cada capa de la espiral
            numero_actual += i;
            suma += numero_actual;
        }
    }

    cout << "En una espiral de " << n << "x" << n << ", la suma es: " << suma << endl;
}

int contarDivisores(int n) {
    int conteo = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            conteo++;
        }
    }
    return conteo;
}
// Funcion principal para encontrar el primer numero triangular con mas de k divisores
int k_divisores(int k) {
    int n = 1;
    while (true) {

        int triangular = (n * (n + 1)) / 2;

        // Cuenta los divisores del numero triangular
        int divisores = contarDivisores(triangular);

        // Si encontramos un numero triangular con mas de k divisores, lo retornamos
        if (divisores > k) {
            cout << endl << "El numero triangular es: " << triangular << " que tiene " << divisores << " divisores." << endl;
            return triangular;
        }

        // Incrementa n para el siguiente numero triangular
        n++;
    }
}
void problema17(){
    int k;
    cout << "Ingrese el valor de k: ";
    cin >> k;

    k_divisores(k);
    // No es necesario volver a imprimir los divisores aquí, ya que se imprimió dentro de la función k_divisores.
}
