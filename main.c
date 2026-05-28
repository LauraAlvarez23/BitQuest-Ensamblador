#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "colores.h"
#include <time.h>

#include "juego.h"

int main(){
    enum MODO_JUEGO modo_juego = MENU;

    srand(time(NULL));

    printf("=========== LABERINTO =========== \n");
    printf("instrucciones insrucciones instrucciones \n");
    printf("--- Presiona cualquier tecla --- \n -");
    _getch();

    system("cls");

    modo_juego = NIVEL_1;
    bool continuar = true;

    while(continuar && modo_juego != FINAL){
        continuar = juego_mov(&modo_juego);
    }

    if(modo_juego == FINAL){
        final_Juego();
    }else{
        printf("Juego terminado manualmente \n");
    }

    printf("Presiona cualquier tecla para salir!");
    _getch();
    system("cls");

    
    return 0;
}