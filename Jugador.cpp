#include "Jugador.h"

Jugador::Jugador(std::string n, char s) {
    nombre = n;
    simbolo = s;
}

Jugador::~Jugador() {}

std::string Jugador::getNombre() const {
    return nombre;
}

char Jugador::getSimbolo() const {
    return simbolo;
}

void Jugador::setNombre(const std::string &n) {
    nombre = n;
}

void Jugador::setSimbolo(char s) {
    simbolo = s;
}
