#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "pacman.h"

/**
 * @brief La clase Game representa el entorno principal del juego tipo Pacman.
 *
 * Hereda de QGraphicsView y contiene la escena gráfica, el jugador (Pacman),
 * el sistema de puntaje, y la lógica de carga del mapa.
 */
class Game : public QGraphicsView {
    Q_OBJECT

protected:
    /**
     * @brief Reimplementación del evento de redimensionamiento de la ventana.
     *
     * Permite ajustar automáticamente la vista cuando el usuario redimensiona
     * la ventana del juego.
     *
     * @param event Evento de redimensionamiento.
     */
    void resizeEvent(QResizeEvent *event) override;

public:
    /**
     * @brief Constructor de la clase Game.
     *
     * Inicializa la escena, carga el mapa, configura el entorno gráfico,
     * y muestra el puntaje inicial.
     *
     * @param parent Puntero al widget padre (opcional).
     */
    Game(QWidget* parent = nullptr);

    /**
     * @brief Aumenta el puntaje del jugador y actualiza el texto en pantalla.
     *
     * @param puntos Cantidad de puntos a añadir al puntaje actual.
     */
    void aumentarPuntaje(int puntos);

    /**
     * @brief Obtiene el puntaje actual del jugador.
     *
     * @return Puntaje actual (entero).
     */
    int getPuntaje() const;

private:
    QGraphicsScene* scene;           ///< Escena gráfica donde se ubican los objetos.
    Pacman* pacman;                  ///< Puntero al personaje principal.
    int puntaje;                     ///< Puntaje actual del jugador.
    QGraphicsTextItem* textoPuntaje; ///< Texto gráfico que muestra el puntaje en pantalla.

    /**
     * @brief Carga el mapa del juego desde un archivo de texto.
     *
     * El archivo debe contener caracteres específicos:
     * '#' = pared, '.' = punto, 'P' = Pacman.
     *
     * @param nombreArchivo Ruta del archivo que contiene el mapa.
     */
    void cargarMapa(const QString& nombreArchivo);
};

#endif // GAME_H
