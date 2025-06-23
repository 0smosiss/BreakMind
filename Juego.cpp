#include "Juego.h"
#include <fstream>
#include <format>

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

        time_t t = std::time(nullptr);
        tm local = {};
        localtime_s(&local, &t);

        char fecha[11];
        std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", &local);

//FUNCION COMUN PARA SACAR LA FECHA LOCAL DEL PC

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