
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

/*
 * Función principal:
 * 1. Lee y valida los datos de entrada.
 * 2. Calcula los resultados de cada unidad.
 * 3. Obtiene el score total.
 * 4. Ordena copias para generar ORDER y FIND.
 * 5. Imprime los resultados en el formato solicitado.
 */
int main(void) {
    int n, m, q;
    int total;
    int resultado;

    /* Matriz que almacena las muestras de cada unidad. */
    int muestras[20][8];

    /* Arreglos para conservar el orden original y realizar los ordenamientos. */
    Registro registros[MAX_UNIDADES];
    Registro copia_score[MAX_UNIDADES];
    Registro copia_id[MAX_UNIDADES];

    char nombre_leido[MAX_NOMBRE];
    char token_extra[2];
    int lectura;

    /* Lee la cantidad de unidades, muestras y el ID que se desea buscar. */
    if (scanf("%d %d %d", &n, &m, &q) != 3) {
        printf("ERROR\n");
        return 0;
    }

    /* Comprueba que los valores generales estén dentro de los rangos permitidos. */
    if (n < 1 || n > MAX_UNIDADES ||
        m < 1 || m > MAX_MUESTRAS ||
        q < 1 || q > 9999) {
        printf("ERROR\n");
        return 0;
    }

    /* Lee y valida individualmente los datos de cada unidad. */
    for (int i = 0; i < n; i++) {

        /* Lee el identificador de la unidad. */
        if (scanf("%d", &registros[i].id) != 1) {
            printf("ERROR\n");
            return 0;
        }

        /* Lee el nombre y comprueba que cumpla las reglas establecidas. */
        lectura = leer_nombre(nombre_leido);

        if (lectura != 1 || !nombre_valido(nombre_leido)) {
            printf("ERROR\n");
            return 0;
        }

        strcpy(registros[i].nombre, nombre_leido);

        /* Lee la configuración de la unidad: tipo y volumen inicial. */
        if (scanf("%d %d",
                  &registros[i].config.tipo,
                  &registros[i].config.p) != 2) {
            printf("ERROR\n");
            return 0;
        }

        /* Valida el ID, el tipo de unidad y el volumen inicial. */
        if (registros[i].id < 1 || registros[i].id > 9999 ||
            (registros[i].config.tipo != 0 &&
             registros[i].config.tipo != 1) ||
            registros[i].config.p < 0 ||
            registros[i].config.p > CAPACIDAD_MAXIMA) {
            printf("ERROR\n");
            return 0;
        }

        /* Comprueba que el identificador no se haya utilizado anteriormente. */
        for (int j = 0; j < i; j++) {
            if (registros[i].id == registros[j].id) {
                printf("ERROR\n");
                return 0;
            }
        }

        /* Lee las muestras de la unidad y verifica que estén entre 0 y 100. */
        for (int j = 0; j < m; j++) {
            if (scanf("%d", &muestras[i][j]) != 1) {
                printf("ERROR\n");
                return 0;
            }

            if (muestras[i][j] < 0 || muestras[i][j] > 100) {
                printf("ERROR\n");
                return 0;
            }
        }
    }

    /* Verifica que no existan datos adicionales después de los registros. */
    if (scanf("%1s", token_extra) == 1) {
        printf("ERROR\n");
        return 0;
    }

    /* Ejecuta la simulación de cada unidad y almacena score y estado. */
    for (int i = 0; i < n; i++) {
        registros[i].score = calcular(
            muestras[i],
            m,
            registros[i].config.tipo,
            registros[i].config.p,
            &registros[i].estado
        );
    }

    /* Calcula la suma de todos los scores mediante la función recursiva. */
    total = total_rec(registros, n);

    /*
     * Copia los registros para generar los dos ordenamientos.
     * De esta manera, el arreglo original conserva el orden de entrada.
     */
    for (int i = 0; i < n; i++) {
        copia_score[i] = registros[i];
        copia_id[i] = registros[i];
    }

    /* Prepara una copia para ORDER y otra para la búsqueda binaria. */
    ordenar(copia_score, n);
    ordenar_por_id(copia_id, n);

    /* Busca el ID solicitado y obtiene su score o -1 si no existe. */
    resultado = buscar(copia_id, n, q);

    /* Imprime los resultados individuales en el orden original de entrada. */
    for (int i = 0; i < n; i++) {
        printf("%d %d %d\n",
               registros[i].id,
               registros[i].score,
               registros[i].estado);
    }

    /* Imprime la suma total de los scores. */
    printf("TOTAL %d\n", total);

    /* Imprime los IDs ordenados según el score y el criterio de desempate. */
    printf("ORDER");
    for (int i = 0; i < n; i++) {
        printf(" %d", copia_score[i].id);
    }
    printf("\n");

    /* Imprime el resultado de la búsqueda del ID solicitado. */
    printf("FIND %d %d\n", q, resultado);

    return 0;
}
