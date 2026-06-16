#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
#include <ctype.h>

#include "colores.h"
#include "juego.h"


// VARIABLES GLOBALES 

// Limites para la vista de 20x20
static int limite_A = 0;    
static int limite_B = 19;

static int limite_C = 0;
static int limite_D = 19;

// Datos de monedas y pasos
static int t_monedas;
static int total_Monedas_Recolectadas = 0;
static int total_Pasos = 0;
static int totalFinal_Monedas = 0;

static bool tiene_llave;

// Funcion que imprime un menu con informacion del juego
void menuAyuda(){
    system("cls");

    /*  Se muestra un menu de ayuda, en el se indican las teclas para el movimiento del jugador, 
        junto con los caracteres importantes que se deben conocer para poder jugar                  */

    printf(MORADO "========== TECLAS ========== \n" RESET);
    printf(ROJO "W o w " RESET); printf("-> Arriba \n");
    printf(ROJO "S o s " RESET); printf("-> Abajo \n");
    printf(ROJO "A o a " RESET); printf("-> Izquierda \n");
    printf(ROJO "D o d " RESET); printf("-> Derecho \n");
    printf(BERRY "Q o q " RESET); printf("-> Salir \n");

    printf(MORADO "\n========= CARACTERES ========= \n" RESET);
    printf(AZULREY "¥ " RESET); printf("-> Tu \n");
    printf(AMARILLO "© " RESET); printf("-> Moneda \n");
    printf(". -> Camino \n");
    printf("█ -> Pared \n");   
    printf("░   -> Puerta \n");
    printf(COLORllAVE "¤ " RESET); printf("-> LLave\n");
    printf("(OJO. Las llaves no se acumulan)\n");
    printf(AMARILLO "\t  SUERTE!\n" RESET);
    printf(GRIS "--- Presiona cualquier tecla para salir! ---" RESET);

    _getch();
    system("cls");

}


// Funcion para acomodar el cursor y que la pantalla no parpadee 
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

// Funcion que permite usar los colores de colores.h
void colores_ansi(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if(GetConsoleMode(hOut, &dwMode)){
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
}

// Llena la matriz con el contenido del archivo correspondiente  
void llenar_matriz(char mat[][COLUMNAS], const char *nombre_archivo){
    FILE *archivo = fopen(nombre_archivo, "r"); //Abre el archivo en modo de lectura
    if(archivo == NULL){
        printf("Error. No se pudo abrir el archivo del mapa. \n");
        return;
    }

    //Va metiendo cada caracter que lee a la matriz
    for(int i=0; i<FILAS; i++){
        for (int j=0; j<COLUMNAS; j++){
            fscanf(archivo, " %c", &mat[i][j]);
        }
    }
    fclose(archivo);

    //Generacion aleatoria de monedas
    srand(time(NULL));

    /* Recorre la matriz, por cada camino libre . , se genera un numero aleatorio de 1 a 100, 
       si este numero es igual a 3, se coloca una moneda en la ubicacion  */ 
    for(int i=0; i<FILAS; i++){
        for(int j=0; j<COLUMNAS; j++){
            if(detectarObjeto(mat, COLUMNAS, i, j, '.') == 1){
                int aleatorio = (rand()%100) + 1;
                if(aleatorio == 3){
                    mat[i][j] = 184;
                }
            }
        }
    }
}

// Imprime la matriz 
void imprimir_matriz(enum MODO_JUEGO modo_juego, char mat [][COLUMNAS], struct Coordenadas pos, int monedas_Recolectadas, int num_Pasos){
    cursor();

    //Indica en que nivel se encuentra el jugador
    switch(modo_juego){
        case NIVEL_1: 
            printf(ROJO "\n====== NIVEL 1 ======\n" RESET);
            break;

        case NIVEL_2:
            printf(ROJO "\n====== NIVEL 2 ======\n" RESET);
            break;

        case NIVEL_3:
            printf(ROJO "\n====== NIVEL 3 ======\n" RESET);
            break;

        case FINAL: 
            final_Juego(modo_juego);
            break;
        
        default: break;
    }

    //Informacion del juego 
    printf(GRIS "Salir con tecla 'q' \n" RESET);
    printf(AZULOSCURO "MONEDAS: " RESET "%d/%d\n", monedas_Recolectadas, t_monedas);
    printf(AZULREY "LLAVE: " RESET); (tiene_llave) ? printf("* \n") : printf(" \n");
    printf(AZUL "PASOS: " RESET "%d \n", num_Pasos);
    printf("Posicion: (%d, %d) \n", pos.y, pos.x);
    printf("\n");
    
    //Imprime la matriz, pero solo la parte de 20x20 que le indican los limites
    //Depende de que caracter se encuentre en la matriz, imprime un caracter especias ASCII
     for(int i=limite_A; i<=limite_B; i++){
        for (int j=limite_C; j<=limite_D; j++){
            if(detectarObjeto(mat, COLUMNAS, i, j, '#') == 1){
                printf("%c%c", 219, 219);
            }else if(detectarObjeto(mat, COLUMNAS, i, j, 184) == 1){                                               
                printf(AMARILLO "%c " RESET, mat[i][j]);
            }else if(detectarObjeto(mat, COLUMNAS, i, j, 190) == 1){                                                 
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

//Validacion de movimiento
void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov, bool *victoria, int *monedas_Recolectadas, int *num_Pasos){
    switch (mov){

        /*  Toma en cuenta que tecla se presiono, de acuerdo a esta, se calcula la posible nueva posicion y se realizan las primeras 3 validaciones:
            -> Que la nueva posicion no sea ninguno de los bordes ni se pase de estos
            -> Que no se intente mover a donde haya una pared (con validarMovimiento)
            -> Que no intente moverse a donde haya una puerta 
        */
        case 'w': 
            if(pos->x-1 > 0 && (validarMovimiento(mat, COLUMNAS, pos->x-1, pos->y)) != 1 && (detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'D')) != 1){
                //Si la nueva posicion es la salida, marca la bandera correspondiente como true
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'E')) == 1){
                    *victoria = true;
                }

                //Si la nueva posicion es una moneda, incrementan las monedas recolectadas
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 184)) == 1){
                    (*monedas_Recolectadas)++;
                }

                //Si la nueva posicion es una llave, cambia la bandera correspondiente, para poder abrir puertas
                if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'K')) == 1){
                    tiene_llave = true;
                }

                //Una vez todo esto es evaluado, se actualiza la posicion y se incrementa el numero de pasos
                pos->x--;
                (*num_Pasos)++;

                //Si la nueva posicion se sale del limite o es igual a este, se actualizan los limites necesarios 
                if(pos->x <= limite_A && limite_A > 0){
                    limite_A--;
                    limite_B--;
                }
                
            //Si la nueva posicion es una puerta y se tiene una llave, se puede realizar el movimiento como se hizo anteriormente
            }else if((detectarObjeto(mat, COLUMNAS, pos->x-1, pos->y, 'D')) == 1 && tiene_llave){
                pos->x--;
                (*num_Pasos)++;
                if(pos->x <= limite_A && limite_A > 0){
                    limite_A--;
                    limite_B--;
                }
                tiene_llave = false;    //Se gasto la llave
            }
            break;

        //Este proceso se repite con cada posible movimiento
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

        default: break;
        break;
    }
}

