#ifndef FUNCIONES_H
#define FUNCIONES_H

#define FILAS 60
#define COLUMNAS 60

#include <stdbool.h>

struct Coordenadas{
    int x;
    int y;
};

enum MODO_JUEGO {MENU, NIVEL_1, NIVEL_2, NIVEL_3, FINAL};


//Funciones C
void cursor();
bool juego_mov(enum MODO_JUEGO *modo_juego);
void llenar_matriz(char mat[][COLUMNAS],  int num_monedas, const char *nombre_archivo);
void imprimir_matriz(enum MODO_JUEGO modo_juego, char mat [][COLUMNAS], struct Coordenadas pos, int monedas_recolectadas);
void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov, bool *victoria, int *monedas_recolectadas);
void imprimirVictoria(enum MODO_JUEGO *modo_juego);
void final_Juego();

//Funciones NASM
int caracteresMapa(char mat[][COLUMNAS], int numCeldas, char c);
int validarMovimiento(char mat[][COLUMNAS], int nColumnas, int nueva_fila, int nueva_columna);
int puntaje(int nMonedas, int pasos, int niveles);
int detectarObjeto(char mat[][COLUMNAS], int nColumnas, int fila, int columna, char c);
int celdasLibres(char mat[][COLUMNAS], int numCeldas);

#endif