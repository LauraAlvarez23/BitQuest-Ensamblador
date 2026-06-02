#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "colores.h"
#include <time.h>

#include "juego.h"

int main(){
    enum MODO_JUEGO modo_juego = MENU;

    srand(time(NULL));

    printf("=========== LABERINTO =========== \n");
    printf("instrucciones insrucciones instrucciones \n");
    printf("--- Presiona cualquier tecla --- \n -");

    printf(CYAN "Menu de ayuda = H \n" RESET);

    char caracter = tolower(_getch());

    if (caracter == 'h'){
        menuAyuda();
    }
    

    system("cls");

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