//La columna del programa 
bool juego_mov(enum MODO_JUEGO *modo_juego, int *num_Pasos){
    colores_ansi();

    //Se crea la matriz que se estara usando
    char laberinto[FILAS][COLUMNAS];

    //Inicializacion de variables
    bool victoria = false;

    int monedasRecolectadas = 0;
    t_monedas = 0;

    limite_A = 0;
    limite_B = 19;
    
    limite_C = 0;
    limite_D = 19;

    tiene_llave = false;

    struct Coordenadas pos = {1,1}; //Coordenadas donde se coloca al jugador al comienzo de cada nivel

    /*  De acuerdo con el nivel en el que se encuentre el jugador, se manda llenar la matriz con el mapa correspondiente. 
        Se obtiene el total de monedas del mapa
    */
    if(*modo_juego == NIVEL_1){
        llenar_matriz(laberinto, "mapa1.txt");
        t_monedas = caracteresMapa(laberinto, FILAS*COLUMNAS, 184);
    }else if(*modo_juego == NIVEL_2){
        llenar_matriz(laberinto, "mapa2.txt");
        t_monedas = caracteresMapa(laberinto, FILAS*COLUMNAS, 184);
    }else if(*modo_juego == NIVEL_3){
         llenar_matriz(laberinto, "mapa3.txt");
         t_monedas = caracteresMapa(laberinto, FILAS*COLUMNAS, 184);
    }

    //Se hace la sumatoria del total de monedas de la partida (de los tres mapas)
    totalFinal_Monedas += t_monedas;    


    //Se obtiene el total de celdas libres 
    int celdas_Libres = celdasLibres(laberinto, FILAS*COLUMNAS);

    //Variable para imprimer caracter despues de un movimiento
    char objeto_bajo_jugador = '.';
    
    //Se coloca el caracter del jugador y se imprime el mapa
    laberinto[pos.x][pos.y] = 190;
    imprimir_matriz(*modo_juego, laberinto, pos, monedasRecolectadas, *num_Pasos);

    while(1){
        //Si se ha presionado una tecla, la obtiene y la convierte en minusculas para que se acepte cualquier variante de w, a, s, d
        if(_kbhit()){
            char tecla = _getch();

            bool tenia_llave_antes = false;
            bool se_movio = false;

            tecla = tolower(tecla);

            if(tecla == 'w' || tecla == 's' || tecla == 'a' || tecla == 'd'){
                //Antes del movimiento, va cambiando la posicion actual por un caracter (que se definira mas abajo)
                laberinto[pos.x][pos.y] = objeto_bajo_jugador;

                tenia_llave_antes = tiene_llave;

                //Valida el movimiento e indica que se presiono alguna tecla de movimiento (se_movio)
                movimiento(laberinto, &pos, tecla, &victoria, &monedasRecolectadas, num_Pasos);
                se_movio = true;

                //Si se llegó a la salida, se imprime el resumen del nivel
                if(victoria){
                    imprimirVictoria(modo_juego, monedasRecolectadas, t_monedas, *num_Pasos, celdas_Libres);
                    return true;
                }
            }else{
                /*  Si se presiona la tecla 'q', se saldra manualmente de la partida, desde este punto se calculan los datos 
                    correspondientes al resumen de la partida */
                if(tecla == 'q'){
                    total_Pasos += *num_Pasos;
                    total_Monedas_Recolectadas += monedasRecolectadas;
                    return false;
                }
            }

            if(se_movio){
                //Guarda el caracter que se encuentra en la posicion actual
                objeto_bajo_jugador = laberinto[pos.x][pos.y];

                //Si este objeto es una moneda, se cambia por un caracter de camino libre .
                if(objeto_bajo_jugador == (char)184){
                    objeto_bajo_jugador = '.';
                
                /* Si el objeto es una llave y NO se tenia una llave, se cambia por un camino,
                por lo tanto, si SI se tenia una llave, esta se deja intacta (sin recolectar pero sin desaparecerla)*/
                }else if(objeto_bajo_jugador == 'K'){
                    if(!tenia_llave_antes){
                        objeto_bajo_jugador = '.';
                    }
                //Lo mismo del primer caso pasa si fue una puerta el caracter de la posicion actual
                }else if(objeto_bajo_jugador == 'D'){
                    objeto_bajo_jugador = '.';
                }
                laberinto[pos.x][pos.y] = 190;  //Se posiciona al jugador y se imprime la matriz actualizada
                imprimir_matriz(*modo_juego, laberinto, pos, monedasRecolectadas, *num_Pasos);    
            }            
        }
        
    }
}

