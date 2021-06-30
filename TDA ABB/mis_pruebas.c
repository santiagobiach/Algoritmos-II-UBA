#include "abb.h"
#include <stdio.h>
#include <string.h>
#include "pa2mm.h"

const int EXITO = 0;
const int ERROR = -1;

typedef struct libro{
	char titulo[100];
	int peso;
	int paginas;
}libro_t;

int comparar_libros_por_paginas(void* libro_1, void* libro_2){
	if(!libro_1 || !libro_2){
		return 0;
	}
	if(((libro_t*)libro_1)->paginas > ((libro_t*)libro_2)->paginas)
        return 1;
    if(((libro_t*)libro_1)->paginas < ((libro_t*)libro_2)->paginas)
        return -1;
    return 0;
}

void probar_creacion_arbol(){
	abb_t* abb = NULL;

	pa2m_afirmar((abb=arbol_crear(NULL, NULL)) == NULL, "Si le paso un comparador NULL, devuelve NULL");
	pa2m_afirmar((abb=arbol_crear(comparar_libros_por_paginas, NULL)) != NULL, "Puedo crear un arbol");
	pa2m_afirmar(abb->nodo_raiz == NULL, "El nodo raiz apunta a NULL");
	pa2m_afirmar(abb->comparador == comparar_libros_por_paginas, "El comparador es el que pasamos por parametro");
	pa2m_afirmar(abb->destructor== NULL, "El destructor es NULL");

	arbol_destruir(abb);
}
libro_t crear_libro(char titulo[100], int peso, int paginas){
	libro_t nuevo_libro;
	strcpy(nuevo_libro.titulo, titulo);
	nuevo_libro.peso = peso;
	nuevo_libro.paginas = paginas;

	return nuevo_libro;
}

void probar_insercion_en_arbol(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_3 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_1 = crear_libro("Cien años de soledad", 2 , 437);

	

	pa2m_afirmar((arbol_insertar(abb, &libro_1)) == EXITO, "Pude insertar un elemento");
	
	pa2m_afirmar((arbol_vacio(abb)) == false, "El arbol no esta vacio");
	pa2m_afirmar((arbol_raiz(abb)) == &libro_1, "La raiz del arbol es la correcta");
	pa2m_afirmar((arbol_insertar(abb, &libro_2)) == EXITO, "Pude insertar otro elemento");
	pa2m_afirmar(((libro_t*)((abb->nodo_raiz)->derecha)->elemento) == &libro_2, 
				 "El nodo es correctamente insertado a la derecha");
	pa2m_afirmar((arbol_insertar(abb, &libro_3)) == EXITO, "Pude insertar un tercer elemento");
	pa2m_afirmar(((libro_t*)((abb->nodo_raiz)->izquierda)->elemento) == &libro_3, 
				 "El nodo es correctamente insertado a la izquierda");

	pa2m_afirmar((arbol_buscar(abb, &libro_2)) == &libro_2, "Busque y encontre el libro correcto");
	pa2m_afirmar((arbol_buscar(abb, &libro_3)) == &libro_3, "Busque y encontre el libro correcto");


	arbol_destruir(abb);
}

void probar_arbol_raiz(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;
	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	int resultado;

	pa2m_afirmar((arbol_raiz(NULL)) == NULL, "La raiz de un arbol NULL es NULL");
	pa2m_afirmar((arbol_raiz(abb)) == NULL, "La raiz de un arbol vacio es NULL");
	resultado = arbol_insertar(abb, &libro_1);

	if(resultado == EXITO){
		pa2m_afirmar((arbol_raiz(abb)) == &libro_1, "La raiz del arbol es la correcta");
	}

	arbol_destruir(abb);
}

void probar_arbol_vacio(){

	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	int resultado;

	pa2m_afirmar((arbol_vacio(NULL)) == true, "UN arbol que no existe esta vacio");
	pa2m_afirmar((arbol_vacio(abb)) == true, "Si el arbol esta vacio devuelve true");

	resultado = arbol_insertar(abb, &libro_1);
	if(resultado == EXITO){
		pa2m_afirmar((arbol_vacio(abb)) == false, "Luego de insertar un elemento, el arbol ya no esta vacio");
	}
	arbol_destruir(abb);
}

