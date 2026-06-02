#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
#include <ctype.h>
#include "colores.h"
#include "juego.h"

static int t_monedas;

static int limite_A = 0;
static int limite_B = 19;

static int limite_C = 0;
static int limite_D = 19;

static int total_Monedas_Recolectadas = 0;
static int total_Pasos = 0;
static int total_Monedas = 0;

static bool tiene_llave;


void menuAyuda(){
    system("cls");

    printf(MORADO " ========== TECLAS ========== \n" RESET);
    printf(ROJO "W o w " RESET); printf("-> Arriba \n");
    printf(ROJO "S o s " RESET); printf("-> Abajo \n");
    printf(ROJO "A o a " RESET); printf("-> Izquierda \n");
    printf(ROJO "D o d " RESET); printf("-> Derecho \n");
    printf(BERRY "Q o q " RESET); printf("-> Salir \n");

    printf(MORADO "\n========= CARACTERES ========= \n" RESET);
    printf(AZULREY "%c " RESET, 190); printf("-> Tu \n");
    printf(AMARILLO "%c " RESET, 184); printf("-> Moneda \n");
    printf("%c -> Camino \n", '.');
    printf("%c -> Pared \n", 219);
    printf("%c -> Puerta \n", 176);
    printf(COLORllAVE "%c " RESET, 207); printf("-> LLave\n");
    printf("(OJO. Las llaves no se acumulan)\n");
    printf(AMARILLO "\t  SUERTE!\n" RESET);
    printf(GRIS "--- Presiona cualquier tecla para salir! ---" RESET);
    _getch();
    system("cls");

}


void cursor(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);

    //printf("\033[H\033[J");
}

