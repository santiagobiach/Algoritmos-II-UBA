#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(!comparador){
		return NULL;
	}

	abb_t* puntero_abb = malloc(sizeof(abb_t));
	if(!puntero_abb){
		return NULL;
	}
	puntero_abb->nodo_raiz = NULL;
	puntero_abb->comparador = comparador;
	puntero_abb->destructor = destructor;

	return puntero_abb;
}
//Post: Un nodo inicializado en memoria dinamica, con el elemento que le llega por parametro.
nodo_abb_t* crear_nodo(void* elemento){
	nodo_abb_t* nuevo_nodo = malloc(sizeof(nodo_abb_t));
	if(!nuevo_nodo){
		return NULL;
	}
	nuevo_nodo->izquierda = NULL;
	nuevo_nodo->derecha = NULL;
	nuevo_nodo->elemento = elemento;
	return nuevo_nodo;
}
//Pre:El nuevo nodo debe ser valido(no NULL), y el comparador tambien debe ser valido(no NULL)
//Post:Inserta el nodo en su lugar correspondiente, de manera recursiva. Devuelve 0 si inserto con exito.
int insertar_nodo_recursivo(nodo_abb_t* raiz, nodo_abb_t* nuevo_nodo, abb_comparador comparador){
	if(!raiz){
		return -1;//Esto nunca deberia pasar.
	}
	int comparacion = comparador(nuevo_nodo->elemento, raiz->elemento);
	if(comparacion<=0){
		if(!raiz->izquierda){
			raiz->izquierda = nuevo_nodo;
			return 0;
		}
		return insertar_nodo_recursivo(raiz->izquierda, nuevo_nodo, comparador);
	}
	if(!raiz->derecha){
		raiz->derecha = nuevo_nodo;
		return 0;
	}
	return insertar_nodo_recursivo(raiz->derecha, nuevo_nodo, comparador);
}

int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol){
		return -1;
	}
	nodo_abb_t* nuevo_nodo = crear_nodo(elemento);
	if(!nuevo_nodo){
		return -1;
	}
	if(!arbol->nodo_raiz){
		arbol->nodo_raiz = nuevo_nodo;
		return 0;
	}
	return insertar_nodo_recursivo(arbol->nodo_raiz, nuevo_nodo, arbol->comparador);
}

//Post: Destruye todos los nodos de manera recursiva, aplicando el destructor a los elementos si es necesario.
void destruir_nodos_recursivo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	if(!nodo){
		return;
	}
	destruir_nodos_recursivo(nodo->izquierda, destructor);

	destruir_nodos_recursivo(nodo->derecha, destructor);

	if(destructor){
		destructor(nodo->elemento);
	}
	free(nodo);
}

void arbol_destruir(abb_t* arbol){
	if(!arbol){
		return;
	}
	destruir_nodos_recursivo(arbol->nodo_raiz, arbol->destructor);
	free(arbol);
}
void* arbol_raiz(abb_t* arbol){
	if(!arbol || arbol_vacio(arbol)){
		return NULL;
	}
	return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
	if(!arbol){
		return true;
	}
	return (arbol->nodo_raiz == NULL);
}
//Pre: El comparador debe ser valido.
//Post: Busca recursivamente el elemento, y si lo encuentra lo devuelve.Si no, devuelve NULL.
void* buscar_elemento_recursivo(nodo_abb_t* raiz, void* elemento, abb_comparador comparador){
	if(!raiz){
		return NULL;
	}
	int comparacion = comparador(elemento, raiz->elemento);
	if(comparacion==0){
		return raiz->elemento;
	}else if(comparacion < 0){
		return buscar_elemento_recursivo(raiz->izquierda, elemento, comparador);
	}
	return buscar_elemento_recursivo(raiz->derecha, elemento, comparador);
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!arbol || arbol_vacio(arbol)){
		return NULL;
	}

	return buscar_elemento_recursivo(arbol->nodo_raiz, elemento, arbol->comparador);
}
//Pre: Array debe ser distinto de NULL.
/*Post: Recorre los nodos de de forma "inorden", y llena el array hasta que termina de recorrer el arbol, o que
        se lleno el array*/
