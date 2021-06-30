#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


lista_t* lista_crear(lista_destructor destructor){

	lista_t* puntero_lista = malloc(sizeof(lista_t));
	if(!puntero_lista){
		return NULL;
	}
	
	puntero_lista->destructor = destructor;
	puntero_lista->nodo_inicio = NULL;
	puntero_lista->nodo_fin = NULL;
	puntero_lista->cantidad = 0;

	return puntero_lista;
}


//Pre: La lista no es NULL.
//Post: Libera la memoria reservada por todos los nodos de la lista.
void destruir_nodos_lista(lista_t* lista, bool destruir_elementos){

	if(!lista_vacia(lista)){
		nodo_t* nodo_actual = lista->nodo_inicio;
		nodo_t* nodo_auxiliar;
		for(int i = 0; i < lista->cantidad; i++){
			nodo_auxiliar = nodo_actual->siguiente;
			if(lista->destructor && destruir_elementos){
				lista->destructor(nodo_actual->elemento);
			}
			free(nodo_actual);
			nodo_actual = nodo_auxiliar;
		}
	}
}

void lista_destruir(lista_t* lista, bool destruir_elementos){
	if(lista != NULL){
		destruir_nodos_lista(lista, destruir_elementos);
		free(lista);
	}	
}

bool lista_vacia(lista_t* lista){
	if(!lista){
		return true;
	}

	return (lista->cantidad == 0);
}

//Post:Crea un nodo reservando la memoria correspondiente e inicializa sus valores en NULL.
nodo_t* crear_nodo(void* elemento){
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo){
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;
	return nuevo_nodo;
}

//Pre: Tanto el nodo como la lista son validos.
/*Post: Inserta el nodo al final de la lista, y lo fija como nodo fin o nodo inicio segun corresponda. 
		Aumenta la cantidad en uno.*/
void insertar_nodo_en_final(lista_t* lista, nodo_t* nuevo_nodo){
	if(lista_vacia(lista)){
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
	}else{
		lista->nodo_fin->siguiente = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
		nuevo_nodo->siguiente = NULL;
	}

	lista->cantidad = lista->cantidad + 1;
}

int lista_insertar(lista_t* lista, void* elemento){
	if(!lista){
		return -1;
	}
	nodo_t* nuevo_nodo = crear_nodo(elemento);
	if(!nuevo_nodo){
		return -1;
	}
	insertar_nodo_en_final(lista, nuevo_nodo);
	return 0;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!lista || lista->cantidad <= posicion){
		return NULL;
	}
	nodo_t* nodo_auxiliar = lista->nodo_inicio;
	for(int i = 0; i < posicion; i++){
		nodo_auxiliar = nodo_auxiliar->siguiente;
	}

	return nodo_auxiliar->elemento;
}
//Pre:Tanto la lista como el nodo son validos.
//Post: Inserta el nodo al principio, y lo fija como el nodo inicio. Aumenta la cantidad en uno.
void insertar_nodo_en_inicio(lista_t* lista, nodo_t* nuevo_nodo){
	nuevo_nodo->siguiente = lista->nodo_inicio;
	lista->nodo_inicio = nuevo_nodo;
	lista->cantidad = lista->cantidad + 1;
}

//Pre: Tanto la lista, el nodo y la posicion(Tiene que estar entre nodo inicio y nodo final) son validos.
//Post: Inserta el nodo en la posicion deseada. Aumenta la cantidad en uno.
void insertar_nodo_en_posicion(lista_t* lista, nodo_t* nuevo_nodo, size_t posicion){
		
	nodo_t* nodo_auxiliar = lista->nodo_inicio;
	for(int i = 1; i < posicion; i++){
		nodo_auxiliar = nodo_auxiliar->siguiente;
	}
	nuevo_nodo->siguiente = nodo_auxiliar->siguiente;
	nodo_auxiliar->siguiente = nuevo_nodo;
	lista->cantidad = lista->cantidad + 1;

}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista){
		return -1;
	}
	if(lista->cantidad <= posicion){
		return lista_insertar(lista, elemento);
	}

	nodo_t* nuevo_nodo = crear_nodo(elemento);
	if(!nuevo_nodo){
			return -1;
	}

	if(posicion == 0 && !lista_vacia(lista)){
		insertar_nodo_en_inicio(lista, nuevo_nodo);
		return 0;
	}else{	
		insertar_nodo_en_posicion(lista, nuevo_nodo, posicion);
		return 0;
	}
}

size_t lista_elementos(lista_t* lista){
	if(!lista){
		return 0;
	}
	return lista->cantidad;
}

