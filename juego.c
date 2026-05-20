#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
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

        if(validarMovimiento(mat, 60, punto_Moneda.y, punto_Moneda.x) != 1){
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

void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov, bool *victoria){
    switch (mov){
        case 'w': 
            if(pos->x-1 > 0 && (validarMovimiento(mat, 60, pos->x-1, pos->y)) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'E')) == 1){
                    *victoria = true;
                }
                pos->x--;
                if(pos->x <= limite_A && limite_A > 0){
                    limite_A--;
                    limite_B--;
                }
                
            }
            break;

        case 's':
            if(pos->x+1 < FILAS  && (validarMovimiento(mat, 60, pos->x+1, pos->y)) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x+1, pos->y, 'E')) == 1){
                    *victoria = true;
                }
                pos->x++;
                if(pos->x >= limite_B && limite_B < FILAS -1){
                    limite_A++;
                    limite_B++;
                }
                
            }
            break;

        case 'a':
            if(pos->y-1 > 0  && (validarMovimiento(mat, 60, pos->x, pos->y-1)) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y-1, 'E')) == 1){
                    *victoria = true;
                }
                pos->y--;
                if(pos->y <= limite_C && limite_C > 0){
                    limite_C--;
                    limite_D--;
                }
            }
            break;


        case 'd': 
            if(pos->y+1 < COLUMNAS-1  && (validarMovimiento(mat, 60, pos->x, pos->y+1)) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y+1, 'E')) == 1){
                    *victoria = true;
                }
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

void juego_mov(int monedas, enum MODO_JUEGO modo_juego){
    char laberinto[FILAS][COLUMNAS];
    bool victoria = false;

    limite_A = 0;
    limite_B = 19;
    
    limite_C = 0;
    limite_D = 19;

    struct Coordenadas pos = {1,1};

    if(modo_juego == NIVEL_1){
        llenar_matriz(laberinto, monedas, "mapa1.txt");
    }else if(modo_juego == NIVEL_2){
        llenar_matriz(laberinto, monedas, "mapa2.txt");
    }else if(modo_juego == NIVEL_3){
         llenar_matriz(laberinto, monedas, "mapa3.txt");
    }
    
    laberinto[pos.x][pos.y] = 190;

    imprimir_matriz(laberinto, pos);

    while(1){
        if(_kbhit()){
            char tecla = _getch();

            if(tecla == 'w' || tecla == 's' || tecla == 'a' || tecla == 'd'){
                laberinto[pos.x][pos.y] = '.';

                movimiento(laberinto, &pos, tecla, &victoria);

                if(victoria){
                    imprimirVictoria(&modo_juego);
                    break;
                }
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

void imprimirVictoria(enum MODO_JUEGO *modo_juego){
    char continuar;
    system("cls");
    printf("=== VICTORIA ===\n");
    printf("Felicidades! Has superado el nivel ");

    switch(*modo_juego){
        case NIVEL_1: 
            printf("1\n");
            *modo_juego = NIVEL_2;
            break;

        case NIVEL_2:
            printf("2\n");
            *modo_juego = NIVEL_3;
            break;

        case NIVEL_3:
            printf("3\n");
            *modo_juego = FINAL;
            break;
    }

    printf("Para continuar, presione cualquier tecla!");
    continuar = _getch();
    system("cls");
    if(*modo_juego != FINAL){
        juego_mov(34, *modo_juego);
    }
    
}