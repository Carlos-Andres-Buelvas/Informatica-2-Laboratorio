#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <cmath>
#include "planetas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Ventana principal para la simulación de movimiento planetario.
 *
 * Esta clase controla la interfaz gráfica del usuario y coordina
 * la creación, simulación, y visualización del movimiento de planetas
 * en un espacio bidimensional.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor de MainWindow.
     * @param parent Widget padre (por defecto nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor de MainWindow.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;                  ///< Interfaz gráfica generada por Qt Designer.
    QTimer *time;                        ///< Temporizador para controlar los pasos de simulación.
    QVector<planetas> astros;           ///< Lista de planetas simulados.
    QVector<QLabel*> labels;            ///< Etiquetas gráficas para representar los planetas.

    /**
     * @brief Aplica cinemática al planeta con índice i.
     *
     * Ajusta la posición del planeta según los parámetros dados.
     *
     * @param akx Aceleración en X.
     * @param aky Aceleración en Y.
     * @param i Índice del planeta en el vector.
     */
    void sineticas(float akx, float aky, int i);

    /**
     * @brief Guarda los datos de los planetas actuales.
     *
     * Puede ser usado para respaldo o análisis de la simulación.
     */
    void guardarDatosPlanetas();

    double tiempoSimulacion = 0.0;  ///< Variable para rastrear el tiempo transcurrido en la simulación.

private slots:
    /**
     * @brief Crea un nuevo planeta y lo agrega a la simulación.
     */
    void nuevo_planeta();

    /**
     * @brief Ejecuta un paso de la simulación.
     *
     * Calcula nuevas posiciones y actualiza la visualización.
     */
    void simulation_step();

    /**
     * @brief Detiene la simulación en curso.
     */
    void stop_simulation();

    /**
     * @brief Inicializa la simulación.
     *
     * Limpia el entorno y establece condiciones iniciales.
     */
    void inicial_simulation();
};

#endif // MAINWINDOW_H
