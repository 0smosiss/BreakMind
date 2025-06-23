#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <string>
using namespace std;

// Clase abstracta base para ambos juegos
class Juego {
protected:
    string nombreJugador;
    int puntuacion;
    bool juegoGanado;

public:
    // Constructor
    Juego(string nombre);

    // Destructor virtual
    virtual ~Juego();

    // Métodos virtuales puros (abstractos)
    virtual void iniciarJuego() = 0;
    virtual void jugar() = 0;
    virtual bool verificarFinJuego() = 0;
    virtual void mostrarResultado() = 0;

    // Metodos virtuales que pueden ser sobrescritos
    virtual void guardarPartida();

    // Metodos públicos
    string getNombreJugador();
    int getPuntuacion();
    bool getJuegoGanado();
    void setPuntuacion(int puntos);
    void setJuegoGanado(bool ganado);
};

#endif