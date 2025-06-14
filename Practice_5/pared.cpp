#include "pared.h"
#include <QBrush>
#include <QPen>

/**
 * @brief Constructor de la clase Pared.
 *
 * Inicializa una celda de pared con tamaño fijo (30x30 píxeles),
 * la pinta de color azul sólido y elimina el borde para una visualización limpia.
 * Esta clase se utiliza para representar obstáculos en el laberinto que
 * Pacman no puede atravesar.
 */
Pared::Pared() {
    // Pared fija de 30x30, alineada con el tile del mapa
    setRect(0, 0, 30, 30);
    setBrush(QBrush(Qt::blue));
    setPen(Qt::NoPen); // elimina borde para mejor visual
}
