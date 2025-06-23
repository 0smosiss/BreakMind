#ifndef MENU_H
#define MENU_H

#include "Juego.h"
#include "Ahorcado.h"
#include "Concentrese.h"

class Menu {
private:
    Juego* juegoActual; // Puntero para polimorfismo

    // Metodos privados
    void mostrarMenuPrincipal();
    void mostrarMenuAhorcado();
    void mostrarHistorial();
    void limpiarPantalla();

public:
    Menu();

    ~Menu();

    // Metodo principal
    void ejecutar();

    // Metodos de gestion
    void crearJuegoAhorcado(string nombreJugador, bool modo);
    void crearJuegoConcentrese(string nombreJugador);
    void eliminarJuegoActual();
};

#endif