void* lista_ultimo(lista_t* lista){
	if(!lista || lista_vacia(lista)){
		return NULL;
	}

	return lista->nodo_fin->elemento;
}
//Pre: La lista es valida.
/*Post: Elimina el nodo que esta al final de la lista. Hay diferencias si el nodo es el unico elemento de la lista 
	  	o no. Decrece la cantidad en uno*/
void borrar_nodo_en_final(lista_t* lista, bool destruir_elemento){
	nodo_t* nodo_auxiliar = lista->nodo_inicio;

	if(lista->destructor && destruir_elemento){
		lista->destructor(lista->nodo_fin->elemento);
	}

	if(lista_elementos(lista) == 1){
		free(nodo_auxiliar);
		lista->nodo_fin = NULL;
		lista->nodo_inicio = NULL;
	}else{
		for (int i = 1; i < lista_elementos(lista) - 1; ++i){
			nodo_auxiliar = nodo_auxiliar->siguiente;
		}
		lista->nodo_fin = nodo_auxiliar;
		free(nodo_auxiliar->siguiente);
		nodo_auxiliar->siguiente = NULL;	
	}	
	lista->cantidad = lista->cantidad - 1;
}
int lista_borrar(lista_t* lista, bool destruir_elemento){
	if(!lista || lista_vacia(lista)){
		return -1;
	}
	
	borrar_nodo_en_final(lista, destruir_elemento);

	return 0;
}
//Pre:La lista es valida.
//Post: Elimina el nodo que esta al principio, fijando el nodo inicio a su siguiente. Decrece la cantidad por uno.
void borrar_nodo_en_inicio(lista_t* lista, bool destruir_elemento){
	nodo_t* nodo_auxiliar = lista->nodo_inicio;
	lista->nodo_inicio = nodo_auxiliar->siguiente;

	if(lista->destructor && destruir_elemento){
		lista->destructor(nodo_auxiliar->elemento);
	}

	free(nodo_auxiliar);
	lista->cantidad = lista->cantidad - 1;
}
//Pre: La lista y la posicion son validos.
//Post: Elimina el nodo en la posicion correspondiente.
void borrar_nodo_en_posicion(lista_t* lista, size_t posicion, bool destruir_elemento){
	nodo_t* nodo_auxiliar = lista->nodo_inicio;
	nodo_t* ptr_a_nodo_a_borrar;
	for(int i = 1; i < posicion; i++){
		nodo_auxiliar = nodo_auxiliar->siguiente;
	}
	ptr_a_nodo_a_borrar = nodo_auxiliar->siguiente;
	nodo_auxiliar->siguiente = ptr_a_nodo_a_borrar->siguiente;
	
	if(lista->destructor && destruir_elemento){
		lista->destructor(ptr_a_nodo_a_borrar->elemento);
	}

	free(ptr_a_nodo_a_borrar);
	lista->cantidad = lista->cantidad - 1;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion, bool destruir_elemento){
	if(!lista || lista_vacia(lista)){
		return -1;
	}
	if(lista_elementos(lista) <= posicion || lista_elementos(lista) == 1){
		return lista_borrar(lista, destruir_elemento);
	}
	
	if(posicion == 0){
		borrar_nodo_en_inicio(lista, destruir_elemento);
	}else{
		borrar_nodo_en_posicion(lista, posicion, destruir_elemento);
	}

	return 0;
}

int lista_apilar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista, bool destruir_elemento){
	return lista_borrar(lista, destruir_elemento);
}
void* lista_tope(lista_t* lista){
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_fin->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista, bool destruir_elemento){
	if(!lista || lista_vacia(lista)){
		return -1;
	}
	borrar_nodo_en_inicio(lista, destruir_elemento);
	return 0;
}

void* lista_primero(lista_t* lista){
	if(!lista || lista_vacia(lista)){
		return NULL;
	}

	return lista->nodo_inicio->elemento;
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista){
		return NULL;
	}

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador){
		return NULL;
	}
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador){
		return false;
	}
	return (iterador->corriente);
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!iterador){
		return false;
	}
	if(iterador->corriente){
		if(iterador->corriente->siguiente == NULL){
			iterador->corriente = iterador->corriente->siguiente;
			return false;
		}
		iterador->corriente = iterador->corriente->siguiente;
		return true;
	}
	return false;
}
void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente){
		return NULL;
	}
	return iterador->corriente->elemento;
}
void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}
size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	if(!lista || !funcion || lista_vacia(lista)){
		return 0;
	}
	nodo_t* nodo_auxiliar = lista->nodo_inicio;
	size_t contador = 1;

	while(funcion(nodo_auxiliar->elemento, contexto) &&  (contador < lista_elementos(lista))){
		nodo_auxiliar = nodo_auxiliar->siguiente;
		contador++;
	}
	return contador;
}