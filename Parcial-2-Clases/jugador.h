#ifndef JUGADOR_H
#define JUGADOR_H

#include "tablero.h"


class Jugador
{
private:

    char ficha;

public:

    Jugador(char f) : ficha(f);
    void ElegirMovimiento(const Tablero& tablero, int &fila, int &columna) const;
};

#endif // JUGADOR_H
