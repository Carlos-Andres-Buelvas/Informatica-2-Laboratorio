#include "pacman.h"
#include "punto.h"
#include "pared.h"
#include "game.h"
#include <QList>
#include <typeinfo>
#include <QGraphicsScene>
#include <QDebug>

/**
 * @brief Constructor de la clase Pacman.
 *
 * Inicializa posiciones, carga el sprite, configura la animación
 * y activa el temporizador de movimiento periódico.
 */
Pacman::Pacman()
    : dx(0), dy(0),
    deseadoDx(0), deseadoDy(0),
    currentFrame(0), frameBase(9), frameSize(30) {

    spriteSheet.load("pacman.png");  ///< Hoja de sprites completa (12 frames)
    setPixmap(spriteSheet.copy(frameBase * frameSize, 0, frameSize, frameSize));

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Pacman::mover);
    timer->start(150);  ///< Mueve cada 150 ms
}

/**
 * @brief Captura las teclas presionadas para establecer la dirección deseada.
 *
 * Las teclas válidas son:
 * - D: derecha
 * - A: izquierda
 * - S: abajo
 * - Z: arriba
 *
 * También actualiza el frame base de la animación según la dirección.
 *
 * @param event Evento de teclado capturado.
 */
void Pacman::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_D:
        deseadoDx = 30; deseadoDy = 0;
        frameBase = 9;
        break;
    case Qt::Key_A:
        deseadoDx = -30; deseadoDy = 0;
        frameBase = 6;
        break;
    case Qt::Key_S:
        deseadoDx = 0; deseadoDy = 30;
        frameBase = 3;
        break;
    case Qt::Key_Z:
        deseadoDx = 0; deseadoDy = -30;
        frameBase = 0;
        break;
    }
}

/**
 * @brief Método principal de lógica y animación llamado por el temporizador.
 *
 * Ejecuta en orden:
 * 1. Intento de cambiar dirección si no hay colisión
 * 2. Movimiento en dirección actual
 * 3. Detección de colisiones con paredes
 * 4. Consumo de puntos
 * 5. Verificación de victoria (sin puntos)
 * 6. Animación de sprite
 * 7. Teletransporte lateral (borde izquierdo y derecho)
 */
void Pacman::mover() {
    // --- 1. Intentar cambiar de dirección (simulada) ---
    int intentoX = x() + deseadoDx;
    int intentoY = y() + deseadoDy;

    setPos(intentoX, intentoY);
    QList<QGraphicsItem*> colisionesDeseadas = collidingItems();
    setPos(x() - deseadoDx, y() - deseadoDy);  // volver a posición original

    bool colisionaDeseado = false;
    for (QGraphicsItem* item : colisionesDeseadas) {
        if (typeid(*item) == typeid(Pared)) {
            colisionaDeseado = true;
            break;
        }
    }

    if (!colisionaDeseado) {
        dx = deseadoDx;
        dy = deseadoDy;
    }

    // --- 2. Mover en la dirección actual ---
    int nuevoX = x() + dx;
    int nuevoY = y() + dy;
    setPos(nuevoX, nuevoY);

    QList<QGraphicsItem*> colisiones = collidingItems();
    bool colisionaPared = false;
    for (QGraphicsItem* item : colisiones) {
        if (typeid(*item) == typeid(Pared)) {
            colisionaPared = true;
            break;
        }
    }

    if (colisionaPared) {
        setPos(x() - dx, y() - dy);
        return;
    }

    // --- 3. Comer puntos ---
    for (QGraphicsItem* item : colisiones) {
        if (typeid(*item) == typeid(Punto)) {
            scene()->removeItem(item);
            delete item;

            // Aumentar puntaje si es posible
            Game* juego = dynamic_cast<Game*>(scene()->views().first());
            if (juego) {
                juego->aumentarPuntaje(10);
            }
        }
    }

    // --- 4. Verificar si quedan puntos (condición de victoria) ---
    QList<QGraphicsItem*> items = scene()->items();
    bool quedanPuntos = false;

    for (QGraphicsItem* item : items) {
        if (typeid(*item) == typeid(Punto)) {
            quedanPuntos = true;
            break;
        }
    }

    if (!quedanPuntos) {
        // Mostrar mensaje de victoria
        QGraphicsTextItem* victoria = new QGraphicsTextItem("You win!");
        victoria->setDefaultTextColor(Qt::green);
        victoria->setFont(QFont("Arial", 32, QFont::Bold));
        victoria->setPos(scene()->width() / 2 - 100, scene()->height() / 2 - 50);
        victoria->setZValue(2);
        scene()->addItem(victoria);

        // Detener movimiento
        timer->stop();
    }

    // --- 5. Animación de sprite ---
    currentFrame = (currentFrame + 1) % 3;
    int frameX = (frameBase + currentFrame) * frameSize;
    setPixmap(spriteSheet.copy(frameX, 0, frameSize, frameSize));

    // --- 6. Teletransporte lateral clásico ---
    QRectF limites = scene()->sceneRect();
    int escenaAncho = static_cast<int>(limites.width());

    if (x() < -frameSize) {
        setX(escenaAncho);
    } else if (x() > escenaAncho) {
        setX(-frameSize);
    }
}
