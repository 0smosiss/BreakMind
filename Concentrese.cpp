#include "Concentrese.h"
#include <fstream>

// Constructor
Concentrese::Concentrese(string nombre) : Juego(nombre) {
    filas = 4;
    columnas = 4;
    parejas = (filas * columnas) / 2;
    parejasEncontradas = 0;
    intentos = 0;

    crearTablero();
}

// Destructor
Concentrese::~Concentrese() {
    liberarMemoria();
}

void Concentrese::iniciarJuego() {
    cout << R"(
===============================================================
|                                                             |
|     ____                       _                            |
|    / ___| ___  _ __   ___ ___ | |_ _ __ ___  ___  ___       |
|   | |   / _ \| '_ \ / __/ _ \| __| '__/ _ \/ __|/ _ \       |
|   | |__| (_) | | | | (_|  __/| |_| | |  __/\__ \  __/       |
|    \____\___/|_| |_|\___\___| \__|_|  \___||___/\___|       |
|                                                             |
|             JUEGO DE MEMORIA Y CONCENTRACION                |
|                                                             |
===============================================================
)" << endl;

    cout << R"(
+-------------------------------------------------------------+
|  JUGADOR: )" << nombreJugador << R"(                        
|  TABLERO: )" << filas << "x" << columnas << R"( ()" << parejas << R"( parejas)      
|  OBJETIVO: Encuentra todas las parejas!                     
+-------------------------------------------------------------+
)" << endl;

    cout << R"(


+======================== INSTRUCCIONES ======================+
|  * Selecciona dos cartas por turno                          |
|  * Si coinciden, permanecen descubiertas                    |
|  * Si no coinciden, se voltean nuevamente                   |
|  * Gana cuando encuentres todas las parejas!                |
+=============================================================+
)" << endl;


    llenarTablero();
    mezclarTablero();

    cout << R"(
===============================================================
                      TABLERO INICIAL                        
===============================================================
)" << endl;

    mostrarTablero();
}





void Concentrese::jugar() {
    int pos1, pos2;

    while (!verificarFinJuego()) {
        cout << "\n--- Turno " << (intentos + 1) << " ---" << endl;
        cout << "Parejas encontradas: " << parejasEncontradas << "/" << parejas << endl;

        mostrarTablero();

        // Pedir primera posicion
        cout << "\nSelecciona la primera posicion (1-" << filas * columnas << "): ";
        cin >> pos1;

        if (pos1 < 1 || pos1 > filas * columnas) {
            cout << "Posicion invalida!" << endl;
            continue;
        }

        // Verificar si ya esta revelada
        int fila1, col1;
        convertirPosicion(pos1, fila1, col1);
        if (revelado[fila1][col1]) {
            cout << "Esa posicion ya esta revelada!" << endl;
            continue;
        }

        // Mostrar primera carta
        revelado[fila1][col1] = true;
        mostrarTablero();
        cout << "Primera carta: " << tablero[fila1][col1] << endl;

        // Pedir segunda posicion
        cout << "Selecciona la segunda posicion (1-" << filas * columnas << "): ";
        cin >> pos2;

        if (pos2 < 1 || pos2 > filas * columnas || pos2 == pos1) {
            cout << "Posición invalida!" << endl;
            revelado[fila1][col1] = false; // Ocultar primera carta
            continue;
        }

        // Verificar si ya esta revelada
        int fila2, col2;
        convertirPosicion(pos2, fila2, col2);
        if (revelado[fila2][col2]) {
            cout << "Esa posicion ya esta revelada!" << endl;
            revelado[fila1][col1] = false; // Ocultar primera carta
            continue;
        }

        // Mostrar segunda carta
        revelado[fila2][col2] = true;
        mostrarTablero();
        cout << "Segunda carta: " << tablero[fila2][col2] << endl;

        // Verificar si son pareja
        if (tablero[fila1][col1] == tablero[fila2][col2]) {
            cout << "¡PAREJA ENCONTRADA!" << endl;
            parejasEncontradas++;
        }
        else {
            cout << "No son pareja..." << endl;
            // Ocultar ambas cartas despues de un momento
            cout << "Presiona Enter para continuar...";
            cin.ignore();
            cin.get();
            revelado[fila1][col1] = false;
            revelado[fila2][col2] = false;
        }

        intentos++;
    }

    mostrarResultado();
}

bool Concentrese::verificarFinJuego() {
    if (parejasEncontradas == parejas) {
        juegoGanado = true;
        // Puntuacion basada en eficiencia (menos intentos = mas puntos)
        puntuacion = (parejas * 20) - (intentos * 2);
        if (puntuacion < 0) puntuacion = 10; // Puntuacion minima
        return true;
    }
    return false;
}

