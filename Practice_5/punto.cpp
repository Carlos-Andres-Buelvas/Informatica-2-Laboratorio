#include "punto.h"
#include <QBrush>
#include <QPen>

/**
 * @brief Constructor de la clase Punto.
 *
 * Representa un punto comestible en el juego Pacman.
 * Se inicializa como un círculo blanco pequeño (10x10 px) sin borde,
 * y debe colocarse centrado dentro de una celda de 30x30 px del laberinto.
 *
 * Este punto es eliminado al ser recogido por Pacman, y contribuye al puntaje.
 */
Punto::Punto() {
    // Punto pequeño, ideal para 30x30
    setRect(0, 0, 10, 10);
    setBrush(QBrush(Qt::white));
    setPen(Qt::NoPen);  // sin borde
}