//Resumen del nivel
void imprimirVictoria(enum MODO_JUEGO *modo_juego, int monedasRecolectadas, int t_monedas, int num_Pasos, int celdas_Libres){
    system("cls");

    //Indica que nivel se acaba de superar
    printf(AMARILLO "====== VICTORIA ======\n" RESET);
    printf("Felicidades! Has superado el nivel ");

    //Datos para el resumen de la partida
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
    //Se imprime la informacion del nivel 
    
    //printf(AMARILLO "MONEDAS: " RESET "%d/%d \n", monedasRecolectadas, t_monedas);
    //printf(BERRY "PASOS: " RESET "%d \n", num_Pasos);
    //printf("CELDAS LIBRES: %d \n", celdas_Libres);

    printf("| " AMARILLO "MONEDAS: " RESET "%d/%d " "%*s\n", monedasRecolectadas, t_monedas, 10, "|");
    printf("| " BERRY "PASOS: " RESET "%-14d |\n", num_Pasos);
    printf("| " RESET  "CELDAS LIBRES: %-6d |\n",  celdas_Libres);
    printf("\nPara continuar, presione cualquier tecla!");
    _getch();
    system("cls");
}

//Resumen de la partida
void final_Juego(enum MODO_JUEGO modo_juego){
    system("cls");

    int total_puntaje = 0; 

    printf(AZUL "*============================================*\n" RESET);
    if(modo_juego == FINAL){
        printf(AZUL "||" AMARILLO "   FELICIDADES! HAS COMPLETADO EL JUEGO    " AZUL "||\n" RESET);
        printf("||          yea :D               ||\n");
    }else{
         printf(CYAN "||" GRIS "     * Juego terminado manualmente *" CYAN "      || \n" RESET);
    }
    printf(AZUL "*============================================*\n" RESET);
    
    printf(AZUL "._.__.__.__.__.___.___.___._.\n" RESET);
    //Informacion importante de la partida
    printf(RESET "| "AMARILLO "MONEDAS TOTALES: " RESET "%d/%d " "%*s\n", total_Monedas_Recolectadas, totalFinal_Monedas, 5, "|"); 
    printf(RESET "| "AMARILLO "PASOS TOTALES: " RESET "%-10d |\n", total_Pasos);
    printf(RESET "| " NARANJA "NIVELES COMPLETADOS: " RESET);

    //Se calcula el puntaje final
    switch(modo_juego){
        case NIVEL_1: printf("%-4d |\n", 0); 
                        total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 0);
                        break;
        case NIVEL_2: printf("%-4d |\n", 1); 
                        total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 1);
                        break;
        case NIVEL_3: printf("%-4d |\n", 2); 
                        total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 2);
                        break;
        case FINAL: printf("%-4d |\n", 3); 
                    total_puntaje = puntaje(total_Monedas_Recolectadas, total_Pasos, 3);
                    break;
        default:
    }

   printf(RESET "| " BERRY "PUNTAJE FINAL: " RESET "%-10d |\n", total_puntaje); 

    printf(AZUL "._.__.__.__.__.___.___.___._.\n" RESET);
}