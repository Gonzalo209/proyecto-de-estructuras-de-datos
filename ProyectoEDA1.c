//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Tamanio de la pila
#define TAM 100

/*
	Creamos la estructura DatoObjeto que contiene los siguientes campos:
	-Clave: numerica entera
	-Nombre: cadena de caracteres
	-Nombre del departamento: cadena de caracteres
*/
typedef struct{
	
	int clave;
	char nombre[20],
		 nombreDepartamento[20];
	
}DatoObjeto;

/*
	Creamos la estructura nodo que contiene los siguientes datos:
	-Dato: DatoObjeto
	-pSiguiente: que hace referencia a su misma estructura

*/
typedef struct nodo{
	
	DatoObjeto dato;
	struct nodo* pSiguiente;
	
}Nodo;

//Convertimos la estructura en apuntador
typedef Nodo* pNodo;

//Prototipos de funciones para los datos del objeto
DatoObjeto leerDatoObjeto();

//Prototipos de funciones auxiliar para la cola enlazada y cola circular enlazada
int contenedorVacio(pNodo );
int contenedorLleno(pNodo *);

//Prototipos de funciones para cola enlazada
void agregarMuestraEntrada(pNodo *, pNodo *, DatoObjeto, int *);
void mostrarMuestraEntrada(pNodo );
DatoObjeto retirarMuestraEntrada(pNodo *, pNodo *, int *);
void eliminarMuestrasDeEntrada(pNodo *, pNodo *);

//Prototipos de funciones para cola circular enlazada
void agregarMuestraAnalizada(pNodo *, pNodo *, DatoObjeto, int *);
void mostrarMuestraAnalizada(pNodo );
DatoObjeto retirarMuestraAnalizada(pNodo *, pNodo *, int *);
void eliminarMuestrasAnalizadas(pNodo *, pNodo *);

//Prototipos de funciones para pila estatica
void agregarMuestraEntrega(DatoObjeto [], int *, DatoObjeto );
void mostrarMuestraEntrega(DatoObjeto [], int );

