#define _CRT_SECURE_NO_WARNINGS
#include "Ahorcado.h"
#include <fstream>

// Constructor
Ahorcado::Ahorcado(string nombre, bool modo) : Juego(nombre) {
    modoJuego = modo;
    intentosFallidos = 0;
    maxIntentos = 6;
    numLetrasUsadas = 0;
    letrasUsadas = new char[26]; // Array dinamico para letras

    // Inicializar array
    for (int i = 0; i < 26; i++) {
        letrasUsadas[i] = '\0';
    }
}

// Destructor
Ahorcado::~Ahorcado() {
    delete[] letrasUsadas; // Liberar memoria dinamica
}

void Ahorcado::iniciarJuego() {
    cout << "\n=== JUEGO DEL AHORCADO ===" << endl;
    cout << "Jugador: " << nombreJugador << endl;

    if (modoJuego) {
        
        cout << R"(
     _                       _                           ____ ____  _   _ 
    | |_   _  __ _  __ _  __| | ___  _ __  __   _____   / ___|  _ \| | | |
 _  | | | | |/ _` |/ _` |/ _` |/ _ \| '__| \ \ / / __| | |   | |_) | | | |
| |_| | |_| | (_| | (_| | (_| | (_) | |     \ V /\__ \ | |___|  __/| |_| |
 \___/ \__,_|\__, |\__,_|\__,_|\___/|_|      \_/ |___/  \____|_|    \___/ 
             |___/                                                        
    )" << endl;
        cargarPalabras();
    }
    else {
        cout << R"(     _                       _                        
    | |_   _  __ _  __ _  __| | ___  _ __  __   _____ 
 _  | | | | |/ _` |/ _` |/ _` |/ _ \| '__| \ \ / / __|
| |_| | |_| | (_| | (_| | (_| | (_) | |     \ V /\__ \
 \___/ \__,_|\__, |\__,_|\__,_|\___/|_|     _\_/ |___/
    | |_   _ |___/  __ _  __| | ___  _ __  |___ \     
 _  | | | | |/ _` |/ _` |/ _` |/ _ \| '__|   __) |    
| |_| | |_| | (_| | (_| | (_| | (_) | |     / __/     
 \___/ \__,_|\__, |\__,_|\__,_|\___/|_|    |_____|    
             |___/                                    )" << endl;
        string palabra;
        cout << "Jugador 2, ingresa la palabra secreta: ";
        cin >> palabra;

        // Limpiar pantalla (simulado)
        for (int i = 0; i < 20; i++) cout << endl;

        establecerPalabra(palabra);
    }

    // Inicializar palabra adivinada con guiones
    palabraAdivinada = "";
    for (int i = 0; i < palabraSecreta.length(); i++) {
        palabraAdivinada += "_";
    }

    cout << "Palabra a adivinar (" << palabraSecreta.length() << " letras)" << endl;
    cout << "Tienes " << maxIntentos << " intentos" << endl;
}

void Ahorcado::jugar() {
    char letra;

    while (!verificarFinJuego()) {
        mostrarEstado();

        cout << "\nIngresa una letra: ";
        cin >> letra;
        letra = tolower(letra);

        if (letraYaUsada(letra)) {
            cout << "Ya usaste esa letra!" << endl;
            continue;
        }

        agregarLetraUsada(letra);

        if (!procesarLetra(letra)) {
            intentosFallidos++;
            cout << "Letra incorrecta!" << endl;
        }
        else {
            cout << "Letra correcta!" << endl;
        }

        cout << endl;
    }

    mostrarResultado();
}

bool Ahorcado::verificarFinJuego() {
    // Verificar si gano (adivino toda la palabra)
    if (palabraAdivinada == palabraSecreta) {
        juegoGanado = true;
        puntuacion = (maxIntentos - intentosFallidos) * 10;
        return true;
    }

    // Verificar si perdio (agoto intentos)
    if (intentosFallidos >= maxIntentos) {
        juegoGanado = false;
        puntuacion = 0;
        return true;
    }

    return false;
}

void Ahorcado::mostrarResultado() {
    cout << "\n=== FIN DEL JUEGO ===" << endl;

    if (juegoGanado) {
        cout << "¡FELICIDADES! Adivinaste la palabra: " << palabraSecreta << endl;
        cout << "Puntuacion: " << puntuacion << " puntos" << endl;
    }
    else {
        cout << "¡PERDISTE! La palabra era: " << palabraSecreta << endl;
        cout << "Puntuacion: 0 puntos" << endl;
    }

    dibujarAhorcado();
}

void Ahorcado::guardarPartida() {
    ofstream archivo("historial.txt", ios::app);
    if (archivo.is_open()) {
        time_t t = time(nullptr);

        struct tm* timeinfo = localtime(&t);
        char fecha[11];
        strftime(fecha, sizeof(fecha), "%Y-%m-%d", timeinfo);

        archivo << fecha << " " << nombreJugador << " AH ";
        archivo << (juegoGanado ? "G" : "P") << " ";
        archivo << puntuacion << endl;
        archivo.close();
    }
}

void Ahorcado::establecerPalabra(string palabra) {
    palabraSecreta = "";
    // Convertir a minusculas
    for (int i = 0; i < palabra.length(); i++) {
        palabraSecreta += tolower(palabra[i]);
    }
}

void Ahorcado::mostrarEstado() {
    cout << "\n--- Estado del juego ---" << endl;
    cout << "Palabra: ";
    for (int i = 0; i < palabraAdivinada.length(); i++) {
        cout << palabraAdivinada[i] << " ";
    }
    cout << endl;

    cout << "Intentos fallidos: " << intentosFallidos << "/" << maxIntentos << endl;

    cout << "Letras usadas: ";
    for (int i = 0; i < numLetrasUsadas; i++) {
        cout << letrasUsadas[i] << " ";
    }
    cout << endl;

    dibujarAhorcado();
}

bool Ahorcado::procesarLetra(char letra) {
    bool encontrada = false;

    for (int i = 0; i < palabraSecreta.length(); i++) {
        if (palabraSecreta[i] == letra) {
            palabraAdivinada[i] = letra;
            encontrada = true;
        }
    }

    return encontrada;
}

bool Ahorcado::letraYaUsada(char letra) {
    for (int i = 0; i < numLetrasUsadas; i++) {
        if (letrasUsadas[i] == letra) {
            return true;
        }
    }
    return false;
}

void Ahorcado::agregarLetraUsada(char letra) {
    if (numLetrasUsadas < 26) {
        letrasUsadas[numLetrasUsadas] = letra;
        numLetrasUsadas++;
    }
}

void Ahorcado::cargarPalabras() {
    ifstream archivo("palabras.txt");
    vector<string> listaPalabras;
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de palabras." << endl;
        establecerPalabra("palabra"); // Palabra por defecto
        return;
    }

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            // Convertir a minusculas
            for (char& c : linea) {
                c = tolower(c);
            }
            listaPalabras.push_back(linea);
        }
    }

    archivo.close();

    if (listaPalabras.empty()) {
        cerr << "Error: El archivo de palabras esta vacio." << endl;
        establecerPalabra("palabra");
    }
    else {
        // Generar indice aleatorio real
        int indice = rand() % listaPalabras.size();
        establecerPalabra(listaPalabras[indice]);
    }
}

void Ahorcado::dibujarAhorcado() {
    cout << "\n";
    switch (intentosFallidos) {
    case 0:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    case 1:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "   ()  |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    case 2:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "   ()  |" << endl;
        cout << "   |   |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    case 3:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "   ()  |" << endl;
        cout << "  /|   |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    case 4:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "   ()  |" << endl;
        cout << "  /|\\ |" << endl;
        cout << "       |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    case 5:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "   ()   |" << endl;
        cout << "  /|\\  |" << endl;
        cout << "  /    |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    case 6:
        cout << "   +---+" << endl;
        cout << "   |   |" << endl;
        cout << "   ()   |" << endl;
        cout << "  /|\\  |" << endl;
        cout << "  / \\  |" << endl;
        cout << "       |" << endl;
        cout << "=========" << endl;
        break;
    }
}