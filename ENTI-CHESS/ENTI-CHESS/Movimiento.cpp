#include "Movimientos.h"
#include "Tablero.h"

using namespace std;

// boolean que retorna cierto o falso segun si en medio de ese movimiento se encuentra o no una pieza
bool caminoLimpio(int iniX, int iniY, int finX, int finY) {

	int xDireccion = 0;
	if (finX != iniX) {
		xDireccion = (finX - iniX) > 0 ? 1 : -1;
	}

	int yDireccion = 0;
	if (finY != iniY) {
		yDireccion = (finY - iniY) > 0 ? 1 : -1;
	}

	int currentX = iniX + xDireccion;
	int currentY = iniY + yDireccion;

	while (currentX != finX || currentY != finY) {
		if (tablero[currentX][currentY] != '*') {
			return false;
		}
		currentX += xDireccion;
		currentY += yDireccion;
	}

	return true;
}

// funcion booleana que retornara cierto o falso segun si el movimiento realizado es valido o no segun el reglamento
bool esValido(int player, char pieza, int iniX, int iniY, int finX, int finY) {

	if (iniX < 0 || iniX >= tablero_SIZE || iniY < 0 || iniY >= tablero_SIZE || finX < 0 || finX >= tablero_SIZE || finY < 0 || finY >= tablero_SIZE) {
		return false;
	}

	// verificamos que los jugadores toquen sus piecas
	if ((player == 1 && (pieza < 'A' || pieza > 'Z')) || (player == 2 && (pieza < 'a' || pieza > 'z'))) { // chivatazo del chatgpt, no sabia que se podia hacer esto para diferenciar entre mayusculas y minusculas. En otro caso podria implementar la libreria cctypes y usar "isLower() & isUpper()"
		return false;
	}
	// excluyo al caballo ya que este si se puede mover aunque tenga a gente en frente
	if ((pieza != 'H' && pieza != 'h') && !caminoLimpio(iniX, iniY, finX, finY)) {
		return false;
	}

	//con un switch con el valor de la pieza seleccionada en ese momento....
	switch (pieza) {
	case'*': {
		return false;
	}
		   /* Apunte rapido: se usa "abs" para convertir cualquier valor en un valor absoluto, es decir cualquier negativo pasa a ser positivo, esto con tal de que no me de problemas como estaba haciendo */
		   // ChatGPT me lo ha chivado ya que en los movimientos diagonales sino me daba problemas a la hora de querer ejecutarlos y no encontraba el problema
		   // caso compartido para peones blancos y negros

	case 'P': case 'p': {
		// movimiento frontal

		// especifico, el peon solo se puede mover hacia adelante (blanco hacia arriba y negro hacia abajo)
		int movimientoFrontal = (pieza == 'P') ? -1 : 1;
		// definimos cuales son las filas iniciales segun el color de la ficha (mayuscula o minuscula)
		int startFila = (pieza == 'P') ? 6 : 1;
		// verificamos que el movimiento se realice hacia a delante
		if (iniX + movimientoFrontal == finX && iniY == finY && tablero[finX][finY] == '*') {
			return true; // en el caso que el movimiento sea de uno
		}
		// el peon podra moverse en diagonal (para captuarar) en caso que el caracter donde se mueva sea "*"
		else if (iniX + movimientoFrontal == finX && abs(iniY - finY) == 1 && tablero[finX][finY] != '*') {
			return true;
		}
		// si el peon se encuentra en alguna de las casillas (su fila respectiva de inicio) iniciales, permitimos que el movimiento se realice siempre y cuando se mueva a una casilla vacia
		else if (iniX == startFila && iniX + 2 * movimientoFrontal == finX && iniY == finY && tablero[finX][finY] == '*' && tablero[iniX + movimientoFrontal][iniY] == '*') {
			return true;
			// si la pieza del peon blanco se encuentra en la fila superior
		}
		else if (pieza == 'P' && finX == 0) {
			tablero[finX][finY] = 'Q';
		}	// lo mismo para el peon negro
		else if (pieza == 'p' && finX == 7) {
			tablero[finX][finY] = 'q';
		}
		break;
	}
			// caso para el alfil
	case 'B':
	case 'b': {
		// siempre y cuando el camino este limpio solo podra moverse en diagonal
		if (abs(iniX - finX) == abs(iniY - finY)) {
			return caminoLimpio(iniX, iniY, finX, finY);
		}
		break;
		// caso para la torre
	case 'T':
	case 't': {
		// siempre y cuando X o Y sean iguales en la posicion inicial y la posterior en el mismo eje sea la misma 
		if (iniX == finX || iniY == finY) {
			// retornamos lo que retornaria la funcion "caminoLimpio" asi mato dos pajaros de un tiro, por un lado verifico que el movimiento de la torre sea solo en el mismo eje en X o Y y que el camino este libre
			return caminoLimpio(iniX, iniY, finX, finY);
		}
		break;

		// caso de la reina
	case 'Q':
	case 'q': {
		// fusiono basicamente los parametros del if de los casos de las torres y los alfiles
		if (iniX == finX || iniY == finY || abs(iniX - finX) == abs(iniY - finY)) {
			// de igual modo que con las torres, mandamos a que el resultado lo de la funcion caminoLimpio asi verificamos que no pueda saltarse las fichas en caso de tener una en medio
			return caminoLimpio(iniX, iniY, finX, finY);
		}
		else {
			return false;
		}
	}
	}
			break;

			// caso del rey
	case 'K':
	case 'k': {
		// se puede mover en cualquier direccion pero unicamente una casilla (se utilizan valores absolutos para el tema de los movimientos que interpreta como diagonales)
		if ((abs(iniX - finX) <= 1 && abs(iniY - finY) <= 1)) {
			// no es necesario verificar si esa posicion se encuentra vacia ya que el rey tambienb puede capturar de esa manera
			return true;
		}
		else {
			return false;
		}
	}
	case 'H':
	case 'h': {
		// hardcodeo cuales son las reglas para que realice siempre el movimiento en L, lo cual es que siempre ha de incrementar en 2 en uno de los dos ejes y posteriormentre uno en positivo o negativo en el eje contrario
		if ((abs(iniX - finX) == 2 && abs(iniY - finY) == 1) || (abs(iniX - finX) == 1 && abs(iniY - finY) == 2)) {
			// no llamo a la funcion "caminoLimpio" ya que el caballo segun la normativa puede saltar a las piezas
			return true;
		}
	}
	}
	}
	// para cualquier cosa que no este contemplada dentro del switch, devuelve false
	return false;
}