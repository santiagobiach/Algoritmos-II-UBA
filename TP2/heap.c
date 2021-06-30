#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int posicion_padre(int n){
	return (n-1)/2;
}
int posicion_hijo_izquierda(int n){
	return 2*n+1;
}

int posicion_hijo_derecha(int n){
	return 2*n+2;
}
void swap(void** vector, int posicion_1, int posicion_2){
	void* aux = vector[posicion_1];
	vector[posicion_1] = vector[posicion_2];
	vector[posicion_2] = aux;
}

void sift_up(heap_t* heap, int n){
	if(n==0){
		return;
	}
	int padre = posicion_padre(n);
	int comparacion = heap->comparador(heap->vector[n], heap->vector[padre]);

	if(comparacion < 0){
		swap(heap->vector, n, padre);
		sift_up(heap, padre);
	}
}
void sift_down(heap_t* heap, int n){
	int hijo_der = posicion_hijo_derecha(n);
	int hijo_izq = posicion_hijo_izquierda(n);
	int pos_menor = hijo_izq;
	int comparacion;

	if(hijo_izq >= heap->tope){
		return;
	}
	if(hijo_der < heap->tope){
		comparacion = heap->comparador(heap->vector[hijo_der], heap->vector[hijo_izq]);
		if(comparacion < 0){
			pos_menor = hijo_der;
		}
	}	
	comparacion = heap->comparador(heap->vector[pos_menor], heap->vector[n]);
	if(comparacion < 0){
		swap(heap->vector, n, pos_menor);
		sift_down(heap, pos_menor);
	}else{
		
	}
}

heap_t* heap_crear(heap_comparador comparador, heap_destructor destructor){

	if(!comparador){
		return NULL;
	}
	heap_t* puntero_heap = malloc(sizeof(heap_t));
	if(!puntero_heap){
		return NULL;
	}
	puntero_heap->tope = 0;
	puntero_heap->vector = NULL;
	puntero_heap->comparador = comparador;
	puntero_heap->destructor = destructor;

	return puntero_heap;
}

int heap_insertar(heap_t* heap, void* elemento){
	if(!heap){
		return -1;
	}
	void** aux = realloc(heap->vector, sizeof(void*) * (unsigned)(heap->tope+1));
	if(!aux){
		return -1;
	}
	
	heap->vector = aux;
	heap->vector[heap->tope] = elemento;
	heap->tope++;

	sift_up(heap, heap->tope-1);
	return 0;
}

void heap_destruir(heap_t* heap){
	if(!heap){
		return;
	}
	if(heap->destructor){
		for(int i = 0; i < heap->tope;i++){
			heap->destructor(heap->vector[i]);
		}
	}
	if(heap->vector != NULL){
		free(heap->vector);
	}
	

	free(heap);
}

void* heap_raiz(heap_t* heap){
	if(!heap || heap->tope == 0){
		return NULL;
	}
	return heap->vector[0];
}

void* heap_extraer_raiz(heap_t* heap){
	if(!heap || heap->tope == 0){

		return NULL;
	}
	void* raiz = heap->vector[0];
	heap->tope--;
	if(heap->tope != 0){
		heap->vector[0] = heap->vector[heap->tope];
		void** aux = realloc(heap->vector, sizeof(void*) * (unsigned)(heap->tope));
		if(!aux){
			return NULL;
		}
		heap->vector = aux;
		sift_down(heap, 0);
		
	}
	return raiz;
}

int heap_elementos(heap_t* heap){
	if(!heap){
		return 0;
	}
	return heap->tope;
}