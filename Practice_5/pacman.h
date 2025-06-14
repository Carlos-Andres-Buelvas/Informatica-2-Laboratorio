#ifndef PACMAN_H
#define PACMAN_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>

/**
 * @brief La clase Pacman representa el personaje principal del juego.
 *
 * Hereda de QGraphicsPixmapItem para ser colocado en la escena gráfica,
 * y de QObject para poder usar señales y slots (temporizador).
 *
 * Controla movimiento por teclado, colisiones, animación de sprites,
 * y verificación de estado del juego (victoria).
 */
class Pacman : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    /**
     * @brief Constructor de la clase Pacman.
     *
     * Inicializa el sprite, las variables de dirección, configura
     * el temporizador de movimiento y activa el enfoque del teclado.
     */
    Pacman();

protected:
    /**
     * @brief Maneja los eventos de teclado para cambiar la dirección deseada.
     *
     * Las teclas válidas son:
     * - 'D' → derecha
     * - 'A' → izquierda
     * - 'S' → abajo
     * - 'Z' → arriba
     *
     * @param event Evento de teclado recibido.
     */
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    /**
     * @brief Método que se ejecuta periódicamente para mover a Pacman.
     *
     * Verifica colisiones con paredes, come puntos, actualiza el sprite,
     * y verifica si se ha ganado la partida.
     */
    void mover();

private:
    int dx, dy;               ///< Dirección actual en X e Y.
    int deseadoDx, deseadoDy; ///< Dirección deseada según la última tecla presionada.
    QTimer* timer;            ///< Temporizador que controla la frecuencia del movimiento.

    // Animación
    QPixmap spriteSheet;      ///< Imagen que contiene todos los sprites de animación.
    int currentFrame;         ///< Índice del frame actual de animación (de 0 a 2).
    int frameBase;            ///< Índice base de la dirección (0 = arriba, 3 = abajo, 6 = izq, 9 = der).
    int frameSize;            ///< Tamaño de cada frame individual (px), normalmente 30x30.
};

#endif // PACMAN_H
