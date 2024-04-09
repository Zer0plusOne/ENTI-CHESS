#include "Tablero.h"
#include "UserInterfaz.h"
#include <iostream>

using namespace std;

int main() {
// inicializamos el tablero y ponemos las piezas
	inicializarTablero();
	setupPiezas();
// variables de juego
	bool gameover = false;
	int currentPlayer = 1;
// bucle jugable
	while (!gameover) {
		system("cls");
		displayTablero();
		makeMove(currentPlayer);
		currentPlayer = (currentPlayer % 2) + 1;
	}
// salida standard
	return 0;
}
