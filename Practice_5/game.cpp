#include "game.h"
#include "punto.h"
#include "pared.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

/**
 * @brief Constructor de la clase Game.
 *
 * Inicializa la escena, ajusta el tamaño del tablero,
 * establece el color de fondo, crea el texto del puntaje,
 * carga el mapa desde archivo y enfoca a Pacman.
 *
 * @param parent Widget padre (por defecto nullptr).
 */
Game::Game(QWidget* parent) : QGraphicsView(parent), puntaje(0) {
    const int tileSize = 30;
    const int columnas = 28;
    const int filas = 31;

    // Crear y configurar la escena
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, columnas * tileSize, filas * tileSize);
    setScene(scene);
    setBackgroundBrush(QBrush(Qt::black));

    // Crear texto de puntaje
    textoPuntaje = new QGraphicsTextItem();
    textoPuntaje->setPlainText("Score: 0");
    textoPuntaje->setDefaultTextColor(Qt::yellow);
    textoPuntaje->setFont(QFont("Consolas", 20, QFont::Bold));
    textoPuntaje->setZValue(1);  // Asegura visibilidad
    textoPuntaje->setPos(10, scene->height() - 35);  // Esquina inferior izquierda
    scene->addItem(textoPuntaje);

    // Cargar mapa desde archivo
    cargarMapa("mapa.txt");

    // Configurar control de teclado
    if (pacman) {
        pacman->setFlag(QGraphicsItem::ItemIsFocusable);
        pacman->setFocus();
    }

    // Ajuste de vista automática
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

/**
 * @brief Carga el mapa desde un archivo de texto.
 *
 * Interpreta caracteres del archivo y genera objetos del juego:
 * '#' → pared, '.' → punto, 'P' → Pacman.
 *
 * @param nombreArchivo Nombre del archivo del mapa.
 */
void Game::cargarMapa(const QString& nombreArchivo) {
    QFile file(nombreArchivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo del mapa";
        return;
    }

    QTextStream in(&file);
    int fila = 0;
    const int tileSize = 30;

    while (!in.atEnd()) {
        QString linea = in.readLine();
        for (int col = 0; col < linea.length(); ++col) {
            QChar ch = linea[col];
            int x = col * tileSize;
            int y = fila * tileSize;

            if (ch == '#') {
                auto* pared = new Pared();
                pared->setPos(x, y);
                scene->addItem(pared);
            } else if (ch == '.') {
                auto* punto = new Punto();
                punto->setPos(x + 10, y + 10);  // centrado en celda de 30x30
                scene->addItem(punto);
            } else if (ch == 'P') {
                pacman = new Pacman();
                pacman->setPos(x, y);
                scene->addItem(pacman);
            }
        }
        fila++;
    }
}

/**
 * @brief Se ejecuta automáticamente al redimensionar la ventana.
 *
 * Reajusta la vista para que siempre se vea completa la escena.
 *
 * @param event Evento de redimensionamiento.
 */
void Game::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

/**
 * @brief Aumenta el puntaje actual del jugador.
 *
 * También actualiza el texto en pantalla con el nuevo valor.
 *
 * @param puntos Cantidad de puntos a sumar al puntaje actual.
 */
void Game::aumentarPuntaje(int puntos) {
    puntaje += puntos;
    textoPuntaje->setPlainText("Puntaje: " + QString::number(puntaje));
}
