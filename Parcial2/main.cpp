#include <iostream>

//  Representa el tablero de juego para Othello

class Tablero {
private:
    char **tablero; //Matriz dinámica para representar el tablero.
    int filas;      // Número de filas en el tablero.
    int columnas;   //Número de columnas en el tablero.

public:

    // Constructor que inicializa el tablero con un tamaño específico.

    Tablero(int filas, int columnas)
        : filas(filas), columnas(columnas) {
        tablero = new char*[filas]; // Inicialización de la matriz dinámica.
        for (int i = 0; i < filas; i++) {
            tablero[i] = new char[columnas];
            for (int j = 0; j < columnas; j++) {
                tablero[i][j] = ' ';
            }
        }

        // Colocando las piezas iniciales en el centro del tablero.
        tablero[filas/2 - 1][columnas/2 - 1] = 'O';
        tablero[filas/2][columnas/2] = 'O';
        tablero[filas/2 - 1][columnas/2] = 'X';
        tablero[filas/2][columnas/2 - 1] = 'X';
    }

    // Destructor. Libera la memoria asignada para el tablero.
    ~Tablero() {
        for (int i = 0; i < filas; i++) {
            delete[] tablero[i];
        }
        delete[] tablero;
    }

    // Imprime el tablero en la consola.

    void ImprimirTablero() const {
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
    /**
     * Verifica si un movimiento es válido para un jugador específico.
     *
     * Fila donde se desea colocar la pieza.
     * Columna donde se desea colocar la pieza.
     * El jugador que desea realizar el movimiento ('X' o 'O').
     * true si el movimiento es válido, false en caso contrario.
     */


    bool EsMovimientoValido(int fila, int columna, char jugador) const {
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

    void RealizarMovimiento(int fila, int columna, char jugador) {
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

    bool HayMovimientosDisponibles(char jugador) const {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (EsMovimientoValido(i, j, jugador)) return true;
            }
        }
        return false;
    }

    // Método para verificar si el juego ha finalizado.
    bool JuegoFinalizado() const {
        return !(HayMovimientosDisponibles('X') || HayMovimientosDisponibles('O'));
    }

    char ObtenerGanador() const {
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
};



class Jugador {
private:
    char ficha;

public:
    Jugador(char f) : ficha(f) {}

    void ElegirMovimiento(const Tablero& tablero, int &fila, int &columna) const {

    }
};

class Juego {
private:
    Tablero* tablero;
    Jugador* jugador1;
    Jugador* jugador2;

public:
    Juego(const Jugador& j1, const Jugador& j2, int filas = 8, int columnas = 8)
        : jugador1(new Jugador(j1)), jugador2(new Jugador(j2)), tablero(new Tablero(filas, columnas)) {}

    ~Juego() {
        delete tablero;
        delete jugador1;
        delete jugador2;
    }

    void IniciarJuego();
    void MostrarResultado() const;
};

void Juego::IniciarJuego() {

}

void Juego::MostrarResultado() const {

}

int main() {
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
