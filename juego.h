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
void juego_mov(int monedas, enum MODO_JUEGO modo_juego);
void llenar_matriz(char mat[][COLUMNAS],  int monedas, const char *nombre_archivo);
void imprimir_matriz(char mat [][COLUMNAS], struct Coordenadas pos);
void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov, bool *victoria);
void imprimirVictoria(enum MODO_JUEGO *modo_juego);

//Funciones NASM
int caracteresMapa(char mat[][COLUMNAS], int numCeldas, char c);
int validarMovimiento(char mat[][COLUMNAS], int nColumnas, int nueva_fila, int nueva_columna);
int puntaje(int nMonedas, int pasos, int niveles);
int detectarObjeto(char mat[][COLUMNAS], int nColumnas, int fila, int columna, char c);
int celdasLibres(char mat[][COLUMNAS], int numCeldas);

#endif