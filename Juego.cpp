#define _CRT_SECURE_NO_WARNINGS
#include "Juego.h"
#include <fstream>

// Constructor
Juego::Juego(string nombre) {
    nombreJugador = nombre;
    puntuacion = 0;
    juegoGanado = false;
}

// Destructor
Juego::~Juego() {
 
}

// Metodo para guardar partida en archivo 
void Juego::guardarPartida() {
    ofstream archivo("historial.txt", ios::app);
    if (archivo.is_open()) {
        time_t t = time(nullptr);
        // FUNCION COMUN PARA SACAR LA FECHA LOCAL DEL PC
        struct tm* timeinfo = localtime(&t);
        char fecha[11];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", timeinfo);

        archivo << fecha << " " << nombreJugador << " ";
        archivo << (juegoGanado ? "G" : "P") << " ";
        archivo << puntuacion << endl;
        archivo.close();
    }
}

string Juego::getNombreJugador() {
    return nombreJugador;
}

int Juego::getPuntuacion() {
    return puntuacion;
}

bool Juego::getJuegoGanado() {
    return juegoGanado;
}

void Juego::setPuntuacion(int puntos) {
    puntuacion = puntos;
}

void Juego::setJuegoGanado(bool ganado) {
    juegoGanado = ganado;
}