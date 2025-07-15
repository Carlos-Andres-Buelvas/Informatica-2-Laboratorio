#include "planetas.h"

/**
 * @brief Constructor de la clase planetas.
 *
 * Inicializa un objeto planeta con su posición, velocidad y masa.
 *
 * @param _xo Posición inicial en X.
 * @param _yo Posición inicial en Y.
 * @param _vxo Velocidad inicial en X.
 * @param _vyo Velocidad inicial en Y.
 * @param _m Masa del planeta.
 */
planetas::planetas(float _xo,float _yo,float _vxo,float _vyo,float _m)
{
    xo = _xo;
    yo = _yo;
    vxo = _vxo;
    vyo = _vyo;
    m = _m;
}

/**
 * @brief Obtiene la posición en X.
 * @return Valor actual de xo.
 */
float planetas::getXo() const
{
    return xo;
}

/**
 * @brief Establece una nueva posición en X.
 * @param newXo Nuevo valor para xo.
 */
void planetas::setXo(float newXo)
{
    xo = newXo;
}

/**
 * @brief Obtiene la posición en Y.
 * @return Valor actual de yo.
 */
float planetas::getYo() const
{
    return yo;
}

/**
 * @brief Establece una nueva posición en Y.
 * @param newYo Nuevo valor para yo.
 */
void planetas::setYo(float newYo)
{
    yo = newYo;
}

/**
 * @brief Obtiene la velocidad en X.
 * @return Valor actual de vxo.
 */
float planetas::getVxo() const
{
    return vxo;
}

/**
 * @brief Establece una nueva velocidad en X.
 * @param newVxo Nuevo valor para vxo.
 */
void planetas::setVxo(float newVxo)
{
    vxo = newVxo;
}

/**
 * @brief Obtiene la velocidad en Y.
 * @return Valor actual de vyo.
 */
float planetas::getVyo() const
{
    return vyo;
}

/**
 * @brief Establece una nueva velocidad en Y.
 * @param newVyo Nuevo valor para vyo.
 */
void planetas::setVyo(float newVyo)
{
    vyo = newVyo;
}

/**
 * @brief Obtiene la masa del planeta.
 * @return Valor actual de la masa m.
 */
float planetas::getM() const
{
    return m;
}

/**
 * @brief Calcula la coordenada X para graficar el planeta en pantalla.
 *
 * Transforma la posición física xo a coordenadas de la interfaz (QGraphicsScene).
 *
 * @return Coordenada X en píxeles.
 */
int planetas::calculate_X_coordinate()
{
    float m = (mw_x1 - mw_xo) / 12000.0;
    return m * (xo + 6000) + mw_xo;
}

/**
 * @brief Calcula la coordenada Y para graficar el planeta en pantalla.
 *
 * Transforma la posición física yo a coordenadas de la interfaz (QGraphicsScene).
 *
 * @return Coordenada Y en píxeles.
 */
int planetas::calculate_Y_coordinate()
{
    float m = (mw_y1 - mw_yo) / -14000.0;
    return m * (yo - 6000) + mw_yo;
}
