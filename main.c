#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "colores.h"
#include <time.h>

#include "juego.h"

int main(){
    enum MODO_JUEGO modo_juego = MENU;

    srand(time(NULL));

    int monedas = rand()%23;

    printf("=========== LABERINTO =========== \n");
    printf("instrucciones insrucciones instrucciones \n");
    printf("--- Presiona cualquier tecla --- \n -");
    _getch();
    modo_juego = NIVEL_1;

    system("cls");

    juego_mov(monedas, modo_juego);


    
    return 0;
}