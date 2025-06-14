#include <QApplication>
#include "game.h"

/**
 * @brief Punto de entrada principal de la aplicación.
 *
 * Crea una instancia de QApplication, inicializa el objeto Game
 * (que representa la ventana principal del juego), lo muestra en pantalla
 * y ejecuta el bucle de eventos de Qt.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Arreglo de argumentos de línea de comandos.
 * @return int Código de salida del programa.
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Game* juego = new Game();
    juego->show();

    return a.exec();
}
