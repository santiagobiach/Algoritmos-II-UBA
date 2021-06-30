#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>
#include <stdlib.h>


typedef int (*heap_comparador)(void*, void*);

typedef void (*heap_destructor)(void*);


typedef struct heap{
	void** vector;
	int tope;
	heap_comparador comparador;
  	heap_destructor destructor;
}heap_t;

//Pre:-
//Post: Crea el heap, reservando la memoria necesaria.
heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor);

//Pre:El heap es valido.
//Post: Inserta el elemento en el heap y lo guarda en la posicion que le corresponde. Devuelve 0 si lo logro, -1 si no.
int heap_insertar(heap_t* heap, void* elemento);

//Pre: El heap es valido.
//Post: Devuelve la raiz o NULL si no la hay. A su vez, la saca del heap.
void* heap_extraer_raiz(heap_t* heap);

//Pre: El heap es valido.
//Post: Devuelve la raiz o NULL si no la hay.
void* heap_raiz(heap_t* heap);

//Pre:-
//Post: Destruye el heap, liberando la memoria reservada.
void heap_destruir(heap_t* heap);

//Pre: El heap es valido.
//Post: La cantidad de elementos que tiene el heap.
int heap_elementos(heap_t* heap);

#endif /* __HEAP_H__*/