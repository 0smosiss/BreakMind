#include "Ahorcado.h"
#include <fstream>
#include <cctype>

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
        std::time_t t = std::time(nullptr);
        std::tm local = {};
        localtime_s(&local, &t);  

        char fecha[11];
        std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", &local);

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
    string palabras[] = {
        "programacion", "computadora", "juego", "ahorcado", "universidad",
        "algoritmo", "variable", "funcion", "compilador", "depurador",
        "framework", "biblioteca", "interfaz", "desarrollo", "software",
        "hardware", "sistema", "aplicacion", "navegador", "servidor",
        "cliente", "protocolo", "encriptacion", "java", "python",
        "javascript", "html", "css", "base", "datos",
        "red", "internet", "web", "codigo", "programa",
        "error", "debug", "test", "git", "github",
        "api", "url", "http", "json", "xml",
        "sql", "mysql", "mongodb", "linux", "windows",
        "android", "ios", "mobile", "app", "frontend",
        "backend", "fullstack", "devops", "cloud", "aws",
        "azure", "docker", "kubernetes", "microservicio", "agile"
    };
    int numPalabras = 60;
    // Selección "aleatoria" simple
    int indice = numLetrasUsadas % numPalabras;
    establecerPalabra(palabras[indice]);
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