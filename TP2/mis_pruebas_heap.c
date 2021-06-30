#include "heap.h"
#include <stdio.h>
#include <string.h>
#include "pa2mm.h"

int comparar_numeros(void* numero_1, void* numero_2){
	if(*(int*)numero_1 > *(int*)numero_2){
		return 1;
	}
	return -1;
}
void probar_creacion_heap(){
	heap_t* heap = NULL;

	pa2m_afirmar((heap=heap_crear(NULL, NULL)) == NULL, "Si le paso un comparador NULL, devuelve NULL");
	pa2m_afirmar((heap=heap_crear(comparar_numeros, NULL)) != NULL, "Puedo crear un heap");
	pa2m_afirmar(heap->comparador == comparar_numeros, "El comparador es el que pasamos por parametro");
	pa2m_afirmar(heap->destructor== NULL, "El destructor es NULL");

	heap_destruir(heap);
}	
void probar_insercion_heap(){
	heap_t* heap = heap_crear(comparar_numeros, NULL);
	int un_numero = 8;
	int otro_numero = 5;
	int otro_numero_mas = 7;

	pa2m_afirmar(heap_insertar(NULL, &un_numero)== -1, "Insertar en un heap NULL devuelve error");
	pa2m_afirmar(heap_insertar(heap, &un_numero)== 0, "Puedo insertar un numero en un heap vacio");
	pa2m_afirmar(heap_insertar(heap, &otro_numero)== 0, "Puedo insertar otro numero en el heap");
	pa2m_afirmar(heap_insertar(heap, &otro_numero_mas)== 0, "Puedo insertar un tercer numero en el heap");
	pa2m_afirmar(*(int*)heap_raiz(heap)== otro_numero, "La raiz es la correcta");
	pa2m_afirmar(*(int*)(heap->vector[1])== un_numero, "El hijo izquierdo es el correcto");
	pa2m_afirmar(*(int*)(heap->vector[2])== otro_numero_mas, "El hijo derecho es el correcto");


	heap_destruir(heap);
}

void probar_raiz_heap(){
	heap_t* heap = heap_crear(comparar_numeros, NULL);
	int un_numero = 3;
	int otro_numero = 2;
	int otro_numero_mas = 1;

	pa2m_afirmar(heap_raiz(heap)== NULL, "La raiz de un heap vacio es NULL");
	int resultado = heap_insertar(heap, &un_numero);
	if(resultado == -1){
		return;
	}
	pa2m_afirmar(*(int*)heap_raiz(heap)== un_numero, "La raiz es la correcta");
	resultado = heap_insertar(heap, &otro_numero);
	if(resultado == -1){
		return;
	}
	pa2m_afirmar(*(int*)heap_raiz(heap)== otro_numero, "La raiz es la correcta");
	resultado = heap_insertar(heap, &otro_numero_mas);
	if(resultado == -1){
		return;
	}
	pa2m_afirmar(*(int*)heap_raiz(heap)== otro_numero_mas, "La raiz es la correcta");

	heap_destruir(heap);
}
void probar_extraer_raiz_heap(){
	heap_t* heap = heap_crear(comparar_numeros, NULL);
	int a = 5;
	int b = 8;
	int c = 4;
	int d = 10;
	int e = 14;
	int f = 2;

	pa2m_afirmar(heap_extraer_raiz(heap)== NULL, "Intentar extraer la raiz de un heap vacio devuelve NULL");
	int resultado = heap_insertar(heap, &a);
	resultado = heap_insertar(heap, &b);
	resultado = heap_insertar(heap, &c);
	resultado = heap_insertar(heap, &d);
	resultado = heap_insertar(heap, &e);
	resultado = heap_insertar(heap, &f);
	if(resultado == -1){
		return;
	}
	pa2m_afirmar(heap_extraer_raiz(heap)== &f, "El elemento extraido es el correcto");
	pa2m_afirmar(heap_raiz(heap)== &c, "La raiz es la correcta");
	pa2m_afirmar(heap_extraer_raiz(heap)== &c, "El elemento extraido es el correcto");
	pa2m_afirmar(heap_raiz(heap)== &a, "La raiz es la correcta");
	pa2m_afirmar(heap_extraer_raiz(heap)== &a, "El elemento extraido es el correcto");
	pa2m_afirmar(heap_raiz(heap)== &b, "La raiz es la correcta");
	pa2m_afirmar(heap_extraer_raiz(heap)== &b, "El elemento extraido es el correcto");
	pa2m_afirmar(heap_raiz(heap)== &d, "La raiz es la correcta");
	pa2m_afirmar(heap_extraer_raiz(heap)== &d, "El elemento extraido es el correcto");
	pa2m_afirmar(heap_raiz(heap)== &e, "La raiz es la correcta");
	pa2m_afirmar(heap_extraer_raiz(heap)== &e, "El elemento extraido es el correcto");
	pa2m_afirmar(heap_raiz(heap)== NULL, "Como el heap esta vacio, la raiz es NULL");
	pa2m_afirmar(heap_extraer_raiz(heap)== NULL, "Extraer la raiz de un heap vacio devuelve NULL");


	heap_destruir(heap);
}


int main(){
	pa2m_nuevo_grupo("PRUEBAS DE CREACION HEAP");
	probar_creacion_heap();

	pa2m_nuevo_grupo("PRUEBAS DE INSERCION HEAP");
	probar_insercion_heap();

	pa2m_nuevo_grupo("PRUEBAS DE RAIZ HEAP");
	probar_raiz_heap();

	pa2m_nuevo_grupo("PRUEBAS DE EXTRAER RAIZ HEAP");
	probar_extraer_raiz_heap();

	pa2m_mostrar_reporte();

	return 0;
}