#ifndef PARED_H
#define PARED_H

#include <QGraphicsRectItem>

/**
 * @brief La clase Pared representa una pared del laberinto en el juego Pacman.
 *
 * Hereda de QGraphicsRectItem para ser colocada como un rectángulo en la escena gráfica.
 * Las paredes se utilizan como obstáculos que Pacman no puede atravesar.
 */
class Pared : public QGraphicsRectItem {
public:
    /**
     * @brief Constructor de la clase Pared.
     *
     * Inicializa un rectángulo de tamaño fijo (usualmente 30x30 px)
     * con color azul para representar una celda de muro del laberinto.
     */
    Pared();
};

#endif // PARED_H
