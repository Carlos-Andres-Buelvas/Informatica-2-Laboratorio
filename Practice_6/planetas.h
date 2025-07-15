#ifndef PLANETAS_H
#define PLANETAS_H

#include <cmath>
#include <QLabel>

/// Coordenadas límites del área de movimiento (por ejemplo, en la interfaz gráfica)
#define mw_xo 200  ///< Límite izquierdo
#define mw_x1 950  ///< Límite derecho
#define mw_yo 0    ///< Límite superior
#define mw_y1 600  ///< Límite inferior

/**
 * @class planetas
 * @brief Representa un planeta con posición, velocidad y masa.
 *
 * Esta clase encapsula los atributos físicos de un planeta y permite
 * calcular su posición sobre un plano 2D, así como obtener y modificar
 * sus propiedades.
 */
class planetas
{
private:
    float xo;   ///< Posición inicial en X
    float yo;   ///< Posición inicial en Y
    float vxo;  ///< Velocidad inicial en X
    float vyo;  ///< Velocidad inicial en Y
    float m;    ///< Masa del planeta

public:
    /**
     * @brief Constructor del planeta.
     * @param _xo Posición inicial en X.
     * @param _yo Posición inicial en Y.
     * @param _vxo Velocidad inicial en X.
     * @param _vyo Velocidad inicial en Y.
     * @param _m Masa del planeta.
     */
    planetas(float _xo, float _yo, float _vxo, float _vyo, float _m);

    /**
     * @brief Calcula la coordenada actual en X.
     * @return Coordenada en X como entero.
     */
    int calculate_X_coordinate();

    /**
     * @brief Calcula la coordenada actual en Y.
     * @return Coordenada en Y como entero.
     */
    int calculate_Y_coordinate();

    /**
     * @brief Obtiene la posición en X.
     * @return Valor de xo.
     */
    float getXo() const;

    /**
     * @brief Establece la posición en X.
     * @param newXo Nuevo valor para xo.
     */
    void setXo(float newXo);

    /**
     * @brief Obtiene la posición en Y.
     * @return Valor de yo.
     */
    float getYo() const;

    /**
     * @brief Establece la posición en Y.
     * @param newYo Nuevo valor para yo.
     */
    void setYo(float newYo);

    /**
     * @brief Obtiene la velocidad en X.
     * @return Valor de vxo.
     */
    float getVxo() const;

    /**
     * @brief Establece la velocidad en X.
     * @param newVxo Nuevo valor para vxo.
     */
    void setVxo(float newVxo);

    /**
     * @brief Obtiene la velocidad en Y.
     * @return Valor de vyo.
     */
    float getVyo() const;

    /**
     * @brief Establece la velocidad en Y.
     * @param newVyo Nuevo valor para vyo.
     */
    void setVyo(float newVyo);

    /**
     * @brief Obtiene la masa del planeta.
     * @return Valor de m.
     */
    float getM() const;
};

#endif // PLANETAS_H
