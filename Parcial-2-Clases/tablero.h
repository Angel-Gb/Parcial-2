#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>


class Tablero
{
    private:

        char **tablero; //Matriz dinámica para representar el tablero.
        int filas;      // Número de filas en el tablero.
        int columnas;   //Número de columnas en el tablero.

    public:

        Tablero(int filas, int columnas);
        ~Tablero();
        void ImprimirTablero() const ;
        bool EsMovimientoValido(int fila, int columna, char jugador) const ;
        void RealizarMovimiento(int fila, int columna, char jugador);
        bool HayMovimientosDisponibles(char jugador) const;
        bool JuegoFinalizado() const;
        char ObtenerGanador() const;

};

#endif // TABLERO_H