//Programa principal
int main(){
	
	//Declaracion de variables locales
	pNodo pFrente, pFinal;
	pNodo pFrente1, pFinal1;	
	DatoObjeto datos[TAM], dato;
	int totalEntrega = -1, opcion, numeroAleatorio,
	totalMuestraEntrada = 0, totalMuestraAnalizada = 0, i;
	
	//Asignamos null a pFrente y a pFinal
	pFrente = pFinal = NULL;
	
	//Asignamos null a pFrente1 y a pFinal1
	pFrente1 = pFinal1 = NULL;
	
	
	while(1){
		
		printf("1. Agregar una muestra de entrada\n2. Mostrar muestras de entrada\n3. Agregar muestras analizadas\n"
			   "4. Agregar muestras de entrega\n5. Mostrar muestras de entrega\n6. Salir");
		printf("\nElija una opcion: ");
		scanf("%d", &opcion);
		
		switch(opcion){
			
			case 1: 
			
				srand(time(NULL));
				
				numeroAleatorio = rand() % 101;
				
				if(numeroAleatorio >= 0 && numeroAleatorio <= 50){
					
					printf("Muestras de entrada....\n");
							
					dato = leerDatoObjeto();
					
					agregarMuestraEntrada(&pFrente, &pFinal, dato, &totalMuestraEntrada);
					
				}else{
					
					printf("No se pudo agregar la muestra de entrada, intente de nuevo");
					
				}
			
				break;
			
			case 2: 
			
				mostrarMuestraEntrada(pFrente);
			
				break;
			
			case 3:
				
				if(contenedorVacio(pFrente)){
					
					printf("No hay muestras de entradas...");
					
				}else{
					
					printf("Muestras analizadas.....\n");
					
					int total = 1 + rand() % totalMuestraEntrada;
					
					printf("Numero de muestra de entrada por entregar: %d\n", total);
					
					for(i = 0; i < total; i++){
							
						dato = retirarMuestraEntrada(&pFrente, &pFinal, &totalMuestraEntrada);
						
						printf("Agregando muestra de entrada con clave %d, nombre: %s y departamento: %s a la muestra analizada\n", dato.clave, dato.nombre, dato.nombreDepartamento);
						
						printf("Procesando muestra analizada con clave %d\n", dato.clave);
						
						agregarMuestraAnalizada(&pFrente1, &pFinal1, dato, &totalMuestraAnalizada);
						
					}
					
					printf("\n\nMostrando muestras analizadas: \n");
							
					mostrarMuestraAnalizada(pFrente1);
					
				}
							
				break;
			
			case 4:
			
				if(contenedorVacio(pFrente1)){
					
					printf("No hay muestras de entradas...");
					
				}else{
					
					printf("Muestras por entregar.....\n");
					
					srand(time(NULL));
					
					numeroAleatorio = rand() % totalMuestraAnalizada;
					
					printf("Numero de muestra por entregar: %d\n", numeroAleatorio);
					
					for(i = 0; i < numeroAleatorio; i++){
						
						dato = retirarMuestraAnalizada(&pFrente1, &pFinal1, &totalMuestraAnalizada);
						
						printf("Agregando muestra analizada con clave %d, nombre: %s y departamento: %s a la muestra por entregar\n", dato.clave, dato.nombre, dato.nombreDepartamento);
									
						printf("Procesando muestra por entregar con clave %d\n", dato.clave);
						
						agregarMuestraEntrega(datos, &totalEntrega, dato);
						
					}
					
				}
			
				break;		
			
			case 5:
				
				mostrarMuestraEntrega(datos, totalEntrega);
				
				break;
			
			case 6: 
				
				printf("Saliendo del programa...\n"); 
				
				eliminarMuestrasDeEntrada(&pFrente, &pFinal);
	
				printf("\n");
	
				eliminarMuestrasAnalizadas(&pFrente1, &pFinal1);
				
				exit(0); 
				
				break;
			
			default: 
				
				printf("Opcion invalida");
			
		}
		
		if(opcion != 6){
			
			printf("\n");
			system("pause");
			system("cls");
			
		}
		
	}
	
	
	return 0;
}

/*
	Funcion: leerDatoObjeto
	Parametros: 
	Operacion: leemos los datos del objeto muestra para despues almacenarlos en la cola.
	Retorno: dato: DatoObjeto, retornamos el contenido del dato
	
*/

DatoObjeto leerDatoObjeto(){
	
	DatoObjeto dato;
	
	printf("INGRESE LOS DATOS DEL OBJETO MUESTRA: \n");
	
	printf("Clave: ");
	scanf("%d", &dato.clave);
	
	printf("Nombre: ");
	fflush(stdin);
	gets(dato.nombre);
	
	printf("Departamento: ");
	fflush(stdin);
	gets(dato.nombreDepartamento);
	
	return dato;
}

/*
	Funcion: colaVacia
	Parametros: pFrente: pNodo
	Operacion: verificamos si a partir de la primer liga de la cola, esta vacia o no
	
*/

int contenedorVacio(pNodo pFrente){

	return pFrente == NULL;

}

/*
	Funcion: colaLlena
	Parametro: pNuevo: pNodo
	Operacion: verificamos si podemos seguir reservando memoria, en caso de que no podamos reservar mas memoria
			   nos va a retornar null
*/

int contenedorLleno(pNodo *pNuevo){
	
	*pNuevo = malloc(sizeof(Nodo));
	
	return *pNuevo == NULL;
	
}


/*
	Funcion: agregarMuestraEntrada
	Parametro: pFrente: pNodo, pFinal: pNodo, dato: DatoObjeto, totalMuestrasEntrada: int
	Operacion: agregamos una muestra de entrada al final de la cola.

*/

