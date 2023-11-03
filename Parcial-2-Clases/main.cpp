#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "tablero.h"
#include "juego.h"
#include "jugador.h"

using namespace std;

void Registro(string NuevoRegistro);
char* HoraFecha();

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
        char filas;
        int fila;
        char columnaChar;
        int columna;
        bool movimientoValido;

        do {

                std::cout << "Turno del jugador " << jugadorActual << std::endl;


                std::cout << "Ingrese la fila (1-8): ";
                std::cin >> filas;
                while(filas < 49 or filas > 56){
                    std::cout<<"Movimiento invalido, intentelo denuevo"<<std::endl;
                    std::cout << "Ingrese la fila (1-8): ";
                    std::cin >> filas;
                }

                fila = filas - '0';

                std::cout << "Ingrese la columna (A-H): ";
                std::cin >> columnaChar;
                while(columnaChar <= 64 or columnaChar >= 73){
                    std::cout<<"Movimiento invalido, intentelo denuevo"<<std::endl;
                    std::cout << "Ingrese la columna (A-H): ";
                    std::cin >> columnaChar;
                }

            columna = columnaChar - 'A';

            _sleep(3000);
            system("cls");

            movimientoValido = tablero.EsMovimientoValido(fila-1, columna, jugadorActual);
            if (!movimientoValido) {
                std::cout << "Movimiento no valido. Por favor, intente de nuevo." << std::endl;
                tablero.ImprimirTablero();
            }
        } while (!movimientoValido);

        tablero.RealizarMovimiento(fila-1, columna, jugadorActual);
        tablero.ImprimirTablero();

        // Cambiar al siguiente jugador
        jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';
    }

    char ganador;

    if (tablero.JuegoFinalizado() == true)
    {
        std::cout<<"El juego a finalizado"<<std::endl;
        ganador = tablero.ObtenerGanador();
        std::cout<<"El ganador es: "<< ganador << std::endl;
        _sleep(3000);
    }

    // Mostrar el resultado
    juego.MostrarResultado();

    char *HorayFecha = HoraFecha();

    for (int k = 0; k < 1; k++)
    {
        string jugador, NuevoRegistro = " ";
        char gano= 0, Nfichas = 0;
        Registro(NuevoRegistro);

        if(ganador == 'X')
        {
            std::cout<<"Ingrese el nombre del jugador X: ";
            std::cin>>jugador;

            Nfichas = tablero.CantidadFichas();

            gano = tablero.ObtenerGanador();
            if(gano == true)
                NuevoRegistro = jugador+",si,"+Nfichas+HorayFecha+";";
            else
                NuevoRegistro = jugador+",no,"+Nfichas+HorayFecha+";";
        }

        else
        {
            std::cout<<"Ingrese el nombre del jugador 0: ";
            std::cin>>jugador;

            Nfichas = tablero.CantidadFichas();

            gano = tablero.ObtenerGanador();
            if(gano == true)
                NuevoRegistro = jugador+",si,"+Nfichas+HorayFecha+";";
            else
                NuevoRegistro = jugador+",no,"+Nfichas+HorayFecha+";";
        }

    }

    return 0;
}


void Registro(string NuevoRegistro){
    ofstream archivo;
    archivo.open("Registro.txt", std::ios::app);
    if(archivo.fail()){
        cout<<"No se pudo abrir el archivo";
        exit(1);
    }

    if(NuevoRegistro != " ")
    {
        archivo<<NuevoRegistro;
        archivo.close();
    }
}

char* HoraFecha(){
    char *registro;
    time_t tAct = time(NULL);
    asctime(localtime(&tAct));
    registro=asctime(localtime(&tAct));
    return registro;
}
