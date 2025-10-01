#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include <string>

class Juego {
private:
    Tablero* tablero;   // puntero dinámico al tablero
    char jugadores[2];  // 'X' y 'O'
    int turnoIndice;    // 0 o 1
    char* turnoPtr;     // puntero al símbolo actual
    std::string archivoGuardado;

public:
    Juego(const std::string &archivo = "savegame.txt"); // constructor con nombre de archivo
    ~Juego();

    // Ejecuta el bucle principal del juego
    void jugar();

    // Guarda y carga el estado del juego
    bool guardar();
    bool cargar();
};

#endif
