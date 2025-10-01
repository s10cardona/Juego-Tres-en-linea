#include "Juego.h"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

Juego::Juego(const std::string &archivo) {
    tablero = new Tablero();
    jugador1 = new Jugador("Jugador 1", 'X');
    jugador2 = new Jugador("Jugador 2", 'O');
    turnoActual = jugador1;  // Comienza el jugador 1
    archivoGuardado = archivo;
}

Juego::~Juego() {
    delete tablero;
    delete jugador1;
    delete jugador2;
}

bool Juego::guardar() {
    ofstream out(archivoGuardado);
    if (!out.is_open()) return false;

    // Guardar tablero
    out << tablero->serializar() << "\n";

    // Guardar jugador1
    out << jugador1->getNombre() << "," << jugador1->getSimbolo() << "\n";

    // Guardar jugador2
    out << jugador2->getNombre() << "," << jugador2->getSimbolo() << "\n";

    // Guardar turno actual
    out << turnoActual->getSimbolo() << "\n";

    out.close();
    return true;
}

bool Juego::cargar() {
    ifstream in(archivoGuardado);
    if (!in.is_open()) return false;

    string s, j1line, j2line, turnoLine;

    // 1. Tablero
    if (!getline(in, s)) { in.close(); return false; }
    tablero->deserializar(s);

    // 2. Jugador 1
    if (!getline(in, j1line)) { in.close(); return false; }
    size_t coma1 = j1line.find(',');
    if (coma1 != string::npos) {
        jugador1->setNombre(j1line.substr(0, coma1));
        jugador1->setSimbolo(j1line[coma1 + 1]);
    }

    // 3. Jugador 2
    if (!getline(in, j2line)) { in.close(); return false; }
    size_t coma2 = j2line.find(',');
    if (coma2 != string::npos) {
        jugador2->setNombre(j2line.substr(0, coma2));
        jugador2->setSimbolo(j2line[coma2 + 1]);
    }

    // 4. Turno actual
    if (!getline(in, turnoLine)) { in.close(); return false; }
    if (turnoLine[0] == jugador1->getSimbolo())
        turnoActual = jugador1;
    else
        turnoActual = jugador2;

    in.close();
    return true;
}

void Juego::jugar() {
    int opcion;
    bool salir = false;

    while (!salir) {
        cout << "\n=== MENU PRINCIPAL ===\n";
        cout << "1. Nueva partida\n";
        cout << "2. Continuar partida\n";
        cout << "3. Reiniciar partida\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida.\n";
            continue;
        }

        switch (opcion) {
        case 1:
            delete tablero;
            tablero = new Tablero();
            turnoActual = jugador1;
            break;
        case 2:
            if (!cargar()) {
                cout << "No se pudo cargar partida. Iniciando nueva.\n";
                delete tablero;
                tablero = new Tablero();
                turnoActual = jugador1;
            }
            break;
        case 3:
            delete tablero;
            tablero = new Tablero();
            turnoActual = jugador1;
            cout << "Partida reiniciada.\n";
            break;
        case 4:
            salir = true;
            continue;
        default:
            cout << "Opcion invalida.\n";
            continue;
        }

        // Bucle del juego
        while (true) {
            tablero->mostrar();
            cout << "Turno de " << turnoActual->getNombre()
                 << " (" << turnoActual->getSimbolo() << ")\n";
            cout << "Ingrese una posicion (1-9) o 0 para salir: ";
            int pos;
            cin >> pos;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida.\n";
                continue;
            }

            if (pos == 0) {
                if (guardar()) cout << "Partida guardada.\n";
                else cout << "No se pudo guardar la partida.\n";
                break;
            }

            if (!tablero->colocarFichaPos(pos, turnoActual->getSimbolo())) {
                cout << "Movimiento invalido. Intente de nuevo.\n";
                continue;
            }

            char ganador = tablero->verificarGanador();
            if (ganador != ' ') {
                tablero->mostrar();
                cout << "¡Ganador: " << turnoActual->getNombre()
                     << " (" << turnoActual->getSimbolo() << ")!\n";
                break;
            }

            if (tablero->tableroLleno()) {
                tablero->mostrar();
                cout << "Empate.\n";
                break;
            }

            // Cambiar turno
            turnoActual = (turnoActual == jugador1) ? jugador2 : jugador1;
        }
    }
}



