#include "UserInterfaz.h"
#include "Movimientos.h"
#include "Tablero.h"
#include <iostream>

using namespace std;

void makeMove(int player) {

	// variables de funcionamiento
	char pieza;
	string start, end;
	int iniX, iniY, finX, finY;
	bool movimientoCompletado = false;

	// realizara este bucle mientras el "while(!movecomleted)" se mantentga en false
	do {
		cout << "Jugador " << player << ", elige una pieza para mover (formato Ej: A1): ";
		cin >> start;
		cout << "Elige la posicion final para tu pieza (formato Ej: A5): ";
		cin >> end;

		// separamos los parametros dados por el usuario con su input y los transformamos en coordenadas para poder trabajar con el tablero de manera numerica
		iniX = 8 - (start[1] - '0');
		iniY = start[0] - 'A';
		finX = 8 - (end[1] - '0');
		finY = end[0] - 'A';
		pieza = tablero[iniX][iniY];


		// realizamos los movimientos si la funcion encargada de verificar el reglamento retorna true
		if (esValido(player, pieza, iniX, iniY, finX, finY)) {
			// modificamos el tablero poniendo la pieza seleccionada
			tablero[finX][finY] = pieza;
			// el valor donde estaba originalmente la pieza vuelve a ser un tablero
			tablero[iniX][iniY] = '*';
			// movimiento realizado exitosamente
			movimientoCompletado = true;
		}
		// en caso de ser false lo que retorna "esValido", mostrara el mensaje de error siguiente (posiblemente este mensaje se modifique en verisonbes futuras segun el error que cometa el jugador)
		else {
			cout << "Movimiento invalido, intenta de nuevo." << endl;
		}
	} while (!movimientoCompletado);
}