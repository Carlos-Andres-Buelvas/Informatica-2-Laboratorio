#ifndef PUNTO_H
#define PUNTO_H

#include <QGraphicsEllipseItem>

/**
 * @brief La clase Punto representa un punto comestible en el juego Pacman.
 *
 * Hereda de QGraphicsEllipseItem para representarse como un círculo pequeño en la escena.
 * Los puntos son recogidos por Pacman y aumentan el puntaje del jugador.
 */
class Punto : public QGraphicsEllipseItem {
public:
    /**
     * @brief Constructor de la clase Punto.
     *
     * Inicializa el punto con tamaño reducido (usualmente 6x6 px) y color blanco.
     * Se debe posicionar de forma centrada dentro de una celda de 30x30 px.
     */
    Punto();
};

#endif // PUNTO_H
