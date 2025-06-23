
#ifndef AHORCADO_H
#define AHORCADO_H

#include "Juego.h"
#include <vector>

class Ahorcado : public Juego {
private:
    string palabraSecreta;
    string palabraAdivinada;
    int intentosFallidos;
    int maxIntentos;
    char* letrasUsadas; // Puntero dinamico
    int numLetrasUsadas;
    bool modoJuego; // true = vs CPU, false = vs Jugador

    void cargarPalabras();
    void generarPalabraAleatoria();
    bool letraYaUsada(char letra);
    void agregarLetraUsada(char letra);
    void dibujarAhorcado();

public:
    // Constructor
    Ahorcado(string nombre, bool modo);

    // Destructor
    ~Ahorcado();

    void iniciarJuego() override;
    void jugar() override;
    bool verificarFinJuego() override;
    void mostrarResultado() override;
    void guardarPartida() override;

    void establecerPalabra(string palabra);
    void mostrarEstado();
    bool procesarLetra(char letra);
};

#endif