void Concentrese::mostrarResultado() {
    cout << "\n=== FIN DEL JUEGO ===" << endl;

    if (juegoGanado) {
        cout << "¡FELICIDADES! Encontraste todas las parejas!" << endl;
        cout << "Intentos realizados: " << intentos << endl;
        cout << "Puntuación: " << puntuacion << " puntos" << endl;
    }

    cout << "\nTablero completo:" << endl;
    mostrarTableroCompleto();
}

void Concentrese::guardarPartida() {
    ofstream archivo("historial.txt", ios::app);
    if (archivo.is_open()) {
        // usamos esta funcion usada comunmente para sacar la fecha local del pc 
        
        // Obtenemos el tiempo actual del sistema
        time_t t = time(nullptr);

        // Creamos una estructura para almacenar la fecha/hora local
        tm local = {};

        // Convertimos el tiempo UTC a tiempo local de forma segura
        localtime_s(&local, &t);

        // Buffer para almacenar la fecha formateada como string
        char fecha[11];

        // Formatear la fecha como "YYYY-MM-DD" (ejemplo: "2024-12-22")
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", &local);

        archivo << fecha << "" << nombreJugador << " MEM ";
        archivo << (juegoGanado ? "G" : "P") << " ";
        archivo << puntuacion << endl;
        archivo.close();
    }
}

void Concentrese::crearTablero() {
    // Crear matriz dinamica para el tablero
    tablero = new char* [filas];
    revelado = new bool* [filas];

    for (int i = 0; i < filas; i++) {
        tablero[i] = new char[columnas];
        revelado[i] = new bool[columnas];

        // Inicializar matrices
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = ' ';
            revelado[i][j] = false;
        }
    }
}

void Concentrese::llenarTablero() {
    char simbolos[] = { '@', '$', '%', '&', '?', '#', 'A', 'B' };
    int simboloActual = 0;
    int contador = 0;

    // Llenar el tablero con parejas
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = simbolos[simboloActual];
            contador++;

            // Cada simbolo aparece dos veces (pareja)
            if (contador % 2 == 0) {
                simboloActual++;
            }
        }
    }
}

void Concentrese::mezclarTablero() {
    // Mezcla simple intercambiando posiciones
    for (int i = 0; i < filas * columnas; i++) {
        int fila1 = i / columnas;
        int col1 = i % columnas;

        int pos2 = (i * 7 + 3) % (filas * columnas); // Formula simple de mezcla
        int fila2 = pos2 / columnas;
        int col2 = pos2 % columnas;

        // Intercambiar
        char temp = tablero[fila1][col1];
        tablero[fila1][col1] = tablero[fila2][col2];
        tablero[fila2][col2] = temp;
    }
}

void Concentrese::liberarMemoria() {
    for (int i = 0; i < filas; i++) {
        delete[] tablero[i];
        delete[] revelado[i];
    }
    delete[] tablero;
    delete[] revelado;
}

void Concentrese::mostrarTablero() {
    cout << "\n   ";
    for (int j = 0; j < columnas; j++) {
        cout << "  " << (j + 1) << " ";
    }
    cout << endl;

    for (int i = 0; i < filas; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < columnas; j++) {
            cout << "[ ";
            if (revelado[i][j]) {
                cout << tablero[i][j];
            }
            else {
                cout << " ";
            }
            cout << " ]";
        }
        cout << endl;
    }

    cout << "\nPosiciones numeradas:" << endl;
    cout << "   ";
    for (int j = 0; j < columnas; j++) {
        cout << "  " << (j + 1) << " ";
    }
    cout << endl;

    for (int i = 0; i < filas; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < columnas; j++) {
            int pos = i * columnas + j + 1;
            if (pos < 10) {
                cout << "[ " << pos << " ]";
            }
            else {
                cout << "[" << pos << " ]";
            }
        }
        cout << endl;
    }
}

void Concentrese::mostrarTableroCompleto() {
    cout << "\n   ";
    for (int j = 0; j < columnas; j++) {
        cout << "  " << (j + 1) << " ";
    }
    cout << endl;

    for (int i = 0; i < filas; i++) {
        cout << (i + 1) << "  ";
        for (int j = 0; j < columnas; j++) {
            cout << "[ " << tablero[i][j] << " ]";
        }
        cout << endl;
    }
}

void Concentrese::convertirPosicion(int pos, int& fila, int& col) {
    pos--; // Convertir de 1-indexado a 0-indexado
    fila = pos / columnas;
    col = pos % columnas;
}

int Concentrese::getFilas() {
    return filas;
}

int Concentrese::getColumnas() {
    return columnas;
}