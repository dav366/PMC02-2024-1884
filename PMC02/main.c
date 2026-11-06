
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
