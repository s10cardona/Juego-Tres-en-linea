#ifndef TABLERO_H
#define TABLERO_H

#include <string>

class Tablero {
private:
    char** celdas; // puntero a puntero para la matriz dinámica 3x3

public:
    Tablero();               // constructor: reserva e inicializa
    ~Tablero();              // destructor: libera memoria

    // Colocar ficha por posición 1..9 (devuelve true si pudo colocar)
    bool colocarFichaPos(int pos, char ficha);

    // Mostrar tablero en consola
    void mostrar();

    // Verificar ganador: devuelve 'X' o 'O' si hay ganador, ' ' si no
    char verificarGanador();

    // Devuelve true si tablero está lleno (empate)
    bool tableroLleno();

    // Serializar tablero a string de 9 caracteres (para guardar)
    std::string serializar();

    // Deserializar tablero desde string de 9 caracteres (para cargar)
    void deserializar(const std::string &s);
};

#endif
