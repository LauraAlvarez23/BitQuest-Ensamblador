#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "juego.h"

int main(){
    struct Coordenadas pos;
    pos.x = 1;
    pos.y = 1;

    srand(time(NULL));

    int monedas = rand()%23;

    char inicio;

    printf("=========== LABERINTO =========== \n");
    printf("instrucciones insrucciones instrucciones \n");
    printf("--- Presiona cualquier tecla --- \n -");
    inicio = _getch();
    

    system("cls");

    juego_mov(pos, monedas);


    
    return 0;
}