void colores_ansi(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if(GetConsoleMode(hOut, &dwMode)){
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
}


void llenar_matriz(char mat[][COLUMNAS], int num_monedas, const char *nombre_archivo){
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
    while(i < num_monedas){
        punto_Moneda.x = (rand()%58) + 1;
        punto_Moneda.y = (rand()%58) + 1;

        if(validarMovimiento(mat, 60, punto_Moneda.x, punto_Moneda.y) != 1 && detectarObjeto(mat, COLUMNAS, punto_Moneda.x, punto_Moneda.y, '.') == 1){
            mat[punto_Moneda.x][punto_Moneda.y] = 184;
            i++;
        }
    }
}


void imprimir_matriz(enum MODO_JUEGO modo_juego, char mat [][COLUMNAS], struct Coordenadas pos, int monedas_Recolectadas, int num_Pasos){
    cursor();

    switch(modo_juego){
        case NIVEL_1: 
            printf("\n====== NIVEL 1 ======\n");
            break;

        case NIVEL_2:
            printf("\n====== NIVEL 2 ======\n");
            break;

        case NIVEL_3:
            printf("\n====== NIVEL 3 ======\n");
            break;

        case FINAL: 
            final_Juego(modo_juego);
            break;
        
        default: break;
    }


    printf(GRIS "Salir con tecla 'q' \n" RESET);
    printf("MONEDAS: %d/%d\n", monedas_Recolectadas, t_monedas);
    printf("LLAVE: "); (tiene_llave) ? printf("* \n") : printf(" \n");
    printf("PASOS: %d \n", num_Pasos);
    printf("Posicion: (%d, %d)  (opcional)\n", pos.y, pos.x);
    printf("\n");
    

     for(int i=limite_A; i<=limite_B; i++){
        for (int j=limite_C; j<=limite_D; j++){
            if(detectarObjeto(mat, COLUMNAS, i, j, '#') == 1){
                printf("%c%c", 219, 219);
            }else if(detectarObjeto(mat, COLUMNAS, i, j, 184) == 1){                                                 //(unsigned char)mat[i][j] == 184
                printf(AMARILLO "%c " RESET, mat[i][j]);
            }else if(detectarObjeto(mat, COLUMNAS, i, j, 190) == 1){                                                 //(unsigned char)mat[i][j] == 190
                printf(AZULREY "%c " RESET, mat[i][j]);
            }else if(detectarObjeto(mat, COLUMNAS, i, j, 'D') == 1){
                printf("%c%c", 176, 176);
            }else if(detectarObjeto(mat, COLUMNAS, i, j, 'K') == 1){
                printf(COLORllAVE "%c " RESET, 207);
            }else{
                printf("%c ", mat[i][j]);
            }
        }
        printf("\n");
    }
}

void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov, bool *victoria, int *monedas_Recolectadas, int *num_Pasos){
    switch (mov){
        case 'w': 
            if(pos->x-1 > 0 && (validarMovimiento(mat, COLUMNAS, pos->x-1, pos->y)) != 1 && (detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'D')) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'E')) == 1){
                    *victoria = true;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 184)) == 1){
                    (*monedas_Recolectadas)++;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'K')) == 1){
                    tiene_llave = true;
                }
                pos->x--;
                (*num_Pasos)++;
                if(pos->x <= limite_A && limite_A > 0){
                    limite_A--;
                    limite_B--;
                }
                
            }else if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'D')) == 1 && tiene_llave){
                pos->x--;
                (*num_Pasos)++;
                if(pos->x <= limite_A && limite_A > 0){
                    limite_A--;
                    limite_B--;
                }
                tiene_llave = false;
            }
            break;

        case 's':
            if(pos->x+1 < FILAS  && (validarMovimiento(mat, COLUMNAS, pos->x+1, pos->y)) != 1 && (detectarObjeto(mat, COLUMNAS, pos->x+1, pos->y, 'D')) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x+1, pos->y, 'E')) == 1){
                    *victoria = true;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x+1, pos->y, 184)) == 1){
                    (*monedas_Recolectadas)++;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x+1, pos->y, 'K')) == 1){
                    tiene_llave = true;
                }
                pos->x++;
                (*num_Pasos)++;
                if(pos->x >= limite_B && limite_B < FILAS -1){
                    limite_A++;
                    limite_B++;
                }
                
            }else if((detectarObjeto(mat, COLUMNAS, pos->x+1, pos->y, 'D')) == 1 && tiene_llave){
                pos->x++;
                (*num_Pasos)++;
                if(pos->x >= limite_B && limite_B < FILAS -1){
                    limite_A++;
                    limite_B++;
                }
                tiene_llave = false;
            }
            break;

        case 'a':
            if(pos->y-1 > 0  && (validarMovimiento(mat, COLUMNAS, pos->x, pos->y-1)) != 1 && (detectarObjeto(mat, COLUMNAS, pos->x, pos->y-1, 'D')) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y-1, 'E')) == 1){
                    *victoria = true;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y-1, 184)) == 1){
                    (*monedas_Recolectadas)++;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y-1, 'K')) == 1){
                    tiene_llave = true;
                }
                pos->y--;
                (*num_Pasos)++;
                if(pos->y <= limite_C && limite_C > 0){
                    limite_C--;
                    limite_D--;
                }
            }else if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y-1, 'D')) == 1 && tiene_llave){
                pos->y--;
                (*num_Pasos)++;
                if(pos->y <= limite_C && limite_C > 0){
                    limite_C--;
                    limite_D--;
                }
                tiene_llave = false;
            }
            break;


        case 'd': 
            if(pos->y+1 < COLUMNAS-1  && (validarMovimiento(mat, COLUMNAS, pos->x, pos->y+1)) != 1 && (detectarObjeto(mat, COLUMNAS, pos->x, pos->y+1, 'D')) != 1){
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y+1, 'E')) == 1){
                    *victoria = true;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y+1, 184)) == 1){
                    (*monedas_Recolectadas)++;
                }
                if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y+1, 'K')) == 1){
                    tiene_llave = true;
                }
                pos->y++;
                (*num_Pasos)++;
                if(pos->y >= limite_D && limite_D < COLUMNAS -1){
                    limite_C++;
                    limite_D++;
                }
            }else if((detectarObjeto(mat, COLUMNAS, pos->x, pos->y+1, 'D')) == 1 && tiene_llave){
                pos->y++;
                (*num_Pasos)++;
                if(pos->y >= limite_D && limite_D < COLUMNAS -1){
                    limite_C++;
                    limite_D++;
                }
                tiene_llave = false;
            }
            break;

        default: printf("Tecla no permitida \n");
        break;
    }
}

