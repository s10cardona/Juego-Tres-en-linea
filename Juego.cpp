// Juego.cpp  (reemplaza tu archivo actual por este)
#include "Juego.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

 // Constructor
Juego::Juego(const std::string &archivo) {
    tablero = new Tablero();
    jugadores[0] = 'X';
    jugadores[1] = 'O';
    turnoIndice = 0;
    turnoPtr = &jugadores[turnoIndice];
    archivoGuardado = archivo;
}

// Destructor
Juego::~Juego() {
    delete tablero;
}

// Guarda el estado actual (usa serializar() de Tablero)
bool Juego::guardar() {
    ofstream out(archivoGuardado);
    if (!out.is_open()) {
        return false;
    }
    string s = tablero->serializar(); // 9 chars
    out << s << "\n";
    out << *turnoPtr << "\n";
    out.close();
    return true;
}

// Carga estado si existe el archivo; devuelve true si pudo cargar
bool Juego::cargar() {
    ifstream in(archivoGuardado);
    if (!in.is_open()) return false;
    string s;
    string turnoLine;
    if (!getline(in, s)) { in.close(); return false; }
    if (!getline(in, turnoLine)) { in.close(); return false; }
    in.close();

    // restaurar tablero y turno
    tablero->deserializar(s);
    if (turnoLine.size() > 0 && (turnoLine[0] == 'X' || turnoLine[0] == 'O')) {
        if (turnoLine[0] == jugadores[0]) turnoIndice = 0;
        else turnoIndice = 1;
        turnoPtr = &jugadores[turnoIndice];
        return true;
    }
    return false;
}

// Bucle principal del juego
void Juego::jugar() {
    cout << "Bienvenido al Triqui (dos jugadores)\n";
    cout << "Se guardara automaticamente despues de cada movimiento.\n";
    cout << "Para salir y guardar en cualquier momento escribe 0 en lugar de posicion.\n\n";

    // intentar cargar partida guardada (si existe)
    if (cargar()) {
        cout << "Se encontro una partida guardada. ¿Deseas continuarla? (s/n): ";
        char resp;
        cin >> resp;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (resp != 's' && resp != 'S') {
            // reiniciar tablero
            delete tablero;
            tablero = new Tablero();
            turnoIndice = 0;
            turnoPtr = &jugadores[turnoIndice];
            guardar(); // guardar tablero limpio
            cout << "Partida nueva iniciada.\n\n";
        } else {
            cout << "Continuando la partida guardada.\n\n";
        }
    } else {
        // no habia guardado, creamos archivo base
        guardar();
    }

    char ganador = ' ';
    while (true) {
        tablero->mostrar();
        cout << "Turno del jugador " << *turnoPtr << ". Ingresa posicion (1-9) o 0 para guardar y salir: ";

        int pos;
        if (!(cin >> pos)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intenta con un numero entre 1 y 9 (o 0 para salir).\n";
            continue;
        }

        if (pos == 0) {
            if (guardar()) cout << "Partida guardada. Puedes volver luego y continuar.\n";
            else cout << "No se pudo guardar la partida.\n";
            break;
        }

        // usar colocarFichaPos (1..9) que existe en Tablero.h
        if (!tablero->colocarFichaPos(pos, *turnoPtr)) {
            cout << "Movimiento invalido (posicion fuera de rango o ya ocupada). Intenta de nuevo.\n\n";
            continue;
        }

        // guardar progreso despues de cada movimiento
        if (!guardar()) cout << "Advertencia: no se pudo guardar el progreso.\n";

        // comprobar ganador y empate
        ganador = tablero->verificarGanador();
        if (ganador != ' ') {
            tablero->mostrar();
            cout << "¡El jugador " << ganador << " ha ganado! Felicidades.\n";
            break;
        }

        if (tablero->tableroLleno()) {
            tablero->mostrar();
            cout << "¡Empate! No hay mas movimientos posibles.\n";
            break;
        }

        // cambiar turno
        turnoIndice = (turnoIndice + 1) % 2;
        turnoPtr = &jugadores[turnoIndice];
    }

    cout << "Gracias por jugar.\n";
}
