#ifndef RETO_H
#define RETO_H

/* Constantes del programa */
#define MAX_UNIDADES 20
#define MAX_MUESTRAS 8
#define MAX_NOMBRE 16
#define CAPACIDAD_MAXIMA 100

/* Configuracion de cada unidad */
typedef struct {
    int tipo;
    int p;
} Configuracion;

/* Registro de cada unidad */
typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    Configuracion config;
    int score;
    int estado;
} Registro;

/* Prototipos de las funciones */
int calcular(int muestras[], int m, int tipo, int p, int *estado);

int total_rec(Registro registros[], int n);

void ordenar(Registro registros[], int n);

int buscar(Registro registros[], int n, int id);

#endif
