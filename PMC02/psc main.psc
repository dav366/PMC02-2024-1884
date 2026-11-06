
Proceso Desbordamiento_De_Un_Deposito
	
    // ==========================================
    // 1. DECLARACION DE VARIABLES
    // ==========================================
	
    Definir n, m, q Como Entero
    Definir i, j Como Entero
    Definir volumen, balance, nuevo Como Entero
    Definir total, resultado Como Entero
    Definir izquierda, derecha, medio Como Entero
    Definir temporal Como Entero
	
    Definir valido, encontrado Como Logico
	
    // Arreglos de datos de las unidades.
    Definir ids, tipos, volumenes Como Entero
    Definir scores, estados Como Entero
    Definir copiaScore, copiaID Como Entero
    Definir nombres Como Cadena
	
    // Matriz de muestras.
    Definir muestras Como Entero
	
    Dimension ids[20]
    Dimension tipos[20]
    Dimension volumenes[20]
    Dimension scores[20]
    Dimension estados[20]
    Dimension copiaScore[20]
    Dimension copiaID[20]
    Dimension nombres[20]
    Dimension muestras[20,8]
	
    valido <- Verdadero
	
    // ==========================================
    // 2. LECTURA Y VALIDACION DE DATOS GENERALES
    // ==========================================
	
    Escribir "Ingrese la cantidad de unidades (n):"
    Leer n
	
    Escribir "Ingrese la cantidad de muestras (m):"
    Leer m
	
    Escribir "Ingrese el ID que desea buscar (q):"
    Leer q
	
    Si n < 1 O n > 20 O m < 1 O m > 8 O q < 1 O q > 9999 Entonces
        valido <- Falso
    FinSi
	
    // ==========================================
    // 3. LECTURA Y VALIDACION DE LAS UNIDADES
    // ==========================================
	
    Si valido Entonces
		
        Para i <- 1 Hasta n Hacer
			
            Escribir "Ingrese ID:"
            Leer ids[i]
			
            Escribir "Ingrese nombre:"
            Leer nombres[i]
			
            Escribir "Ingrese tipo de unidad (0 o 1):"
            Leer tipos[i]
			
            Escribir "Ingrese volumen inicial:"
            Leer volumenes[i]
			
            // Validar identificador.
            Si ids[i] < 1 O ids[i] > 9999 Entonces
                valido <- Falso
            FinSi
			
            // Validar tipo.
            Si tipos[i] <> 0 Y tipos[i] <> 1 Entonces
                valido <- Falso
            FinSi
			
            // Validar volumen inicial.
            Si volumenes[i] < 0 O volumenes[i] > 100 Entonces
                valido <- Falso
            FinSi
			
            // Validar longitud del nombre.
            Si Longitud(nombres[i]) < 1 O Longitud(nombres[i]) > 15 Entonces
                valido <- Falso
            FinSi
			
            // Validar caracteres del nombre.
            Si NombreValido(nombres[i]) = Falso Entonces
                valido <- Falso
            FinSi
			
            // Comprobar identificadores duplicados.
            Si i > 1 Entonces
				
                Para j <- 1 Hasta i-1 Hacer
					
                    Si ids[i] = ids[j] Entonces
                        valido <- Falso
                    FinSi
					
                FinPara
				
            FinSi
			
            // Leer y validar las muestras.
            Para j <- 1 Hasta m Hacer
				
                Escribir "Ingrese muestra:"
                Leer muestras[i,j]
				
                Si muestras[i,j] < 0 O muestras[i,j] > 100 Entonces
                    valido <- Falso
                FinSi
				
            FinPara
			
        FinPara
		
    FinSi
	
    // ==========================================
    // 4. CALCULO DE LOS DEPOSITOS
    // ==========================================
	
    Si valido Entonces
		
        Para i <- 1 Hasta n Hacer
			
            volumen <- volumenes[i]
            scores[i] <- 0
			
            Para j <- 1 Hasta m Hacer
				
                // Calcular el balance de la muestra.
                balance <- muestras[i,j] - 50
				
                // Invertir el balance para el tipo 1.
                Si tipos[i] = 1 Entonces
                    balance <- balance * (-1)
                FinSi
				
                nuevo <- volumen + balance
				
                // Controlar el desbordamiento.
                Si nuevo > 100 Entonces
					
                    scores[i] <- scores[i] + (nuevo - 100)
                    volumen <- 100
					
                Sino
					
                    // Controlar el volumen minimo.
                    Si nuevo < 0 Entonces
                        volumen <- 0
                    Sino
                        volumen <- nuevo
                    FinSi
					
                FinSi
				
            FinPara
			
            // Determinar el estado final.
            Si volumen >= 50 Entonces
                estados[i] <- 1
            Sino
                estados[i] <- 0
            FinSi
			
        FinPara
		
        // ==========================================
        // 5. SUMA RECURSIVA DE LOS SCORES
        // ==========================================
		
        total <- TotalRec(scores, n)
		
        // ==========================================
        // 6. CREAR COPIAS PARA LOS ORDENAMIENTOS
        // ==========================================
		
        Para i <- 1 Hasta n Hacer
			
            copiaScore[i] <- i
            copiaID[i] <- i
			
        FinPara
		
        // ==========================================
        // 7. ORDENAR POR SCORE DESCENDENTE
        //    Y POR ID ASCENDENTE EN LOS EMPATES
        // ==========================================
		
        Si n > 1 Entonces
			
            Para i <- 1 Hasta n-1 Hacer
				
                Para j <- 1 Hasta n-i Hacer
					
                    Si scores[copiaScore[j]] < scores[copiaScore[j+1]] O (scores[copiaScore[j]] = scores[copiaScore[j+1]] Y ids[copiaScore[j]] > ids[copiaScore[j+1]]) Entonces
						
                        temporal <- copiaScore[j]
                        copiaScore[j] <- copiaScore[j+1]
                        copiaScore[j+1] <- temporal
						
                    FinSi
					
                FinPara
				
            FinPara
			
        FinSi
		
        // ==========================================
        // 8. ORDENAR POR ID ASCENDENTE
        // ==========================================
		
        Si n > 1 Entonces
			
            Para i <- 1 Hasta n-1 Hacer
				
                Para j <- 1 Hasta n-i Hacer
					
                    Si ids[copiaID[j]] > ids[copiaID[j+1]] Entonces
						
                        temporal <- copiaID[j]
                        copiaID[j] <- copiaID[j+1]
                        copiaID[j+1] <- temporal
						
                    FinSi
					
                FinPara
				
            FinPara
			
        FinSi
		
        // ==========================================
        // 9. BUSQUEDA BINARIA
        // ==========================================
		
        izquierda <- 1
        derecha <- n
        resultado <- -1
        encontrado <- Falso
		
        Mientras izquierda <= derecha Y encontrado = Falso Hacer
			
            medio <- Trunc((izquierda + derecha) / 2)
			
            Si ids[copiaID[medio]] = q Entonces
				
                resultado <- scores[copiaID[medio]]
                encontrado <- Verdadero
				
            Sino
				
                Si ids[copiaID[medio]] < q Entonces
                    izquierda <- medio + 1
                Sino
                    derecha <- medio - 1
                FinSi
				
            FinSi
			
        FinMientras
		
        // ==========================================
        // 10. PRESENTACION DE RESULTADOS
        // ==========================================
		
        // Mostrar unidades en el orden de entrada.
        Para i <- 1 Hasta n Hacer
			
            Escribir ids[i], " ", scores[i], " ", estados[i]
			
        FinPara
		
        // Mostrar suma total.
        Escribir "TOTAL ", total
		
        // Mostrar ordenamiento por score.
        Escribir Sin Saltar "ORDER"
		
        Para i <- 1 Hasta n Hacer
			
            Escribir Sin Saltar " ", ids[copiaScore[i]]
			
        FinPara
		
        Escribir ""
		
        // Mostrar resultado de la busqueda.
        Escribir "FIND ", q, " ", resultado
		
    Sino
		
        Escribir "ERROR"
		
    FinSi
	
