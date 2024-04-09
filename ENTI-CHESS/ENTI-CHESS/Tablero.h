#pragma once

#define TABLERO_H

#include <string>

const int tablero_SIZE = 8;

extern char tablero[tablero_SIZE][tablero_SIZE];

void inicializarTablero();
void setupPiezas();
void displayTablero();

