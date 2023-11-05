#ifndef JUEGO_H
#define JUEGO_H

#include "jugador.h"
#include "tablero.h"

class Juego
{
    private:

        Tablero* tablero;
        Jugador* jugador1;
        Jugador* jugador2;

    public:
        Juego(const Jugador& j1, const Jugador& j2, int filas = 8, int columnas = 8)
            : jugador1(new Jugador(j1)), jugador2(new Jugador(j2)), tablero(new Tablero(filas, columnas)) {}


        void iniciarJuego();
        void MostrarResultado() const;

        ~Juego();
};

#endif // JUEGO_H
