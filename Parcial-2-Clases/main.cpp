#include <iostream>
#include "tablero.h"
#include "juego.h"
#include "jugador.h"

using namespace std;



int main()
{

    // Crear jugadores
    Jugador jugador1('X');
    Jugador jugador2('O');

    // Crear un tablero de 8x8
    Tablero tablero(8, 8);

    // Crear una instancia del juego con los jugadores y el tablero
    Juego juego(jugador1, jugador2, 8, 8);

    // Mostrar el tablero inicial
    std::cout << "Tablero inicial:" << std::endl;
    tablero.ImprimirTablero();

    char jugadorActual = 'X';
    while (!tablero.JuegoFinalizado()) {
        int fila;
        char columnaChar;
        int columna;
        bool movimientoValido;

        do {
            std::cout << "Turno del jugador " << jugadorActual << std::endl;
            std::cout << "Ingrese la fila (1-8): ";
            std::cin >> fila;
            std::cout << "Ingrese la columna (A-H): ";
            std::cin >> columnaChar;
            columna = columnaChar - 'A';

            movimientoValido = tablero.EsMovimientoValido(fila-1, columna, jugadorActual);
            if (!movimientoValido) {
                std::cout << "Movimiento no valido. Por favor, intente de nuevo." << std::endl;
            }
        } while (!movimientoValido);

        tablero.RealizarMovimiento(fila-1, columna, jugadorActual);
        tablero.ImprimirTablero();

        // Cambiar al siguiente jugador
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    // Mostrar el resultado
    juego.MostrarResultado();

    return 0;
}
