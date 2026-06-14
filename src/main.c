#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#include "juego.h"
#include "colores.h"

int main(){
    //Iniciamos en el menu inicial
    enum MODO_JUEGO modo_juego = MENU;

    //Para poder usar caracteres especiales
    #ifdef _WIN32
    UINT codificacion_original = GetConsoleOutputCP(); // Guardamos la codificación original para restaurarla al final
    SetConsoleOutputCP(CP_UTF8);
    #endif

    system("cls");

    //Menu inicial
    printf(CYAN "╔══════════════════════════════════╗   \n" RESET);
    printf(CYAN "║        " RESET); 
    printf("»»  LABERINTO ««          ");
    printf(CYAN "║\n" RESET);
    printf(CYAN "╠══════════════════════════════════╣   \n");
    printf("║      instrucciones insrucciones    ║\n");
    printf("║"); printf(VERDE " --- Presiona cualquier tecla ---" RESET); printf(" ║ \n");

    printf(CYAN "║      | Menu de ayuda = H |       ║\n" RESET);
    printf(CYAN "╚══════════════════════════════════╝   \n" RESET);

    char caracter = tolower(_getch());

    //Si el caracter presionado fue h o H, se muestra el menu de ayuda
    if (caracter == 'h'){
        menuAyuda();
    }
    
    system("cls");

    // Regresamos a la codificación original 
    #ifdef _WIN32
    SetConsoleOutputCP(codificacion_original);
    #endif

    //Comienza el juego con el nivel 1
    modo_juego = NIVEL_1;
    bool continuar = true;
    int num_Pasos;

    while(continuar && modo_juego != FINAL){
        num_Pasos = 0;

        //Si se retorno true, el jugador termino el juego, si retorno false, el jugador salio manualmente
        continuar = juego_mov(&modo_juego, &num_Pasos);
    }

    //Pantalla final
    final_Juego(modo_juego);

    printf("\nPresiona cualquier tecla para salir!");
    _getch();
    system("cls");

    return 0;
}