#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

/**
 * @brief Constructor de la clase MainWindow.
 *
 * Inicializa la interfaz gráfica y conecta señales a sus respectivos slots.
 * @param parent Puntero al widget padre.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    time = new QTimer;
    ui->Btn_stop->setEnabled(false);

    connect(ui->Siguiente, SIGNAL(clicked(bool)), this, SLOT(nuevo_planeta()));
    connect(ui->Btn_inicio, SIGNAL(clicked(bool)), this, SLOT(inicial_simulation()));
    connect(time, SIGNAL(timeout()), this, SLOT(simulation_step()));
    connect(ui->Btn_stop, SIGNAL(clicked(bool)), this, SLOT(stop_simulation()));
}

/**
 * @brief Destructor de MainWindow.
 *
 * Libera memoria asociada a la interfaz, el temporizador y las etiquetas.
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete time;
    for (int i = 0; i < labels.length(); i++) delete labels[i];
}

/**
 * @brief Aplica ecuaciones de cinemática al planeta con índice i.
 *
 * Se actualizan posición y velocidad del planeta usando aceleraciones dadas.
 *
 * @param akx Aceleración en X.
 * @param aky Aceleración en Y.
 * @param i Índice del planeta.
 */
void MainWindow::sineticas(float akx, float aky, int i)
{
    astros[i].setVxo((astros[i].getVxo() + akx));
    astros[i].setVyo((astros[i].getVyo() + aky));
    astros[i].setXo(astros[i].getXo() + astros[i].getVxo());
    astros[i].setYo(astros[i].getYo() + astros[i].getVyo());
}

/**
 * @brief Crea un nuevo planeta con datos introducidos por el usuario.
 *
 * El planeta se añade al vector de astros, junto con una etiqueta gráfica.
 */
void MainWindow::nuevo_planeta()
{
    float x, y, vx, vy, m;
    x = ui->Num_Xo->value();
    y = ui->Num_Yo->value();
    vx = ui->Num_Vxo->value();
    vy = ui->Num_Vyo->value();
    m = ui->Num_M->value();

    astros.push_back(planetas(x, y, vx, vy, m));
    astros.shrink_to_fit();
    labels.push_back(new QLabel("Planeta", this));
    labels.last()->setVisible(true);
    labels.shrink_to_fit();

    // Reiniciar los campos del formulario
    ui->Num_Xo->setValue(0.0);
    ui->Num_Yo->setValue(0.0);
    ui->Num_Vxo->setValue(0.0);
    ui->Num_Vyo->setValue(0.0);
    ui->Num_M->setValue(0.0);
}

/**
 * @brief Inicializa la simulación desde cero.
 *
 * Limpia archivos previos, reinicia el tiempo y configura la UI.
 */
void MainWindow::inicial_simulation()
{
    tiempoSimulacion = 0.0;

    // Limpiar archivos de datos anteriores
    for (int i = 0; i < astros.size(); ++i) {
        QString nombreArchivo = QString("planeta_%1.txt").arg(i);
        QFile archivo(nombreArchivo);
        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            archivo.close();
        }
    }

    time->start(1000 * 0.001); // 1 ms por paso de simulación
    ui->Btn_stop->setEnabled(true);
    ui->Siguiente->setEnabled(false);
    ui->Btn_inicio->setEnabled(false);
}

/**
 * @brief Ejecuta un paso de la simulación física.
 *
 * Calcula fuerzas gravitatorias entre planetas, actualiza posiciones y
 * guarda los datos en archivos individuales por planeta.
 */
void MainWindow::simulation_step()
{
    int x, y;
    float akx = 0.0;
    float aky = 0.0;
    double norma = 0.0;

    for (int i = 0; i < astros.length(); i++) {
        for (int j = 0; j < astros.length(); j++) {
            if (i != j) {
                norma = std::sqrt(std::pow((astros[j].getXo() - astros[i].getXo()), 2) +
                                  std::pow((astros[j].getYo() - astros[i].getYo()), 2));
                akx += ((astros[j].getM() / std::pow(norma, 3)) * (astros[j].getXo() - astros[i].getXo()));
                aky += ((astros[j].getM() / std::pow(norma, 3)) * (astros[j].getYo() - astros[i].getYo()));
            }
        }
        sineticas(akx, aky, i);
        akx = 0.0;
        aky = 0.0;
    }

    for (int i = 0; i < astros.length(); i++) {
        x = astros[i].calculate_X_coordinate();
        y = astros[i].calculate_Y_coordinate();
        labels[i]->setGeometry(x, y, 35, 10);
    }

    guardarDatosPlanetas();
}

/**
 * @brief Detiene la simulación actual.
 *
 * También reactiva botones de control para reiniciar o añadir planetas.
 */
void MainWindow::stop_simulation()
{
    time->stop();
    ui->Btn_stop->setEnabled(false);
    ui->Siguiente->setEnabled(true);
    ui->Btn_inicio->setEnabled(true);
}

/**
 * @brief Guarda el estado actual de todos los planetas en archivos `.txt`.
 *
 * Se crea un archivo por planeta, incluyendo:
 * tiempo, posición (X,Y), velocidad (Vx,Vy), y masa.
 */
void MainWindow::guardarDatosPlanetas()
{
    for (int i = 0; i < astros.size(); ++i) {
        QString nombreArchivo = QString("planeta_%1.txt").arg(i);
        QFile archivo(nombreArchivo);

        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            continue;
        }

        QTextStream salida(&archivo);
        salida.setRealNumberPrecision(6);
        salida.setRealNumberNotation(QTextStream::FixedNotation);

        salida << QString("%1\t%2\t%3\t%4\t%5\t%6\n")
                      .arg(tiempoSimulacion, 0, 'f', 6)
                      .arg(astros[i].getXo(), 0, 'f', 6)
                      .arg(astros[i].getYo(), 0, 'f', 6)
                      .arg(astros[i].getVxo(), 0, 'f', 6)
                      .arg(astros[i].getVyo(), 0, 'f', 6)
                      .arg(astros[i].getM(), 0, 'f', 6);

        archivo.close();
    }

    // Aumentar tiempo según el paso de integración (ajustable)
    tiempoSimulacion += 0.032;
}