void probar_buscar_elemento_en_arbol(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_aux = crear_libro("El pendulo de Foucault", 3, 824);
	int resultado;

	pa2m_afirmar((arbol_buscar(NULL, &libro_2)) == NULL, "Buscar en un arbol NULL devuelve NULL");
	pa2m_afirmar((arbol_buscar(abb, &libro_2)) == NULL, "Buscar en un arbol vacio devuelve NULL");

	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_4);
	if(resultado == EXITO){
		pa2m_afirmar((arbol_buscar(abb, &libro_1)) == &libro_1, "Busque y encontre el primer libro");
		pa2m_afirmar((arbol_buscar(abb, &libro_2)) == &libro_2, "Busque y encontre el segundo libro");
		pa2m_afirmar((arbol_buscar(abb, &libro_3)) == &libro_3, "Busque y encontre el tercer libro");
		pa2m_afirmar((arbol_buscar(abb, &libro_4)) == &libro_4, "Busque y encontre el cuarto libro");
	}

	pa2m_afirmar((arbol_buscar(abb, &libro_aux)) == NULL, "Buscar un libro que no esta en el arbol devuelve NULL");

	arbol_destruir(abb);
}
void probar_borrar_elemento_en_arbol(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Stoner", 1 , 242);
	libro_t libro_2 = crear_libro("El gigante enterrado", 1 , 353);
	libro_t libro_3 = crear_libro("After Dark", 1 , 210);
	libro_t libro_4 = crear_libro("La caza del carnero salvaje", 2 , 406);
	libro_t libro_5 = crear_libro("El señor de los anillos", 3, 824);
	libro_t libro_6 = crear_libro("El capitan Alatriste", 1, 321);
	libro_t libro_7 = crear_libro("El club de los negocios raros", 2, 380);
	libro_t libro_aux = crear_libro("Cometas en el cielo", 2, 351);
	int resultado;

	pa2m_afirmar((arbol_borrar(NULL, &libro_1)) == ERROR, "Borrar en un arbol NULL devuelve error");
	pa2m_afirmar((arbol_borrar(abb, &libro_1)) == ERROR, "Borrar en un arbol vacio devuelve error");

	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_6);
	resultado = arbol_insertar(abb, &libro_5);
	resultado = arbol_insertar(abb, &libro_7);


	if(resultado == EXITO){
		pa2m_afirmar((arbol_borrar(abb, &libro_aux)) == ERROR, "Intentar borrar un elemento que no existe devuelve ERROR");

		pa2m_afirmar((arbol_borrar(abb, &libro_5)) == EXITO, "Puedo borrar un nodo hoja");
		pa2m_afirmar((arbol_buscar(abb, &libro_5)) == NULL, "Buscar el libro borrado devuelve NULL")


		pa2m_afirmar((arbol_borrar(abb, &libro_4)) == EXITO, "Puedo borrar un nodo con un hijo");
		pa2m_afirmar((arbol_buscar(abb, &libro_4)) == NULL, "Buscar el libro borrado devuelve NULL");
		pa2m_afirmar(((libro_t*)((abb->nodo_raiz)->derecha)->elemento) == &libro_7, 
					 "El nodo eliminado es reemplazado por su hijo");

		pa2m_afirmar((arbol_borrar(abb, &libro_1)) == EXITO, "Puedo borrar un nodo con dos hijos");
		pa2m_afirmar((arbol_buscar(abb, &libro_1)) == NULL, "Buscar el libro borrado devuelve NULL");
		pa2m_afirmar(((libro_t*)((abb->nodo_raiz)->izquierda)->elemento) == &libro_3, 
					 "El nodo borrado es reemplazado por su predecesor inorden");

		pa2m_afirmar((arbol_borrar(abb, &libro_2)) == EXITO, "Puedo borrar la raiz, que tiene dos hijos");
		pa2m_afirmar((arbol_buscar(abb, &libro_2)) == NULL, "Buscar el libro borrado devuelve NULL");
		pa2m_afirmar(arbol_raiz(abb) == &libro_6, "El nodo borrado es reemplazado por su predecesor inorden");
		pa2m_afirmar((libro_t* )((abb->nodo_raiz)->izquierda)->elemento == &libro_3, 
				 	 "La raiz tiene a su izquierda el nodo correcto");
		pa2m_afirmar((libro_t* )((abb->nodo_raiz)->derecha)->elemento == &libro_7, 
			         "La raiz tiene a su derecha el nodo correcto");

		pa2m_afirmar((arbol_borrar(abb, &libro_3)) == EXITO, "Puedo borrar un nodo hoja");
		pa2m_afirmar((arbol_buscar(abb, &libro_3)) == NULL, "Buscar el libro borrado devuelve NULL");
		pa2m_afirmar(abb->nodo_raiz->izquierda == NULL, "La raiz tiene a su izquierda NULL");
		
		pa2m_afirmar((arbol_borrar(abb, &libro_7)) == EXITO, "Puedo borrar un nodo hoja");
		pa2m_afirmar((arbol_buscar(abb, &libro_7)) == NULL, "Buscar el libro borrado devuelve NULL");
		pa2m_afirmar(abb->nodo_raiz->derecha == NULL, "La raiz tiene a su derecha NULL");

		pa2m_afirmar((arbol_borrar(abb, &libro_6)) == EXITO, "Puedo borrar la raiz, que es el ultimo nodo del arbol");
		pa2m_afirmar((arbol_buscar(abb, &libro_6)) == NULL, "Buscar el libro borrado devuelve NULL");
		pa2m_afirmar(abb->nodo_raiz == NULL, "La raiz tiene es NULL");
		pa2m_afirmar(arbol_vacio(abb) == true, "El arbol esta vacio");

	}	

	arbol_destruir(abb);
}
void probar_borrar_raiz_del_arbol(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;
	libro_t libro_1 = crear_libro("Falcó", 1 , 296);
	libro_t libro_2 = crear_libro("El hombre que amaba a los perros", 3 , 633);
	libro_t libro_3 = crear_libro("El conde de Montecristo", 5 , 1232);
	libro_t libro_4 = crear_libro("El sueño del celta", 2 , 450);
	int resultado = 0;

	

	resultado = arbol_insertar(abb, &libro_1);

	pa2m_afirmar((arbol_borrar(abb, &libro_1)) == EXITO, "Borrar la raiz del arbol con un solo elemento da exito");
	pa2m_afirmar((arbol_vacio(abb)) == true, "El arbol esta vacio");
	pa2m_afirmar((arbol_raiz(abb)) == NULL, "La raiz del arbol es NULL");

	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);

	pa2m_afirmar((arbol_borrar(abb, &libro_1)) == EXITO, "Borrar la raiz del arbol con dos elemento da exito");
	pa2m_afirmar((arbol_vacio(abb)) == false, "El arbol no esta vacio");
	pa2m_afirmar((arbol_raiz(abb)) == &libro_2, "La raiz del arbol es la correcta");


	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_3);

	pa2m_afirmar((arbol_borrar(abb, &libro_2)) == EXITO, "Borrar la raiz del arbol con cuatro elemento da exito");
	pa2m_afirmar((arbol_vacio(abb)) == false, "El arbol no esta vacio");
	pa2m_afirmar((arbol_raiz(abb)) == &libro_4, "La raiz del arbol es la correcta");
	resultado = resultado;


	arbol_destruir(abb);
}

