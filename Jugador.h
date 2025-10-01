#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador {
private:
    std::string nombre;
    char simbolo; // 'X' o 'O'

public:
    Jugador(std::string n = "Jugador", char s = 'X');
    ~Jugador();

    std::string getNombre() const;
    char getSimbolo() const;
    void setNombre(const std::string &n);
    void setSimbolo(char s);
};

#endif
