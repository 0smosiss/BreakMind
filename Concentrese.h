#ifndef CONCENTRESE_H
#define CONCENTRESE_H

#include "Juego.h"

class Concentrese : public Juego {
private:
    char** tablero; // Puntero doble para matriz dinamica
    bool** revelado; // Matriz de posiciones reveladas
    int filas;
    int columnas;
    int parejas;
    int parejasEncontradas;
    int intentos;

    // Métodos privados
    void crearTablero();
    void llenarTablero();
    void mezclarTablero();
    void liberarMemoria();
    bool sonPareja(int pos1, int pos2);
    void convertirPosicion(int pos, int& fila, int& col);

public:
    Concentrese(string nombre);

    ~Concentrese();

    void iniciarJuego() override;
    void jugar() override;
    bool verificarFinJuego() override;
    void mostrarResultado() override;
    void guardarPartida() override;

    void mostrarTablero();
    void mostrarTableroCompleto();
    bool revelarPosicion(int posicion);
    int getFilas();
    int getColumnas();
};

#endif