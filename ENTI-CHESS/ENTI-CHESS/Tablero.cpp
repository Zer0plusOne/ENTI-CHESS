#include "Tablero.h"
#include <iostream>
#include <string>

using namespace std;
// defino la variable del tablero ya que sino el aplicativo crashea
char tablero[tablero_SIZE][tablero_SIZE];

void inicializarTablero() {
	for (int i = 0; i < tablero_SIZE; i++) {
		for (int j = 0; j < tablero_SIZE; j++) {
			tablero[i][j] = '*';
		}
	}
}
void setupPiezas() {

	// almacenamos las piezas segun su color para luego ser insertadas dentro del tablero ya inicializado
	const string whitePiezasFila = "THBQKBHT";
	const string blackPiezasFila = "thbkqbht";
	const char whitePeon = 'P';
	const char blackPeon = 'p';

	// rellenamos las piezas en el tablero con este bucle for
	for (int i = 0; i < tablero_SIZE; i++) {
		tablero[6][i] = whitePeon;
		tablero[7][i] = whitePiezasFila[i];
		tablero[1][i] = blackPeon;
		tablero[0][i] = blackPiezasFila[i];
	}
}

// mostramos el tablero de la misma manera que mostramos en su momento el mapa del snake
void displayTablero() {
	cout << "  -----------------" << endl;
	for (int i = 0; i < tablero_SIZE; i++) {
		cout << 8 - i << "| ";
		for (int j = 0; j < tablero_SIZE; j++) {
			cout << tablero[i][j] << " ";
		}
		cout << "|\n";
	}
	cout << "  -----------------" << endl;
	cout << "   A B C D E F G H" << endl;
}
