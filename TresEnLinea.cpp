#include <iostream>
#include <cstdio>  
#include "Juego.h"
using namespace std;

int main() {
    bool salir = false;
    while (!salir) {
        cout << "\n===== MENU TRIQUI =====\n";
        cout << "1. Jugar / Continuar\n";
        cout << "2. Reiniciar partida\n";
        cout << "3. Salir\n";
        cout << "Elige una opcion: ";

        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            Juego* partida = new Juego("savegame.txt");
            partida->jugar();
            delete partida; 
        }
        else if (opcion == 2) {
            if (remove("savegame.txt") == 0) {
                cout << "Partida anterior eliminada. Se iniciara una nueva en el siguiente juego.\n";
            } else {
                cout << "No habia partida guardada.\n";
            }
        }
        else if (opcion == 3) {
            cout << "Saliendo del juego...\n";
            salir = true;
        }
        else {
            cout << "Opcion invalida. Intenta de nuevo.\n";
        }
    }

    return 0;
}