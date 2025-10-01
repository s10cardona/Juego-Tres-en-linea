#include "Juego.h"
#include <iostream>
#include <fstream>
using namespace std;

// Constructor
Juego::Juego(const string& archivo) {
    tablero = new Tablero(); // creamos tablero en memoria dinámica
    jugadorActual = 'X';     // inicia siempre X
    archivoGuardado = archivo;
    cargarPartida();         // intentamos cargar guardado
}

// Destructor
Juego::~Juego() {
    delete tablero; // liberar memoria del tablero
}

// Cargar partida desde archivo
void Juego::cargarPartida() {
    ifstream file(archivoGuardado);
    if (file.is_open()) {
        char c;
        int i = 0;
        while (file >> c && i < 9) {
            if (c == 'X' || c == 'O' || c == ' ')
                tablero->setCelda(i, c);
            i++;
        }
        file >> jugadorActual; // cargar turno del jugador
        file.close();

        cout << "\nSe encontro una partida guardada. "
             << "¿Deseas continuarla? (s/n): ";
        char opcion;
        cin >> opcion;
        if (opcion == 'n' || opcion == 'N') {
            // reiniciar tablero
            delete tablero;
            tablero = new Tablero();
            jugadorActual = 'X';
        }
    }
}

// Guardar partida en archivo
void Juego::guardarPartida() {
    ofstream file(archivoGuardado);
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            file << tablero->getCelda(i) << " ";
        }
        file << jugadorActual; // guardar turno actual
        file.close();
    }
}

// Ciclo principal del juego
void Juego::jugar() {
    bool jugando = true;

    while (jugando) {
        tablero->mostrar();
        cout << "Turno del jugador " << jugadorActual << endl;
        cout << "Elige una posicion (1-9): ";

        int pos;
        cin >> pos;

        if (pos < 1 || pos > 9) {
            cout << "Posicion invalida. Intenta de nuevo.\n";
            continue;
        }

        // Intentar colocar la ficha
        if (!tablero->colocarFicha(pos - 1, jugadorActual)) {
            cout << "Esa posicion ya esta ocupada. Intenta otra.\n";
            continue;
        }

        // Guardar el progreso
        guardarPartida();

        // Verificar ganador
        char ganador = tablero->verificarGanador();
        if (ganador != ' ') {
            tablero->mostrar();
            cout << "¡El jugador " << ganador << " ha ganado! Felicidades.\n";
            break; // termina juego, pero NO borra archivo
        }

        // Verificar empate
        if (tablero->tableroLleno()) {
            tablero->mostrar();
            cout << "¡Empate! No hay mas movimientos posibles.\n";
            break; // termina juego, pero NO borra archivo
        }

        // Cambiar de jugador
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }
}

