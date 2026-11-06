
/*****************************************************************************************************/
/*           Programación para mecatrónicos                                                          */
/* Nombre:    Omar David Guzmán Guerrero                                                             */
/* Matricula: 2024-1884                                                                              */
/* Correo:    20241884@itla.edu.do                                                                   */
/* Seccion:   Sabados                                                                                */
/* Practica:  main.c (segundo parcial)                                                               */
/* Fecha de entrega: 06/11/2026                                                                      */
/* Link Repositorio GitHub: https://github.com/dav366/PMC02-2024-1884                                */
/*****************************************************************************************************/

/* RETO 02: Desbordamiento de un depósito */

/* Librerías necesarias para la entrada/salida y manejo de cadenas. */
#include <stdio.h>
#include <string.h>
#include "reto.h"

/*
 * Lee un nombre completo desde la entrada estándar.
 * Controla su longitud para evitar almacenar nombres que superen
 * el tamaño máximo permitido por el arreglo.
 */
static int leer_nombre(char nombre[MAX_NOMBRE]) {
    int c;
    int longitud = 0;
    int excedido = 0;

    /* Ignora los espacios en blanco que aparecen antes del nombre. */
    do {
        c = getchar();
    } while (c != EOF && (c == ' ' || c == '\n' ||
             c == '\t' || c == '\r' || c == '\v' || c == '\f'));

    if (c == EOF) {
        return 0;
    }

    /* Lee los caracteres hasta encontrar un separador o el final de entrada. */
    while (c != EOF && c != ' ' && c != '\n' &&
           c != '\t' && c != '\r' && c != '\v' && c != '\f') {
        if (longitud < MAX_NOMBRE - 1) {
            nombre[longitud] = (char)c;
        } else {
            excedido = 1;
        }

        longitud++;
        c = getchar();
    }

    /* Rechaza nombres vacíos o que excedan la longitud permitida. */
    if (excedido || longitud == 0) {
        return -1;
    }

    nombre[longitud] = '\0';
    return 1;
}

/*
 * Verifica que el nombre esté compuesto únicamente por letras,
 * números o guion bajo, según las reglas del proyecto.
 */
static int nombre_valido(const char nombre[]) {
    int i;

    if (nombre[0] == '\0') {
        return 0;
    }

    for (i = 0; nombre[i] != '\0'; i++) {
        char c = nombre[i];

        if (!((c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') ||
              c == '_')) {
            return 0;
        }
    }

    return 1;
}

/*
 * Simula el comportamiento del depósito para una unidad.
 * Procesa cada muestra, actualiza el volumen y acumula en score
 * la cantidad que supera la capacidad máxima.
 * Finalmente determina el estado según el volumen alcanzado.
 */
int calcular(int muestras[], int m, int tipo, int p, int *estado) {
    int volumen = p;
    int score = 0;
    int balance;
    int nuevo;

    /* Procesa las muestras en el orden en que fueron recibidas. */
    for (int i = 0; i < m; i++) {
        balance = muestras[i] - 50;

        /* El tipo 1 invierte el efecto de cada muestra. */
        if (tipo == 1) {
            balance = -balance;
        }

        nuevo = volumen + balance;

        /* Controla el límite superior y acumula el desbordamiento. */
        if (nuevo > CAPACIDAD_MAXIMA) {
            score += nuevo - CAPACIDAD_MAXIMA;
            volumen = CAPACIDAD_MAXIMA;
        }
        /* Evita que el volumen del depósito sea negativo. */
        else if (nuevo < 0) {
            volumen = 0;
        }
        /* Si está dentro de los límites, conserva el nuevo volumen. */
        else {
            volumen = nuevo;
        }
    }

    /* El estado es 1 si el volumen final es al menos 50; de lo contrario, 0. */
    *estado = (volumen >= 50) ? 1 : 0;

    return score;
}

/*
 * Calcula recursivamente la suma de los scores de todas las unidades.
 * El caso base ocurre cuando no quedan registros por procesar.
 */
int total_rec(Registro registros[], int n) {
    if (n == 0) {
        return 0;
    }

    return registros[n - 1].score + total_rec(registros, n - 1);
}

/*
 * Ordena los registros mediante el método burbuja.
 * Prioriza el score más alto y utiliza el ID ascendente
 * como criterio secundario cuando dos scores son iguales.
 */
void ordenar(Registro registros[], int n) {
    Registro temporal;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (registros[j].score < registros[j + 1].score ||
                (registros[j].score == registros[j + 1].score &&
                 registros[j].id > registros[j + 1].id)) {

                /* Intercambia los registros cuando no cumplen el orden requerido. */
                temporal = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temporal;
            }
        }
    }
}

/*
 * Ordena una copia de los registros por ID ascendente.
 * Este orden es necesario para poder aplicar la búsqueda binaria.
 */
static void ordenar_por_id(Registro registros[], int n) {
    Registro temporal;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (registros[j].id > registros[j + 1].id) {
                temporal = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temporal;
            }
        }
    }
}

/*
 * Busca un ID dentro de un arreglo previamente ordenado.
 * Reduce el intervalo de búsqueda a la mitad en cada iteración.
 * Devuelve el score correspondiente o -1 si no encuentra el ID.
 */
int buscar(Registro registros[], int n, int id) {
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (registros[medio].id == id) {
            return registros[medio].score;
        }

        /* Si el ID buscado es mayor, continúa en la mitad derecha. */
        if (registros[medio].id < id) {
            izquierda = medio + 1;
        } else {
            /* Si es menor, continúa en la mitad izquierda. */
            derecha = medio - 1;
        }
    }

    return -1;
}
