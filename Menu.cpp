#include "Menu.h"
#include <fstream>

Menu::Menu() {
    juegoActual = nullptr;
}

Menu::~Menu() {
    eliminarJuegoActual();
}

void Menu::ejecutar() {
    int opcion;

    do {
        mostrarMenuPrincipal();
        cout << R"( 
   _________________________
   Selecciona una opcion: )";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre;
            cout << R"(
   _____________________
   Ingresa tu nombre:)";
            cin >> nombre;


            mostrarMenuAhorcado();
            int modoAhorcado;
            cout << "Selecciona el modo: ";
            cin >> modoAhorcado;

            bool modo = (modoAhorcado == 1); // true = vs CPU, false = vs Jugador
            crearJuegoAhorcado(nombre, modo);

            juegoActual->iniciarJuego();
            juegoActual->jugar();
            juegoActual->guardarPartida();

            eliminarJuegoActual();
            break;
        }
        case 2: {
            string nombre;
            cout << R"(
   _________________________
   Ingresa tu nombre:)";
            cin >> nombre;

            crearJuegoConcentrese(nombre);

            juegoActual->iniciarJuego();
            juegoActual->jugar();
            juegoActual->guardarPartida();

            eliminarJuegoActual();
            break;
        }
        case 3:
            mostrarHistorial();
            break;
        case 4:
            cout << "¡Gracias por jugar!" << endl;
            break;
        default:
            cout << "Opcion invalida. Intenta de nuevo." << endl;
        }

        if (opcion != 4) {
            cout << "\nPresiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }

    } while (opcion != 4);
}

void Menu::mostrarMenuPrincipal() {
    limpiarPantalla();
    cout << R"(
  +============================================================+                    
  |                                                            |
  |    ____                 _      __  __ _           _        |
  |   | __ ) _ __ ___  __ _| | __ |  \/  (_)_ __   __| |       |
  |   |  _ \| '__/ _ \/ _` | |/ / | |\/| | | '_ \ / _` |       |
  |   | |_) | | |  __/ (_| |   <  | |  | | | | | | (_| |       |
  |   |____/|_|  \___|\__,_|_|\_\ |_|  |_|_|_| |_|\__,_|       |
  |                                                            |
  |                                                            |
  |                      -= 0smosis =-                         |
  |                                                            |
  +============================================================+
  |                                                            |
  |                    1. JUGAR AHORCADO                       |
  |    +-----------------------------------------------+       |
  |    |      +-----+    Adivina la palabra            |       |
  |    |      |     |    secreta antes de que          |       |
  |    |      |     O    se complete el dibujo         |       |
  |    |      |    /|\                                 |       |
  |    |      |    / \                                 |       |
  |    +-----------------------------------------------+       |
  |                                                            |
  |                    2. JUGAR CONCENTRESE                    |
  |    +-----------------------------------------------+       |
  |    |   [?] [?] [?] [?]                             |       |
  |    |   [?] [?] [?] [?]   Encuentra las parejas     |       |
  |    |   [?] [?] [?] [?]   de cartas usando          |       |
  |    |   [?] [?] [?] [?]   tu memoria!               |       |
  |    +-----------------------------------------------+       |
  |                                                            |
  |                     3. VER HISTORIAL                       |
  |    +-----------------------------------------------+       |
  |    |   * Estadisticas de partidas                  |       |
  |    |   * Mejores puntajes                          |       |
  |    |   * Historial completo                        |       |
  |    +-----------------------------------------------+       |
  |                                                            |
  |                        4. SALIR                            |
  |    +-----------------------------------------------+       |
  |    |   Gracias por jugar!                          |       |
  |    |   Vuelve pronto...                            |       |
  |    +-----------------------------------------------+       |
  |                                                            |
  +============================================================+)" << endl;
}

void Menu::mostrarMenuAhorcado() {
    cout << R"( 
  +=============================================+
  |                                             |
  |          1. JUGADOR vs CPU                  |
  |   +---------------------------------------+ |
  |   |  +---+    VS    [CPU]                 | |
  |   |  |o_o|          /###\                 | |
  |   |  |___|         ( o.o )                | |
  |   |  Jugador      Palabras aleatorias     | |
  |   +---------------------------------------+ |
  |                                             |
  |         2. JUGADOR vs JUGADOR               |
  |   +---------------------------------------+ |
  |   |  +---+    VS    +---+                 | |
  |   |  |^_^|          |>_<|                 | |
  |   |  |___|          |___|                 | |
  |   |  Player 1      Player 2               | |
  |   +---------------------------------------+ |
  +=============================================+)"<<endl;
}

void Menu::mostrarHistorial() {
    cout << "\n=== HISTORIAL DE PARTIDAS ===" << endl;

    ifstream archivo("historial.txt");
    if (archivo.is_open()) {
        string linea;
        bool hayDatos = false;

        cout << "Fecha       Jugador    Juego  Resultado  Puntuacion" << endl;
        cout << "---------------------------------------------------" << endl;

        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                cout << linea << endl;
                hayDatos = true;
            }
        }

        if (!hayDatos) {
            cout << "No hay partidas guardadas." << endl;
        }

        archivo.close();
    }
    else {
        cout << "No se pudo abrir el archivo de historial." << endl;
    }
}

void Menu::limpiarPantalla() {
    for (int i = 0; i < 3; i++) {
        cout << endl;
    }
}

void Menu::crearJuegoAhorcado(string nombreJugador, bool modo) {
    eliminarJuegoActual();
    juegoActual = new Ahorcado(nombreJugador, modo);
}

void Menu::crearJuegoConcentrese(string nombreJugador) {
    eliminarJuegoActual();
    juegoActual = new Concentrese(nombreJugador);
}

void Menu::eliminarJuegoActual() {
    if (juegoActual != nullptr) {
        delete juegoActual;
        juegoActual = nullptr;
    }
}