void probar_arbol_recorrido_inorden(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_5 = crear_libro("El pendulo de Foucault", 3, 824);
	libro_t* biblioteca[10];

	int resultado;
	size_t contador;

	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_5);

	if(resultado == EXITO){
		contador = arbol_recorrido_inorden(abb, (void** )biblioteca, 10);
		pa2m_afirmar((arbol_raiz(abb)) == &libro_3, "La raiz del arbol es la correcta");
		pa2m_afirmar(contador == 5, "Logro insertar 5 libros en el vector");
		pa2m_afirmar(biblioteca[0] == &libro_1, "El primer elemento es el correcto");
		pa2m_afirmar(biblioteca[1] == &libro_4, "El segundo elemento es el correcto");
		pa2m_afirmar(biblioteca[2] == &libro_3, "El tercer elemento es el correcto");
		pa2m_afirmar(biblioteca[3] == &libro_5, "El cuarto elemento es el correcto");
		pa2m_afirmar(biblioteca[4] == &libro_2, "El quinto elemento es el correcto");
		

	}

	
	arbol_destruir(abb);
}

void probar_arbol_recorrido_preorden(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;
	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_5 = crear_libro("El pendulo de Foucault", 3, 824);
	libro_t* biblioteca[10];

	int resultado;
	size_t contador;

	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_5);
	if(resultado == EXITO){
		contador = arbol_recorrido_preorden(abb, (void** )biblioteca, 10);
		pa2m_afirmar((arbol_raiz(abb)) == &libro_3, "La raiz del arbol es la correcta");
		pa2m_afirmar(contador == 5, "Logro insertar 5 libros en el vector");
		pa2m_afirmar(biblioteca[0] == &libro_3, "El primer elemento es el correcto");
		pa2m_afirmar(biblioteca[1] == &libro_1, "El segundo elemento es el correcto");
		pa2m_afirmar(biblioteca[2] == &libro_4, "El tercer elemento es el correcto");
		pa2m_afirmar(biblioteca[3] == &libro_2, "El cuarto elemento es el correcto");
		pa2m_afirmar(biblioteca[4] == &libro_5, "El quinto elemento es el correcto");

		for(int i = 0; i < 5; i++){
			printf("\nTitulos: %s\n", biblioteca[i]->titulo);
		}

	}

	
	arbol_destruir(abb);
}

