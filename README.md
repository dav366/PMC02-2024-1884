# PMC02 - Desbordamiento de un depósito

## Información del proyecto

| Campo | Información |
|---|---|
| Asignatura | Programación para Mecatrónicos |
| Proyecto | Reto 02: Desbordamiento de un depósito |
| Estudiante | Omar David Guzmán Guerrero |
| Matrícula | 2024-1884 |
| Correo | 20241884@itla.edu.do |
| Sección | Sábados |
| Fecha de entrega | 06/11/2026 |

## Descripción

Este proyecto consiste en el desarrollo de un simulador de desbordamiento de un depósito utilizando el lenguaje de programación C.

El programa procesa diferentes unidades a partir de sus identificadores, nombres, configuraciones y muestras de entrada. Mediante estos datos, simula las variaciones del volumen de cada depósito, controla sus límites de capacidad y calcula la cantidad acumulada de desbordamiento.

Además, implementa diferentes técnicas de programación, como funciones, estructuras, arreglos, recursividad, algoritmos de ordenamiento y búsqueda binaria.

## Funcionalidades principales

- Lectura y validación de los datos de entrada.
- Validación de nombres e identificadores.
- Simulación del comportamiento de cada depósito.
- Control del volumen mínimo y máximo permitido.
- Cálculo individual de las puntuaciones (`score`).
- Determinación del estado final de cada unidad.
- Cálculo recursivo de la puntuación total.
- Ordenamiento por puntuación descendente e identificador ascendente.
- Ordenamiento por identificador para realizar búsquedas.
- Búsqueda binaria de unidades mediante su identificador.
- Presentación de resultados en el formato establecido.

## Tecnologías utilizadas

- Lenguaje C (estándar C11).
- GCC como compilador.
- Python 3 para la automatización de pruebas.
- PSeInt para la representación del pseudocódigo.
- Git y GitHub para el control de versiones.

## Requisitos

Para compilar y ejecutar el proyecto se necesita:

- Un compilador GCC compatible con C11.
- Una terminal o entorno de desarrollo.
- Python 3 para ejecutar el evaluador automático.

## Compilación

Desde la terminal, ubícate en la carpeta del proyecto y ejecuta:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto
```

En Windows, también puedes generar el ejecutable con:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o reto.exe
```

## Ejecución

En Linux o macOS:

```bash
./reto
```

En Windows:

```bash
.\reto.exe
```

El programa recibe los datos mediante la entrada estándar y presenta los resultados correspondientes.

## Sistema de pruebas

El proyecto incluye diez casos de prueba organizados en dos grupos:

**Pruebas públicas**
- Seis escenarios de prueba.
- Cada escenario contiene un archivo de entrada `.in` y su salida esperada `.out`.

**Pruebas propias**
- Cuatro escenarios adicionales.
- Cada escenario contiene su archivo de entrada `.in` y su salida esperada `.out`.

Los archivos JSON contienen la definición de los casos y permiten trabajar con el evaluador automático.

## Ejecución del evaluador

Para ejecutar las pruebas públicas:

```bash
python evaluar.py publicas.json .\reto.exe
```

Para ejecutar las pruebas propias:

```bash
python evaluar.py propias.json .\reto.exe
```

El evaluador ejecuta los escenarios correspondientes y compara los resultados obtenidos con las salidas esperadas.

## Documentación adicional

- `plan.md`: planificación, descripción de la lógica y diseño del programa.
- `psc main.psc`: representación del algoritmo en PSeInt.
- `reto.h`: definición de constantes, estructuras y prototipos.
- `main.c`: implementación del simulador.
- `evaluar.py`: automatización de las pruebas.

## Autor

**Omar David Guzmán Guerrero**

Estudiante de Tecnología en Mecatrónica / Programación para Mecatrónicos.

Instituto Tecnológico de las Américas (ITLA).

Matrícula: 2024-1884.
