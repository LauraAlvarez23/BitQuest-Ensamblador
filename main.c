#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "colores.h"
#include <time.h>
#include <windows.h>

#include "juego.h"

int main(){
    enum MODO_JUEGO modo_juego = MENU;

    #ifdef _WIN32
    UINT codificacion_original = GetConsoleOutputCP(); // Guardamos la codificación original para restaurarla al final
    SetConsoleOutputCP(CP_UTF8);
    #endif

    srand(time(NULL));

    printf(CYAN "╔══════════════════════════════════╗   \n" RESET);
    printf(CYAN "║        »»  LABERINTO ««          ║  \n" RESET);
    printf(CYAN "╠══════════════════════════════════╣   \n");
    printf("║      instrucciones insrucciones   %c \n");
    printf("║"); printf(VERDE " --- Presiona cualquier tecla ---" RESET); printf(" ║ \n");

    printf(CYAN "║      | Menu de ayuda = H |       ║\n" RESET);
    printf(CYAN "╚══════════════════════════════════╝   \n" RESET);

    char caracter = tolower(_getch());

    if (caracter == 'h'){
        menuAyuda();
    }
    
    system("cls");

    // Regresamos a la codificación original 
    #ifdef _WIN32
    SetConsoleOutputCP(codificacion_original);
    #endif

    modo_juego = NIVEL_1;
    bool continuar = true;
    int num_Pasos;

    while(continuar && modo_juego != FINAL){
        num_Pasos = 0;
        continuar = juego_mov(&modo_juego, &num_Pasos);
    }

    final_Juego(modo_juego);

    printf("\nPresiona cualquier tecla para salir!");
    _getch();
    system("cls");

    return 0;
}