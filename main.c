#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "juego.h"

int main(){
    enum MODO_JUEGO modo_juego = MENU;

    srand(time(NULL));

    int monedas = rand()%23;

    char inicio;

    printf("=========== LABERINTO =========== \n");
    printf("instrucciones insrucciones instrucciones \n");
    printf("--- Presiona cualquier tecla --- \n -");
    inicio = _getch();
    modo_juego = NIVEL_1;

    system("cls");

    juego_mov(monedas, modo_juego);


    
    return 0;
}