void agregarMuestraEntrada(pNodo *pFrente, pNodo *pFinal, DatoObjeto dato, int *totalMuestrasEntrada){
	
	pNodo pNuevo;
	
	if(contenedorLleno(&pNuevo)){
		
		printf("Ya no se pueden agregar mas muestras");
		
	}else{
		
		pNuevo->dato = dato;
		(*totalMuestrasEntrada)++;
		pNuevo->pSiguiente = NULL;	
		
		if(contenedorVacio(*pFrente)){
			
			*pFrente = pNuevo;
			
		}else{
			
			(*pFinal)->pSiguiente = pNuevo;
			
		}
		
		*pFinal = pNuevo;
		
		printf("Se agrego la muestra con exito: \nClave: %d\nNombre: %s\nDepartamento: %s\n", dato.clave, dato.nombre, dato.nombreDepartamento);
		
	}
	
}


/*
	Funcion: mostrarMuestraEntrada
	Parametro: pFrente: pNodo
	Operacion: mostramos todas las muestras de entrada que ham sido agregado en la cola
*/

void mostrarMuestraEntrada(pNodo pFrente){
	
	if(contenedorVacio(pFrente)){
	
		printf("No hay muestras ingresadas");
			
	}else{
		
		pNodo pPosicion = pFrente;
		
		printf("MOSTRANDO MUESTRAS DE ENTRADA: \n");
		
		while(pPosicion != NULL){
			
			printf("Clave: %d\nNombre: %s\nDepartamento: %s\n", pPosicion->dato.clave, pPosicion->dato.nombre, pPosicion->dato.nombreDepartamento);
		
			pPosicion = pPosicion->pSiguiente;
			
		}
		
	}
	
}


/*
	Funcion: retirarMuestraEntrada
	Parametro: pFrente: pNodo, pFinal: pNodo
	Operacion: retiramos una muestra de entrada al inicio de la cola, para posteriormente ser evaluada en la fase de proceso 
	Retorno: dato: DatoObjeto es lo que contiene el inicio de la cola, que en este caso es la primer muestra de entrada

*/

DatoObjeto retirarMuestraEntrada(pNodo *pFrente, pNodo *pFinal, int *totalMuestrasEntrada){
	
	if(contenedorVacio(*pFrente)){
		
		return;
		
	}else{
		
		pNodo pLibera = *pFrente;
		DatoObjeto dato;
		
		if(*pFrente == *pFinal){
			
			*pFrente = *pFinal = NULL;
			
		}else{
			
			*pFrente = (*pFrente)->pSiguiente;
			
		}
		
		dato = pLibera->dato;
		
		(*totalMuestrasEntrada)--;
		
		free(pLibera);
		
		return dato;	
	}
	
}

/*
	Funcion: agregarMuestraEntrada
	Parametro: pFrente: pNodo, pFinal: pNodo, dato: DatoObjeto
	Operacion: agregamos una muestra analizada dentro de la cola circular

*/

void agregarMuestraAnalizada(pNodo *pFrente, pNodo *pFinal, DatoObjeto dato, int* totalMuestrasAnalizada){
	
	pNodo pNuevo;
	
	if(contenedorLleno(&pNuevo)){
		
		printf("Ya no se pueden agregar mas muestras analizadas");
		
	}else{
		
		pNuevo->dato = dato;
		(*totalMuestrasAnalizada)++;
		
		if(contenedorVacio(*pFrente)){
			
			*pFrente = pNuevo;
			
			pNuevo->pSiguiente = *pFrente;
			
		}else{
			
			(*pFinal)->pSiguiente = pNuevo;
			
			pNuevo->pSiguiente = *pFrente;
						
		}
		
		*pFinal = pNuevo;
		
	}
	
}

/*
	Funcion: mostrarMuestraAnalizada
	Parametro: pFrente: pNodo
	Operacion: mostramos todas las muestras analizadas que han sido agregado en la cola
*/