void probar_arbol_recorrido_postorden(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_5 = crear_libro("El pendulo de Foucault", 3, 824);
	libro_t* biblioteca[10];

	int resultado;
	size_t contador;

	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_5);
	if(resultado == EXITO){
		contador = arbol_recorrido_postorden(abb, (void** )biblioteca, 10);
		pa2m_afirmar((arbol_raiz(abb)) == &libro_3, "La raiz del arbol es la correcta");
		pa2m_afirmar(contador == 5, "Logro insertar 5 libros en el vector");
		pa2m_afirmar(biblioteca[0] == &libro_4, "El primer elemento es el correcto");
		pa2m_afirmar(biblioteca[1] == &libro_1, "El segundo elemento es el correcto");
		pa2m_afirmar(biblioteca[2] == &libro_5, "El tercer elemento es el correcto");
		pa2m_afirmar(biblioteca[3] == &libro_2, "El cuarto elemento es el correcto");
		pa2m_afirmar(biblioteca[4] == &libro_3, "El quinto elemento es el correcto");
	

	}

	
	arbol_destruir(abb);
}
bool sumar_paginas(void* libro, void* sumatoria){
	if(libro && sumatoria){
        *(int*)sumatoria += ((libro_t*)libro)->paginas;
    }
    return false;
}
bool iterar_hasta_471(void* libro, void* extra){
	extra=extra;
    if(libro){
        
        if(((libro_t*)libro)->paginas == 471)
            return true;
    }
    return false;
}
void probar_iterador_interno_inorden(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_5 = crear_libro("El pendulo de Foucault", 3, 824);
	int resultado = 0;
	size_t contador;
	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_5);

	if(resultado == EXITO){
		int sumatoria = 0;
		contador = abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, sumar_paginas, &sumatoria);
		pa2m_afirmar(contador == 5, "Itero sobre 5 elementos");
		pa2m_afirmar(sumatoria == 2969, "La cantidad de paginas es 2969.");

		contador = abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, iterar_hasta_471, NULL);
		pa2m_afirmar(contador == 3, "Recorro hasta la raiz, itero sobre 3 elementos");
		
	}
	arbol_destruir(abb);
}

void probar_iterador_interno_preorden(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_5 = crear_libro("El pendulo de Foucault", 3, 824);
	int resultado = 0;
	size_t contador;
	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_5);

	if(resultado == EXITO){
		int sumatoria = 0;
		contador = abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, sumar_paginas, &sumatoria);
		pa2m_afirmar(contador == 5, "Itero sobre 5 elementos");
		pa2m_afirmar(sumatoria == 2969, "La cantidad de paginas es 2969.");

		contador = abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, iterar_hasta_471, NULL);
		pa2m_afirmar(contador == 1, "Recorro hasta la raiz, itero sobre 1 elementos");
		
	}
	arbol_destruir(abb);
}