bool juego_mov(enum MODO_JUEGO *modo_juego, int *num_Pasos){
    colores_ansi();

    char laberinto[FILAS][COLUMNAS];
    bool victoria = false;


    int monedasRecolectadas = 0;
    int totalMonedas = 23;

    t_monedas = 0;

    limite_A = 0;
    limite_B = 19;
    
    limite_C = 0;
    limite_D = 19;

    tiene_llave = false;

    struct Coordenadas pos = {1,1};

    if(*modo_juego == NIVEL_1){
        llenar_matriz(laberinto, totalMonedas, "mapa1.txt");
        t_monedas = caracteresMapa(laberinto, FILAS*COLUMNAS, 184);
    }else if(*modo_juego == NIVEL_2){
        llenar_matriz(laberinto, totalMonedas, "mapa2.txt");
        t_monedas = caracteresMapa(laberinto, FILAS*COLUMNAS, 184);
    }else if(*modo_juego == NIVEL_3){
         llenar_matriz(laberinto, totalMonedas, "mapa3.txt");
         t_monedas = caracteresMapa(laberinto, FILAS*COLUMNAS, 184);
    }
    total_Monedas += t_monedas;


    int celdas_Libres = celdasLibres(laberinto, FILAS*COLUMNAS);
    
    laberinto[pos.x][pos.y] = 190;

    imprimir_matriz(*modo_juego, laberinto, pos, monedasRecolectadas, *num_Pasos);

    while(1){
        if(_kbhit()){
            char tecla = _getch();

            bool se_movio = false;

            tecla = tolower(tecla);

            if(tecla == 'w' || tecla == 's' || tecla == 'a' || tecla == 'd'){
                laberinto[pos.x][pos.y] = '.';

                movimiento(laberinto, &pos, tecla, &victoria, &monedasRecolectadas, num_Pasos);
                se_movio = true;

                if(victoria){
                    imprimirVictoria(modo_juego, monedasRecolectadas, t_monedas, *num_Pasos, celdas_Libres);
                    return true;
                }
            }else{
                if(tecla == 'q'){
                    total_Pasos += *num_Pasos;
                    total_Monedas_Recolectadas += monedasRecolectadas;
                    return false;
                }
            }

            if(se_movio){
                laberinto[pos.x][pos.y] = 190;
                imprimir_matriz(*modo_juego, laberinto, pos, monedasRecolectadas, *num_Pasos);    
            }            
        }
        
    }
}

void imprimirVictoria(enum MODO_JUEGO *modo_juego, int monedasRecolectadas, int t_monedas, int num_Pasos, int celdas_Libres){
    system("cls");
    printf("=== VICTORIA ===\n");
    printf("Felicidades! Has superado el nivel ");

    total_Pasos += num_Pasos;
    total_Monedas_Recolectadas += monedasRecolectadas;

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

        case FINAL: 
            final_Juego(*modo_juego);
            break;

        
        default: break;
    }
    printf("MONEDAS: %d/%d \n", monedasRecolectadas, t_monedas);
    printf("\nCELDAS LIBRES: %d \n", celdas_Libres);
    printf("PASOS: %d \n", num_Pasos);

    printf("Para continuar, presione cualquier tecla!");
    _getch();
    system("cls");
}


void final_Juego(enum MODO_JUEGO modo_juego){
    system("cls");

    int total_puntaje = 0; 

    printf("\n===========================================\n");
    if(modo_juego == FINAL){
        printf("FELICIDADES! HAS COMPLETADO EL JUEGO \n");
        printf("yea \n");
    }else{
         printf("Juego terminado manualmente \n");
    }
    
    printf(AMARILLO "MONEDAS TOTALES: " RESET); printf("%d/%d \n", total_Monedas_Recolectadas, total_Monedas);
    printf(AMARILLO "PASOS TOTALES: " RESET); printf("%d \n", total_Pasos);
    printf("NIVELES COMPLETADOS: ");

    switch(modo_juego){
        case NIVEL_1: printf("0"); 
                        total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 0);
                        break;
        case NIVEL_2: printf("1"); 
                        total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 1);
                        break;
        case NIVEL_3: printf("2"); 
                        total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 2);
                        break;
        case FINAL: printf("3"); 
                    total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 3);
                    break;
        default:
    }
    printf("\n");

    printf("PUNTAJE FINAL: "); printf("%d", total_puntaje);

     printf("\n===========================================\n");
}