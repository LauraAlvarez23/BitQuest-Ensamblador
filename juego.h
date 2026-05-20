#ifndef FUNCIONES_H
#define FUNCIONES_H

#define FILAS 60
#define COLUMNAS 60

struct Coordenadas{
    int x;
    int y;
};

//Funciones C
void cursor();
void juego_mov(struct Coordenadas pos, int monedas);
void llenar_matriz(char mat[][COLUMNAS],  int monedas, const char *nombre_archivo);
void imprimir_matriz(char mat [][COLUMNAS], struct Coordenadas pos);
void movimiento(char mat[][COLUMNAS], struct Coordenadas *pos, char mov);

//Funciones NASM
int caracteresMapa(char mat[][COLUMNAS], int numCeldas, char c);
int validarMovimiento(char mat[][COLUMNAS], int nColumnas, int nueva_fila, int nueva_columna);
int puntaje(int nMonedas, int pasos, int niveles);
int detectarObjeto(char mat[][COLUMNAS], int nColumnas, int fila, int columna, char c);
int celdasLibres(char mat[][COLUMNAS], int numCeldas);

#endif