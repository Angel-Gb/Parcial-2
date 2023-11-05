#include "tablero.h"

//Constructor que inicializa el tablero con un tamaño especifico

Tablero::Tablero(int filas, int columnas)
{
    tablero = new char* [filas]; // Inicialización de la matriz dinámica.
    for (int i = 0; i <= filas; i++) {
        tablero[i] = new char [columnas];
        for (int j = 0; j <= columnas; j++) {
            tablero[i][j] = 32;
        }
    }

    //filas, columnas;
    // Colocando las piezas iniciales en el centro del tablero.

    tablero[filas/2 - 1][columnas/2 - 1] = 'O';
    tablero[filas/2][columnas/2] = 'O';
    tablero[filas/2 - 1][columnas/2] = 'X';
    tablero[filas/2][columnas/2 - 1] = 'X';

}

// Destructor. Libera la memoria asignada para el tablero.

Tablero::~Tablero() {

    for (int i = 0; i < filas; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;

}

// Imprime el tablero en la consola.

void Tablero::ImprimirTablero() const {

    std::cout << "  ";  // Espaciado para las etiquetas de las filas
    for (char c = 'A'; c < 'A' + columnas; c++) {
        std::cout << c << " ";
    }
    std::cout << std::endl;
        // Imprimir contenido del tablero.
    for (int i = 0; i < filas; i++) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < columnas; j++) {
            std::cout << tablero[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Tablero::EsMovimientoValido(int fila, int columna, char jugador) const {

    // Verificar que la casilla esté vacía.
    if (tablero[fila][columna] != ' ') return false;
    char oponente = (jugador == 'X') ? 'O' : 'X'; //Determinar quién es el oponente.
    int direcciones[8][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}}; // Direcciones para buscar piezas enemigas.

    // Revisar todas las direcciones para encontrar una pieza oponente contigua.
    for (int i = 0; i < 8; i++) {
        int x = fila + direcciones[i][0];
        int y = columna + direcciones[i][1];
        bool encontroOponente = false;

        // Continuar en esa dirección hasta encontrar una pieza propia.
        while (x >= 0 && x < filas && y >= 0 && y < columnas && tablero[x][y] == oponente) {
            x += direcciones[i][0];
            y += direcciones[i][1];
            encontroOponente = true;
        }

        // Si se encontró una pieza propia al final, el movimiento es válido.
        if (encontroOponente && x >= 0 && x < filas && y >= 0 && y < columnas && tablero[x][y] == jugador)
            return true;
    }
    return false;
}

void Tablero::RealizarMovimiento(int fila, int columna, char jugador) {

    if (!EsMovimientoValido(fila, columna, jugador)) return;
    tablero[fila][columna] = jugador;

    char oponente = (jugador == 'X') ? 'O' : 'X';
    int direcciones[8][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};

    for (int i = 0; i < 8; i++) {
        int x = fila + direcciones[i][0];
        int y = columna + direcciones[i][1];
        bool encontroOponente = false;

        while (x >= 0 && x < filas && y >= 0 && y < columnas && tablero[x][y] == oponente) {
            x += direcciones[i][0];
            y += direcciones[i][1];
            encontroOponente = true;
        }

        if (encontroOponente && x >= 0 && x < filas && y >= 0 && y < columnas && tablero[x][y] == jugador) {
            x = fila + direcciones[i][0];
            y = columna + direcciones[i][1];
            while (x >= 0 && x < filas && y >= 0 && y < columnas && tablero[x][y] == oponente) {
                tablero[x][y] = jugador;
                x += direcciones[i][0];
                y += direcciones[i][1];
            }
        }
    }
}

bool Tablero::HayMovimientosDisponibles(char jugador) const {

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (EsMovimientoValido(i, j, jugador)) return true;
        }
    }
    return false;
}

// Método para verificar si el juego ha finalizado.
bool Tablero::JuegoFinalizado() const {

    if(HayMovimientosDisponibles('X')==false or HayMovimientosDisponibles('O')==false)
        return true;

    //return !(HayMovimientosDisponibles('X') or HayMovimientosDisponibles('O'));
}

char Tablero::ObtenerGanador() const {

    int x = 0, o = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] == 'X') x++;
            else if (tablero[i][j] == 'O') o++;
        }
    }
    if (x == o) return '-';
    return (x > o) ? 'X' : 'O';
}

int Tablero::CantidadFichas() {

    int x = 0, o = 0;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (tablero[i][j] == 'X') x++;
            else if (tablero[i][j] == 'O') o++;
        }
    }

    if (x >= o) {
        return x;
    } else {
        return o;
    }

}