void probar_iterador_interno_postorden(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Harry Potter y la Piedra Filosofal", 1 , 223);
	libro_t libro_2 = crear_libro("El camino de los reyes", 4 , 1106);
	libro_t libro_3 = crear_libro("Cien años de soledad", 2 , 471);
	libro_t libro_4 = crear_libro("Klaus y Lucas", 2 , 345);
	libro_t libro_5 = crear_libro("El pendulo de Foucault", 3, 824);
	int resultado = 0;
	size_t contador;
	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_5);

	if(resultado == EXITO){
		int sumatoria = 0;
		contador = abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, sumar_paginas, &sumatoria);
		pa2m_afirmar(contador == 5, "Itero sobre 5 elementos");
		pa2m_afirmar(sumatoria == 2969, "La cantidad de paginas es 2969.");

		contador = abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, iterar_hasta_471, NULL);
		pa2m_afirmar(contador == 5, "Recorro hasta la raiz, itero sobre 5 elementos");
		
	}
	arbol_destruir(abb);
}
void probar_iterador_interno_con_null(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_POSTORDEN, iterar_hasta_471, NULL) == 0, 
				 "No puedo iterar sobre un arbol nulo");
	pa2m_afirmar(abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, NULL, NULL) == 0, 
				 "No puedo iterar con una funcion nula");

	arbol_destruir(abb);

}
void probar_operaciones_en_conjunto(){
	abb_t* abb = arbol_crear(comparar_libros_por_paginas, NULL);
	if(!abb) return;

	libro_t libro_1 = crear_libro("Eragon", 3 , 702);
	libro_t libro_2 = crear_libro("Nacidos de la Bruma", 3 , 512);
	libro_t libro_3 = crear_libro("El laberinto de los espiritus", 4 , 810);
	libro_t libro_4 = crear_libro("1Q84", 3 , 511);
	libro_t libro_5 = crear_libro("El club Dante", 3, 410);
	libro_t libro_6 = crear_libro("Las aventuras de Arthur Gordon Pym", 1, 192);
	int resultado;

	resultado = arbol_insertar(abb, &libro_4);
	resultado = arbol_insertar(abb, &libro_2);
	resultado = arbol_insertar(abb, &libro_5);
	pa2m_afirmar(resultado == 0, "Inserte con exito tres elementos en el arbol");
	pa2m_afirmar(arbol_raiz(abb) == &libro_4, "La raiz es la correcta");
	pa2m_afirmar((arbol_buscar(abb, &libro_2)) == &libro_2, "Busque y encontre el elemento deseado");
	pa2m_afirmar((arbol_borrar(abb, &libro_2)) == EXITO, "Pude borrar un elemento");
	pa2m_afirmar((arbol_buscar(abb, &libro_2)) ==NULL, "Buscar el elemento borrado devuelve NULL");
	pa2m_afirmar((arbol_borrar(abb, &libro_4)) == EXITO, "Borro la raiz");
	pa2m_afirmar(arbol_raiz(abb) == &libro_5, "La nueva raiz es la correcta");
	pa2m_afirmar((arbol_borrar(abb, &libro_5)) == EXITO, "Borro la raiz");
	pa2m_afirmar((arbol_vacio(abb)) == true, "El arbol esta vacio");
	pa2m_afirmar((arbol_raiz(abb)) == NULL, "La raiz es NULL");
	resultado = arbol_insertar(abb, &libro_1);
	resultado = arbol_insertar(abb, &libro_3);
	resultado = arbol_insertar(abb, &libro_6);
	pa2m_afirmar(resultado == 0, "Inserte con exito otros tres elementos en el arbol");
	pa2m_afirmar((arbol_raiz(abb)) == &libro_1, "La raiz es la correcta");
	pa2m_afirmar((arbol_borrar(abb, &libro_1)) == EXITO, "Borro la raiz");
	pa2m_afirmar((arbol_buscar(abb, &libro_1)) ==NULL, "Buscar el elemento borrado devuelve NULL");
	pa2m_afirmar(arbol_raiz(abb) == &libro_6, "La nueva raiz es la correcta");
	
	arbol_destruir(abb);
}
int main(){

	pa2m_nuevo_grupo("PRUEBAS DE CREACION ARBOL");
	probar_creacion_arbol();

	pa2m_nuevo_grupo("PRUEBAS DE INSERCION");
	probar_insercion_en_arbol();

	pa2m_nuevo_grupo("PRUEBAS DE ARBOL RAIZ");
	probar_arbol_raiz();

	pa2m_nuevo_grupo("PRUEBAS DE ARBOL VACIO");
	probar_arbol_vacio();

	pa2m_nuevo_grupo("PRUEBAS DE BUSCAR ELEMENTO EN ARBOL");
	probar_buscar_elemento_en_arbol();

	pa2m_nuevo_grupo("PRUEBAS DE BORRAR ELEMENTO DEL ARBOL");
	probar_borrar_elemento_en_arbol();

	pa2m_nuevo_grupo("PRUEBAS DE BORRAR RAIZ DEL ARBOL");
	probar_borrar_raiz_del_arbol();

	pa2m_nuevo_grupo("PRUEBAS DE ARBOL RECORRIDO INORDEN");
	probar_arbol_recorrido_inorden();

	pa2m_nuevo_grupo("PRUEBAS DE ARBOL RECORRIDO PREORDEN");
	probar_arbol_recorrido_preorden();

	pa2m_nuevo_grupo("PRUEBAS DE ARBOL RECORRIDO POSTORDEN");
	probar_arbol_recorrido_postorden();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO CON NULL");
	probar_iterador_interno_con_null();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO INORDEN");
	probar_iterador_interno_inorden();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO PREORDEN");
	probar_iterador_interno_preorden();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO POSTORDEN");
	probar_iterador_interno_postorden();

	pa2m_nuevo_grupo("PRUEBAS DE OPERACIONES EN CONJUNTO");
	probar_operaciones_en_conjunto();

	pa2m_mostrar_reporte();

	return 0;
}