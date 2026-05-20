#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "juego.h"

static int limite_A = 0;
static int limite_B = 19;

static int limite_C = 0;
static int limite_D = 19;

void cursor(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);
}


void llenar_matriz(char mat[][COLUMNAS], int monedas, const char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r");
    if(archivo == NULL){
        printf("Error. No se pudo abrir el archivo del mapa. \n");
        return;
    }

    for(int i=0; i<FILAS; i++){
        for (int j=0; j<COLUMNAS; j++){
            fscanf(archivo, " %c", &mat[i][j]);
        }
    }
    fclose(archivo);

    int i = 0;
    struct Coordenadas punto_Moneda;
    while(i < monedas){
        punto_Moneda.x = rand()%58;
        punto_Moneda.y = rand()%58;

        if(validarMovimiento(mat, 60, punto_Moneda.x, punto_Moneda.y) != 1){
            mat[punto_Moneda.x][punto_Moneda.y] = 'M';
            i++;
        }
    }
}


void imprimir_matriz(char mat [][COLUMNAS], struct Coordenadas pos){
    cursor();

    printf("Salir con tecla 'q' \n");
    printf("Posicion: (%d, %d)\n", pos.y, pos.x);
    printf("\n");
    

     for(int i=limite_A; i<=limite_B; i++){
        for (int j=limite_C; j<=limite_D; j++){
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov){
    switch (mov){
        case 'w': 
            if(pos->x-1 > 0 && (validarMovimiento(mat, 60, pos->x-1, pos->y)) != 1){
                pos->x--;
                if(pos->x <= limite_A && limite_A > 0){
                    limite_A--;
                    limite_B--;
                }
            }
            break;

        case 's':
            if(pos->x+1 < FILAS  && (validarMovimiento(mat, 60, pos->x+1, pos->y)) != 1){
                pos->x++;
                if(pos->x >= limite_B && limite_B < FILAS -1){
                    limite_A++;
                    limite_B++;

                }
            }
            break;

        case 'a':
            if(pos->y-1 > 0  && (validarMovimiento(mat, 60, pos->x, pos->y-1)) != 1){
                pos->y--;
                if(pos->y <= limite_C && limite_C > 0){
                    limite_C--;
                    limite_D--;
                }
            }
            break;


        case 'd': 
            if(pos->y+1 < COLUMNAS-1  && (validarMovimiento(mat, 60, pos->x, pos->y+1)) != 1){
                pos->y++;
                if(pos->y >= limite_D && limite_D < COLUMNAS -1){
                    limite_C++;
                    limite_D++;
                }
            }
            break;

        default: printf("Tecla no permitida \n");
        break;
    }
}

void juego_mov(struct Coordenadas pos, int monedas){
    char laberinto[FILAS][COLUMNAS];

    llenar_matriz(laberinto, monedas, "mapa2.txt");

    laberinto[pos.x][pos.y] = 190;

    imprimir_matriz(laberinto, pos);

    while(1){
        if(_kbhit()){
            char tecla = _getch();

            if(tecla == 'w' || tecla == 's' || tecla == 'a' || tecla == 'd'){
                laberinto[pos.x][pos.y] = '.';
                movimiento(laberinto, &pos, tecla);
                
            }else{
                if(tecla == 'q'){
                    break;
                }
            }

            laberinto[pos.x][pos.y] = 190;
            imprimir_matriz(laberinto, pos);
        }
        
    }



}