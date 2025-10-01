#include "Tablero.h"
#include <iostream>
using namespace std;

// Constructor: reservar memoria dinámica 3x3 e inicializar con espacios
Tablero::Tablero() {
    celdas = new char*[3];
    for (int i = 0; i < 3; i++) {
        celdas[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            celdas[i][j] = ' ';
        }
    }
}

// Destructor: liberar memoria
Tablero::~Tablero() {
    for (int i = 0; i < 3; i++) {
        delete[] celdas[i];
    }
    delete[] celdas;
}

// Colocar ficha usando posición 1..9
bool Tablero::colocarFichaPos(int pos, char ficha) {
    if (pos < 1 || pos > 9) return false;
    int idx = pos - 1;
    int fila = idx / 3;
    int col = idx % 3;
    if (celdas[fila][col] == ' ') {
        celdas[fila][col] = ficha;
        return true;
    }
    return false; // celda ocupada
}

// Mostrar tablero con numeración de filas/columnas y posiciones 1..9 como guía
void Tablero::mostrar() {
    cout << "Tablero:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char ch = celdas[i][j];
            if (ch == ' ') {
                // mostrar el número de posición para ayudar al jugador
                int pos = i*3 + j + 1;
                cout << " " << pos << " ";
            } else {
                cout << " " << ch << " ";
            }
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "----+----+----\n";
    }
    cout << "\n";
}

// Verificar ganador (filas, columnas, diagonales)
char Tablero::verificarGanador() {
    // filas y columnas
    for (int i = 0; i < 3; i++) {
        if (celdas[i][0] != ' ' && celdas[i][0] == celdas[i][1] && celdas[i][1] == celdas[i][2])
            return celdas[i][0];
        if (celdas[0][i] != ' ' && celdas[0][i] == celdas[1][i] && celdas[1][i] == celdas[2][i])
            return celdas[0][i];
    }
    // diagonales
    if (celdas[0][0] != ' ' && celdas[0][0] == celdas[1][1] && celdas[1][1] == celdas[2][2])
        return celdas[0][0];
    if (celdas[0][2] != ' ' && celdas[0][2] == celdas[1][1] && celdas[1][1] == celdas[2][0])
        return celdas[0][2];
    return ' ';
}

// Verificar lleno
bool Tablero::tableroLleno() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (celdas[i][j] == ' ') return false;
    return true;
}

// Serializar (concatenar 9 caracteres en orden 0..8)
std::string Tablero::serializar() {
    string s;
    s.reserve(9);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            s.push_back(celdas[i][j]);
    return s;
}

// Deserializar desde string de 9 chars
void Tablero::deserializar(const std::string &s) {
    if ((int)s.size() < 9) return; // protección mínima
    int k = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            char ch = s[k++];
            // Asegurarse que solo X,O o espacio se guarden
            if (ch == 'X' || ch == 'O' || ch == ' ')
                celdas[i][j] = ch;
            else
                celdas[i][j] = ' ';
        }
}
