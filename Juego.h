#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include "Jugador.h"
#include <string>

class Juego {
private:
    Tablero* tablero;       // puntero dinámico al tablero
    Jugador* jugador1;      // jugador 1
    Jugador* jugador2;      // jugador 2
    Jugador* turnoActual;   // quién está jugando
    std::string archivoGuardado;

public:
    Juego(const std::string &archivo = "savegame.txt");
    ~Juego();

    void jugar();   // lógica principal
    bool guardar(); // guardar progreso
    bool cargar();  // cargar progreso
};

#endif

