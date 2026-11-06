# PMC02 – Desbordamiento de un depósito

## 1. Descripción del proyecto

El proyecto consiste en desarrollar un simulador en lenguaje C que permita evaluar el comportamiento de varios depósitos a partir de una serie de muestras.

Cada depósito posee un identificador, un nombre, un tipo de configuración y un volumen inicial. A partir de las muestras recibidas, el programa calcula las variaciones del volumen, identifica los desbordamientos y determina el estado final de cada depósito.

Además, el programa calcula un acumulado general, ordena los depósitos según su puntuación y permite consultar el resultado de un depósito mediante su identificador.

## 2. Objetivo

Implementar una solución en C11 que procese y valide los datos de múltiples depósitos, aplique las reglas de simulación y presente los resultados correspondientes.

El desarrollo utiliza estructuras, arreglos, matrices, funciones, recursividad, ordenamiento y búsqueda binaria.

## 3. Datos de entrada

El programa recibe inicialmente tres valores:

| Variable | Descripción | Rango permitido |
|---|---|---|
| n | Cantidad de depósitos | 1 a 20 |
| m | Cantidad de muestras por depósito | 1 a 8 |
| q | Identificador que se desea buscar | 1 a 9999 |

Posteriormente, cada depósito contiene:

| Dato | Descripción | Restricción |
|---|---|---|
| id | Identificador | 1 a 9999, sin duplicados |
| nombre | Nombre del depósito | 1 a 15 caracteres |
| tipo | Configuración de operación | 0 o 1 |
| p | Volumen inicial | 0 a 100 |
| muestras | Valores recibidos | Cada valor entre 0 y 100 |

Los nombres aceptan letras ASCII mayúsculas y minúsculas, números y guion bajo.