void mostrarMuestraAnalizada(pNodo pFrente){
	
	if(contenedorVacio(pFrente)){
		
		printf("No hay muestras analizadas");
		
	}else{
		
		pNodo pPosicion = pFrente->pSiguiente;
		
		do{
			
			printf("Clave: %d\nNombre: nombre\nDepartamento: %s\n", pPosicion->dato.clave, pPosicion->dato.nombre, pPosicion->dato.nombreDepartamento);
			
			pPosicion = pPosicion->pSiguiente;
			
		}while(pPosicion != pFrente->pSiguiente);
		
	}
	
}

/*
	Funcion: retirarMuestraAnalizada
	Parametro: pFrente: pNodo, pFinal: pNodo
	Operacion: retiramos una muestra de entrada al inicio de la cola, para posteriormente ser evaluada en la fase de muestras por entregar
	Retorno: dato: DatoObjeto es lo que contiene el inicio de la cola, que en este caso es la primer muestra analizada

*/

DatoObjeto retirarMuestraAnalizada(pNodo *pFrente, pNodo *pFinal, int *totalMuestraAnalizada){
	
	if(contenedorVacio(*pFrente)){
		
		return;
		
	}else{
		
		pNodo pLibera = *pFrente;
		DatoObjeto dato;
		
		if(*pFrente == *pFinal){
			
			*pFrente = *pFinal = NULL;
			
		}else{
		
			*pFrente = (*pFrente)->pSiguiente;
			
			(*pFinal)->pSiguiente = *pFrente;
						
		}
		
		dato = pLibera->dato;
		
		(*totalMuestraAnalizada)--;
		
		free(pLibera);
		
		return dato;
	
	}
	
}

void agregarMuestraEntrega(DatoObjeto datos[], int *totalEntrega, DatoObjeto dato){
	
	if(*totalEntrega == TAM - 1){
		
		printf("Ya no se pueden agregar mas muestrar por entregar");
		
	}else{
		
		(*totalEntrega)++;
		
		datos[*totalEntrega] = dato;
		
	}
	
}

void mostrarMuestraEntrega(DatoObjeto datos[], int totalEntrega){
	
	if(totalEntrega == -1){
		
		printf("No hay muestras entregadas");
		
	}else{
		
		int i;
		
		for(i = 0; i <= totalEntrega; i++){
			
			printf("La muestra %d se entrego al departamento %s\n", datos[i].clave, datos[i].nombreDepartamento);
			
		}
		
		
	}
	
	
}

/*
	Funcion: eliminarMuestraDeEntrada
	Parametro: pFrente: pNodo, pFinal: pNodo
	Operacion: eliminamos todas las muestras de entrada
*/

void eliminarMuestrasDeEntrada(pNodo *pFrente, pNodo *pFinal){
	
	if(! contenedorVacio(*pFrente)){
		
		pNodo pPosicion = *pFrente;
		pNodo pLibera = NULL;
		
		while(pPosicion != NULL){
			
			pLibera = pPosicion;
			
			pPosicion = pPosicion->pSiguiente;
			
			free(pLibera);
			
		}
		
		*pFrente = *pFinal = NULL;
		
		printf("Liberando todo los nodos");
		
	}
	
}

/*
	Funcion: eliminarMuestrasAnalizadas
	Parametro: pFrente: pNodo, pFinal: pNodo
	Operacion: eliminamos todas las muestras analizadas
	
*/
void eliminarMuestrasAnalizadas(pNodo *pFrente, pNodo *pFinal){
	
	if(! contenedorVacio(*pFrente)){
		
		pNodo pPosicion = *pFrente;
		pNodo pLibera = NULL;
		
		do{
			
			pLibera = pPosicion;
			
			pPosicion = pPosicion->pSiguiente;
			
			free(pLibera);
			
		}while(pPosicion != *pFrente);
		
		*pFrente = *pFinal = NULL;
		
		printf("Liberando todo los nodos");
		
	}
	
}