size_t recorrer_nodos_inorden_recursivo(nodo_abb_t* raiz, void** array, size_t tamanio_array, size_t contador){
	if(!raiz || contador >= tamanio_array){
		return contador;
	}
	contador = recorrer_nodos_inorden_recursivo(raiz->izquierda, array, tamanio_array, contador);
	array[contador] = raiz->elemento;
	contador++;

	contador = recorrer_nodos_inorden_recursivo(raiz->derecha, array, tamanio_array, contador);

	return contador;
}
//Post:Llama a la funcion recursiva.
size_t recorrer_nodos_inorden(nodo_abb_t* raiz, void** array, size_t tamanio_array){
	return recorrer_nodos_inorden_recursivo(raiz, array, tamanio_array, 0);
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !array || arbol_vacio(arbol)){
		return 0;
	}
	return recorrer_nodos_inorden(arbol->nodo_raiz, array, tamanio_array);
}
//Pre: Array debe ser distinto de NULL.
/*Post: Recorre los nodos de de forma "preorden", y llena el array hasta que termina de recorrer el arbol, o que
        se lleno el array*/
size_t recorrer_nodos_preorden_recursivo(nodo_abb_t* raiz, void** array, size_t tamanio_array, size_t contador){
	if(!raiz || contador >= tamanio_array){
		return contador;
	}

	array[contador] = raiz->elemento;
	contador++;

	contador = recorrer_nodos_preorden_recursivo(raiz->izquierda, array, tamanio_array, contador);

	contador = recorrer_nodos_preorden_recursivo(raiz->derecha, array, tamanio_array, contador);

	return contador;
}
//Post: Llama a la funcion recursiva
size_t recorrer_nodos_preorden(nodo_abb_t* raiz, void** array, size_t tamanio_array){
	return recorrer_nodos_preorden_recursivo(raiz, array, tamanio_array, 0);
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !array || arbol_vacio(arbol)){
		return 0;
	}
	return recorrer_nodos_preorden(arbol->nodo_raiz, array, tamanio_array);
}
//Pre: Array debe ser distinto de NULL. El bool debe estar inicializado.
/*Post: Recorre los nodos de de forma "postorden", y llena el array hasta que termina de recorrer el arbol, o que
        se lleno el array*/
size_t recorrer_nodos_postorden_recursivo(nodo_abb_t* raiz, void** array, size_t tamanio_array, size_t contador,
									      bool* termino){

	if(!raiz || contador >= tamanio_array || (*termino)){
		return contador;
	}

	contador = recorrer_nodos_postorden_recursivo(raiz->izquierda, array, tamanio_array, contador, termino);

	contador = recorrer_nodos_postorden_recursivo(raiz->derecha, array, tamanio_array, contador, termino);
	if(!(*termino)){
		if(contador >= tamanio_array){
			*termino = true;
			return contador;
		}
		array[contador] = raiz->elemento;
		contador++;
	}
	
	return contador;
}
//Post: Llama a la funcion recursiva.
size_t recorrer_nodos_postorden(nodo_abb_t* raiz, void** array, size_t tamanio_array){
	bool bool_aux = false;

	return recorrer_nodos_postorden_recursivo(raiz, array, tamanio_array, 0, &bool_aux);
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
	if(!arbol || !array || arbol_vacio(arbol)){
		return 0;
	}
	return recorrer_nodos_postorden(arbol->nodo_raiz, array, tamanio_array);
}
//Pre: El nodo debe ser valido(distinto de NULL, y tiene que tener 2 hijos).
//Post: Devuelve el predecesor inorden del nodo, haciendo las operaciones con punteros correspondientes.
nodo_abb_t* buscar_predecesor_inorden(nodo_abb_t* raiz){
	nodo_abb_t* nodo_aux = raiz->izquierda;
	nodo_abb_t* predecesor_inorden;

	if(!nodo_aux->derecha){
		return nodo_aux;
	}

	while(nodo_aux->derecha->derecha){
		nodo_aux = nodo_aux->derecha;
	}

	predecesor_inorden = nodo_aux->derecha;
	nodo_aux->derecha = predecesor_inorden->izquierda;

	return predecesor_inorden;
}