FinProceso


// ==========================================
// 11. FUNCION RECURSIVA TOTALREC
// ==========================================

Funcion resultado <- TotalRec(scores Por Referencia, n)
	
    Si n = 0 Entonces
		
        resultado <- 0
		
    Sino
		
        resultado <- scores[n] + TotalRec(scores, n-1)
		
    FinSi
	
FinFuncion


// ==========================================
// 12. FUNCION DE VALIDACION DE NOMBRES
// ==========================================

Funcion valido <- NombreValido(nombre)
	
    Definir i, j Como Entero
    Definir caracter, permitidos Como Cadena
    Definir encontrado Como Logico
	
    permitidos <- "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_"
	
    valido <- Verdadero
	
    // Evitar recorrer un nombre vacio.
    Si Longitud(nombre) = 0 Entonces
		
        valido <- Falso
		
    Sino
		
        Para i <- 0 Hasta Longitud(nombre)-1 Hacer
			
            caracter <- Subcadena(nombre, i, i)
            encontrado <- Falso
			
            // Buscar cada caracter en la lista permitida.
            Para j <- 0 Hasta Longitud(permitidos)-1 Hacer
				
                Si caracter = Subcadena(permitidos, j, j) Entonces
                    encontrado <- Verdadero
                FinSi
				
            FinPara
			
            Si encontrado = Falso Entonces
                valido <- Falso
            FinSi
			
        FinPara
		
    FinSi
	
FinFuncion
