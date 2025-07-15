#include "mainwindow.h"
#include <QApplication>

/**
 * @brief Función principal del programa.
 *
 * Esta función inicializa la aplicación Qt, crea la ventana principal
 * y lanza el bucle de eventos de la interfaz gráfica.
 *
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @return Código de salida de la aplicación.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  ///< Inicializa la aplicación Qt con los argumentos del sistema.
    MainWindow w;                ///< Crea la ventana principal de la simulación.
    w.show();                    ///< Muestra la ventana.
    return a.exec();             ///< Inicia el bucle principal de eventos.
}