//Pre: El nodo debe ser distinto valido(distinto de NULL).
//Post: Borra el nodo que viene por parametro. Hace las operaciones con punteros correspondientes
nodo_abb_t* borrar_nodo(nodo_abb_t* raiz, abb_liberar_elemento destructor, int* resultado){
	if(!raiz->izquierda && !raiz->derecha){

		if(destructor){
			destructor(raiz->elemento);
		}

		free(raiz);
		*resultado = 0;
		return NULL;	
	}else if(!raiz->izquierda || !raiz->derecha){

		nodo_abb_t* nueva_raiz = raiz->derecha?raiz->derecha:raiz->izquierda;
		if(destructor){
			destructor(raiz->elemento);	
		}

		free(raiz);
		*resultado = 0;
		return nueva_raiz;
	}
	nodo_abb_t* nueva_raiz = buscar_predecesor_inorden(raiz);
	nueva_raiz->derecha =raiz->derecha;
	/*Si el predecesor es el nodo inmediatamente a la izquierda, simplemente hay que asignarle a su 
	  derecha lo que tenia la raiz.*/
	if(raiz->izquierda!=nueva_raiz){
		nueva_raiz->izquierda = raiz->izquierda;
	}

	if(destructor){
		destructor(raiz->elemento);	
	}
	free(raiz);
	*resultado = 0;

	return nueva_raiz;
}
//Pre: El comparador debe valido(distinto que NULL).
//Post: Busca recursivamente el nodo a borrar.
nodo_abb_t* borrar_recursivo(nodo_abb_t* raiz, void* elemento, abb_comparador comparador, 
							 abb_liberar_elemento destructor, int* resultado){

	if(!raiz){
		*resultado = -1;
		return NULL;
	}
	int comparacion = comparador(elemento, raiz->elemento);
	if(comparacion == 0){
		return borrar_nodo(raiz, destructor, resultado);
	}else if(comparacion < 0){
		raiz->izquierda = borrar_recursivo(raiz->izquierda, elemento, comparador, destructor, resultado);
	}else{
		raiz->derecha = borrar_recursivo(raiz->derecha, elemento, comparador, destructor, resultado);
	}
	

	return raiz;
}

int arbol_borrar(abb_t* arbol, void* elemento){
	if(!arbol || arbol_vacio(arbol)){
		return -1;
	}
	int resultado = -1;

	arbol->nodo_raiz = borrar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador, arbol->destructor, &resultado);

	return resultado;
}
//Pre: La funcion debe ser valida(distinta de NULL). El bool debe estar inicializado.
//Post:Itera recursivamente y le aplica la funcion a cada nodo. Cuando la funcion devuelve true, deja de iterar.
size_t iterar_inorden_recursivo(nodo_abb_t* raiz, bool (*funcion)(void*, void*), size_t contador, void* extra,
								bool* termino){
	if(!raiz || (*termino)){
		return contador;
	}

	contador = iterar_inorden_recursivo(raiz->izquierda, funcion, contador, extra, termino);

	if(!(*termino)){
		if(funcion(raiz->elemento, extra)){
			*termino = true;
			contador++;
			return contador;
		}
		contador++;
	}

	contador = iterar_inorden_recursivo(raiz->derecha, funcion, contador, extra, termino);

	return contador;
}
//Pre: La funcion debe ser valida(distinta de NULL). El bool debe estar inicializado.
//Post:Itera recursivamente y le aplica la funcion a cada nodo. Cuando la funcion devuelve true, deja de iterar.
size_t iterar_preorden_recursivo(nodo_abb_t* raiz, bool (*funcion)(void*, void*), size_t contador, void* extra, bool* termino){
	if(!raiz || (*termino)){
		return contador;
	}

	if(!(*termino)){
		if(funcion(raiz->elemento, extra)){
			*termino = true;
			contador++;
			return contador;
		}
		contador++;
	}

	contador = iterar_preorden_recursivo(raiz->izquierda, funcion, contador, extra, termino);

	contador = iterar_preorden_recursivo(raiz->derecha, funcion, contador, extra, termino);

	return contador;
}
//Pre: La funcion debe ser valida(distinta de NULL). El bool debe estar inicializado.
//Post:Itera recursivamente y le aplica la funcion a cada nodo. Cuando la funcion devuelve true, deja de iterar.
size_t iterar_postorden_recursivo(nodo_abb_t* raiz, bool (*funcion)(void*, void*), size_t contador, void* extra, bool* termino){
	if(!raiz || (*termino)){
		return contador;
	}
	
	contador = iterar_postorden_recursivo(raiz->izquierda, funcion, contador, extra, termino);
	
	
	contador = iterar_postorden_recursivo(raiz->derecha, funcion, contador, extra, termino);
	
	
	if(!(*termino)){
		if(funcion(raiz->elemento, extra)){
			*termino = true;
			contador++;
			return contador;
		}
		contador++;
	}
	return contador;
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(!arbol || !funcion){
		return 0;
	}
	size_t contador = 0;
	bool bool_aux = false;

	if(recorrido == ABB_RECORRER_INORDEN){
		contador = iterar_inorden_recursivo(arbol->nodo_raiz, funcion, contador, extra, &bool_aux);
	}else if(recorrido == ABB_RECORRER_PREORDEN){
		contador = iterar_preorden_recursivo(arbol->nodo_raiz, funcion, contador, extra, &bool_aux);
	}else if(recorrido == ABB_RECORRER_POSTORDEN){
		contador = iterar_postorden_recursivo(arbol->nodo_raiz, funcion, contador, extra, &bool_aux);
	}
	return contador;
}