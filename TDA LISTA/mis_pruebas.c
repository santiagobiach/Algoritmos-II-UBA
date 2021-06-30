#include "lista.h"
#include "pa2mm.h"
#include <stdio.h>

const int EXITO = 0;
const int ERROR = -1;

void probar_creacion_lista(){
	lista_t* lista = NULL;

	pa2m_afirmar((lista=lista_crear()) != NULL, "Puedo crear una lista");
	pa2m_afirmar(lista->nodo_inicio == NULL, "El nodo inicio apunta a NULL");
	pa2m_afirmar(lista->nodo_fin == NULL, "El nodo final apunta a NULL");
	pa2m_afirmar(lista->cantidad == 0, "La capacidad es 0");

	lista_destruir(lista);
}
void probar_insercion_al_final(){
	lista_t* lista = NULL;
	lista = lista_crear();
	if(!lista) return;
	int resultado = 0;
	int a = 2, b = 4, c = 7, d = 10;

	resultado = lista_insertar(NULL, &a);
	pa2m_afirmar((resultado == ERROR), "Intentar insertar en una lista NULL deberia fallar");
	pa2m_afirmar(lista_elementos(lista) == 0, "La cantidad debe ser 0");

	resultado = lista_insertar(lista, &a);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar un elemento");
	pa2m_afirmar(lista_elementos(lista) == 1, "La lista tiene un elemento");
	

	resultado = lista_insertar(lista, &b);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar otro elemento");
	pa2m_afirmar(lista_elementos(lista) == 2, "La lista tiene dos elemento");

	resultado = lista_insertar(lista, &c);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar otro elemento mas");
	pa2m_afirmar(lista_elementos(lista) == 3, "La lista tiene tres elemento");

	resultado = lista_insertar(lista, &d);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar un cuarto elemento");
	pa2m_afirmar(lista_elementos(lista) == 4, "La lista tiene cuatro elemento");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &a ,"El primer elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &b ,"El segundo elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &c ,"El tercer elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == &d ,"El cuarto elemento es el correcto");

	lista_destruir(lista);
}

void probar_elementos_en_posicion(){
	lista_t* lista = NULL;
	lista = lista_crear();
	if(!lista) return;

	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL ,"Si intento usar una lista NULL devuelve NULL");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 20) == NULL ,
				 "Si intento ver el elemento de una posicion afuera de la lista devuelve NULL");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
				 "Si intento acceder a la posicion 0 de una lista vacia debe devolver NULL");


	lista_destruir(lista);
}

void probar_insercion_en_posicion(){
	lista_t* lista = NULL;
	lista = lista_crear();
	if(!lista) return;
	int resultado = 0;
	int a = 2, b = 4, c = 7, d = 10, e = 5;

	resultado = lista_insertar_en_posicion(NULL, &a, 0);
	pa2m_afirmar((resultado == ERROR), "Intentar insertar en una lista NULL deberia fallar");
	pa2m_afirmar(lista->cantidad == 0, "La cantidad debe ser 0");

	resultado = lista_insertar_en_posicion(lista, &a, 5);
	pa2m_afirmar((resultado == EXITO), "Puede insertar un elemento en una lista vacia en una posicion que no existe");
	pa2m_afirmar(lista->cantidad == 1, "La lista tiene un elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &a ,"El elemento es correctamente posicionado en el 0");

	resultado = lista_insertar_en_posicion(lista, &b, 1);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar otro elemento en la posicion 1, que no existe");
	pa2m_afirmar(lista->cantidad == 2, "La lista tiene dos elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &b ,"El elemento es correctamente posicionado al final");

	resultado = lista_insertar_en_posicion(lista, &c, 10);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar otro elemento mas en una posicion que no existe");
	pa2m_afirmar(lista->cantidad == 3, "La lista tiene tres elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &c ,"El elemento es correctamente posicionado al final");

	resultado = lista_insertar_en_posicion(lista, &d, 0);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar un elemento al principio de la lista");
	pa2m_afirmar(lista->cantidad == 4, "La lista tiene cuatro elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &d ,"El elemento es correctamente posicionado al inicio");

	resultado = lista_insertar_en_posicion(lista, &e, 3);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar un quinto elemento en la posicion tres, que ya existe");
	pa2m_afirmar(lista->cantidad == 5, "La lista tiene cinco elementos");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &d ,
				 "El elemento es correctamente posicionado en el tercer lugar");

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &d ,"El primer elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &a ,"El segundo elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &b ,"El tercer elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == &e ,"El cuarto elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == &c ,"El quinto elemento es el correcto");	

	lista_destruir(lista);
}

void probar_en_cantidad(){
	lista_t* lista = NULL;
	lista = lista_crear();
	if(!lista) return;

	int vector[50];
	int resultado = 0;
	int a = 25, b = 4, c = 21;

	for(int i = 0; i < 50 && resultado == EXITO;i++){
		vector[i] = i;
		resultado = lista_insertar(lista, &(vector[i]));
	}
	pa2m_afirmar((resultado == EXITO), "Pudo insertar 50 elementos en la lista");
	pa2m_afirmar((lista->cantidad == 50), "La cantidad de elementos es 50");

	for(int i = 0; i < lista->cantidad && resultado == EXITO; i++){
		if(*(int*)lista_elemento_en_posicion(lista, (size_t)i) != i){
			resultado = ERROR;
		}
	}
	pa2m_afirmar((resultado == EXITO), "Todos los elementos son correctos");

	resultado = lista_insertar_en_posicion(lista, &a, 25);
	pa2m_afirmar((resultado == EXITO), "Pudo insertar un elemento en la posicion 25 con exito");
	pa2m_afirmar((lista_elementos(lista) == 51), "La cantidad de elementos es 51");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 25) == &a ,"El elemento 25 es el correcto");	

	resultado = lista_insertar_en_posicion(lista, &b, 0);
	pa2m_afirmar((resultado == EXITO), "Pudo insertar un elemento en la posicion 0 con exito");
	pa2m_afirmar((lista_elementos(lista) == 52), "La cantidad de elementos es 52");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &b ,"El elemento 0 es el correcto");

	resultado = lista_insertar_en_posicion(lista, &c, 100);
	pa2m_afirmar((resultado == EXITO), "Puedo insertar un elemento si la posicion no existe");
	pa2m_afirmar((lista_elementos(lista)== 53), "La cantidad de elementos es 53");
	pa2m_afirmar(lista_ultimo(lista) == &c ,"El elemento es correctamente insertado al final");

	resultado = 0;
	for(int i = 0; i < 30 && resultado == EXITO;i++){
		resultado = lista_borrar_de_posicion(lista, 1);
	}		
	pa2m_afirmar((resultado == EXITO), "Puedo borrar 30 elementos en una posicion arbitraria");
	pa2m_afirmar((lista_elementos(lista) == 23), "Hay 23 elementos en la lista");
	lista_destruir(lista);
}
void probar_borrar(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int resultado = 0;
	int a = 20, b = 30, c = 12;
	pa2m_afirmar((resultado =lista_borrar(NULL)) == ERROR, "Borrar un nodo en una lista NULL debe devolver error");
	pa2m_afirmar((resultado =lista_borrar(lista)) == ERROR, "Borrar un nodo en una lista vacia debe devolver error");

	resultado = lista_insertar(lista, &a);
	resultado = lista_insertar(lista, &b);
	resultado = lista_insertar(lista, &c);

	pa2m_afirmar((resultado =lista_borrar(lista)) == EXITO, "Pudo borrar el ultimo nodo de una lista de tres");
	pa2m_afirmar((lista_elementos(lista)) == 2, "La cantidad es dos");
	pa2m_afirmar(lista_ultimo(lista) == &b, "El ultimo elemento es el correcto");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &a, "El primer elemento es el correcto");
	pa2m_afirmar((resultado =lista_borrar(lista)) == EXITO, "Pudo borrar el ultimo nodo de una lista de dos");
	pa2m_afirmar((lista_elementos(lista)) == 1, "La cantidad es uno");
	pa2m_afirmar(lista_ultimo(lista) == &a, "El ultimo elemento es el correcto");
	pa2m_afirmar(lista->nodo_fin == lista->nodo_inicio, "Como la cantidad es uno, nodo inicio y nodo fin deben ser iguales");
	pa2m_afirmar((resultado =lista_borrar(lista)) == EXITO, "Pudo borrar el ultimo nodo de una lista de uno");
	pa2m_afirmar((lista_elementos(lista)) == 0, "La cantidad es cero");
	pa2m_afirmar(lista->nodo_fin  == NULL, "Nodo fin debe ser NULL");
	pa2m_afirmar(lista->nodo_inicio  == NULL, "Nodo inicio debe ser NULL");
	lista_destruir(lista);
}

void probar_lista_elementos(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int resultado = 0;
	int vector[20];

	pa2m_afirmar(lista_elementos(NULL) == 0, "Los elementos de una lista NULL deben ser 0");
	pa2m_afirmar(lista_elementos(lista) == 0, "Los elementos de una lista vacia deben ser 0");

	
	for(int i = 0; i < 20 && resultado == EXITO;i++){
		vector[i] = i;
		resultado = lista_insertar(lista, &(vector[i]));
	}
	pa2m_afirmar(lista_elementos(lista) == 20, "Despues de insertar 20 elementos, la cantidad es 20");

	lista_destruir(lista);
}


void probar_lista_ultimo(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int resultado = 0;
	int vector[20];

	pa2m_afirmar(lista_ultimo(NULL) == NULL, "El ultimo elemento de una lista NULL debe ser NULL");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "El ultimo elemento de una lista vacia debe ser NULL");

	for(int i = 0; i < 20 && resultado == EXITO;i++){
		vector[i] = i;
		resultado = lista_insertar(lista, &(vector[i]));
	}

	pa2m_afirmar(*(int*)lista_ultimo(lista) == 19, "Luego de insertar 20 elementos, el ultimo es correcto");

	lista_destruir(lista);
}
void probar_borrar_en_posicion(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int resultado = 0;
	int a = 2, b = 4, c = 7, d = 10, e = 5;

	pa2m_afirmar((resultado =lista_borrar_de_posicion(NULL, 2)) == ERROR, 
				  "Borrar un nodo en una lista NULL debe devolver error");

	pa2m_afirmar((resultado =lista_borrar_de_posicion(lista, 2)) == ERROR, 
				  "Borrar un nodo en una lista vacia debe devolver error");
	
	resultado = lista_insertar(lista, &a);
	resultado = lista_insertar(lista, &b);
	resultado = lista_insertar(lista, &c);
	resultado = lista_insertar(lista, &d);
	resultado = lista_insertar(lista, &e);

	if(resultado != EXITO) return;


	pa2m_afirmar((resultado = lista_borrar_de_posicion(lista, 2)) == EXITO, "Pude borrar el elemento 2 de una lista de 5");
	pa2m_afirmar((lista_elementos(lista)) == 4, "La cantidad es cuatro");
	pa2m_afirmar((lista_elemento_en_posicion(lista, 2)) == &d, "El elemento en posicion 2 es el correcto");


	pa2m_afirmar((resultado = lista_borrar_de_posicion(lista, 0)) == EXITO, "Pude borrar el elemento 0 de una lista de 4");
	pa2m_afirmar((lista_elementos(lista)) == 3, "La cantidad es 3");	
	pa2m_afirmar((lista_elemento_en_posicion(lista, 0)) == &b, "El elemento en posicion 0 es el correcto");

	pa2m_afirmar((resultado = lista_borrar_de_posicion(lista, 21)) == EXITO, 
			      "Pude borrar un elemento si la posicion no existe");
	pa2m_afirmar((lista_elementos(lista)) == 2, "La cantidad es dos");	
	pa2m_afirmar((lista_ultimo(lista)) == &d, "El elemento en la ultima posicion es el correcto");

	pa2m_afirmar((resultado = lista_borrar_de_posicion(lista, 0)) == EXITO, 
			      "Pude borrar un elemento en la posicion 0");
	pa2m_afirmar((lista_elementos(lista)) == 1, "La cantidad es uno");	
	pa2m_afirmar((lista_elemento_en_posicion(lista, 0)) == &d, "El elemento en la primera posicion es el correcto");
	pa2m_afirmar(lista->nodo_fin == lista->nodo_inicio, 
				 "Como la cantidad es uno, nodo inicio y nodo fin deben ser iguales");

	pa2m_afirmar((resultado = lista_borrar_de_posicion(lista, 0)) == EXITO, 
			      "Pude borrar un elemento en la posicion 0");
	pa2m_afirmar((lista_vacia(lista)) == true, "La lista esta vacia");
	pa2m_afirmar(lista->nodo_fin  == NULL, "Nodo fin debe ser NULL");
	pa2m_afirmar(lista->nodo_inicio  == NULL, "Nodo inicio debe ser NULL");	
	lista_destruir(lista);
}

void probar_pila(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int resultado;
	int a = 2, b=3, c=4, d=5, e=6;

	pa2m_afirmar((resultado =lista_apilar(NULL, &a)) == ERROR, "Apilar en una lista NULL debe devolver error");

	pa2m_afirmar((resultado =lista_apilar(lista, &a)) == EXITO, "Pude apilar en una lista vacia");

	pa2m_afirmar((resultado =lista_apilar(lista, &b)) == EXITO, "Pude apilar en una lista con un elemento");

	pa2m_afirmar((resultado =lista_apilar(lista, &c)) == EXITO, "Pude apilar en una lista con dos elementos");

	pa2m_afirmar((resultado =lista_apilar(lista, &d)) == EXITO, "Pude apilar en una lista con tres elementos");

	pa2m_afirmar((resultado =lista_apilar(lista, &e)) == EXITO, "Pude apilar en una lista con cuatro elementos");

	pa2m_afirmar((lista_tope(lista)) == &e, "El elemento en el tope es el correcto");
	pa2m_afirmar((resultado =lista_desapilar(lista)) == EXITO, "Pude desapilar el elemento correctamente");

	pa2m_afirmar((lista_tope(lista)) == &d, "El elemento en el tope es el correcto");
	pa2m_afirmar((resultado =lista_desapilar(lista)) == EXITO, "Pude desapilar el elemento correctamente");

	pa2m_afirmar((lista_tope(lista)) == &c, "El elemento en el tope es el correcto");
	pa2m_afirmar((resultado =lista_desapilar(lista)) == EXITO, "Pude desapilar el elemento correctamente");

	pa2m_afirmar((lista_tope(lista)) == &b, "El elemento en el tope es el correcto");
	pa2m_afirmar((resultado =lista_desapilar(lista)) == EXITO, "Pude desapilar el elemento correctamente");

	pa2m_afirmar((lista_tope(lista)) == &a, "El elemento en el tope es el correcto");
	pa2m_afirmar((resultado =lista_desapilar(lista)) == EXITO, "Pude desapilar el elemento correctamente");

	pa2m_afirmar((lista_tope(lista)) == NULL, "El tope de una lista vacia es NULL");
	pa2m_afirmar((resultado = lista_desapilar(lista)) == ERROR, "Intentar desapilar una lista vacia debe devolver error");
	pa2m_afirmar((lista_tope(NULL)) == NULL, "El tope de una lista NULL es NULL");
	pa2m_afirmar((resultado = lista_desapilar(NULL)) == ERROR, "Intentar desapilar una lista NULL debe devolver error");

	lista_destruir(lista);							

}

void probar_cola(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int resultado;
	int a = 2, b=3, c=4, d=5, e=6;

	pa2m_afirmar((resultado =lista_encolar(NULL, &a)) == ERROR, "Encolar en una lista NULL debe devolver error");

	pa2m_afirmar((resultado =lista_encolar(lista, &a)) == EXITO, "Pude encolar en una lista vacia");

	pa2m_afirmar((resultado =lista_encolar(lista, &b)) == EXITO, "Pude encolar en una lista con un elemento");

	pa2m_afirmar((resultado =lista_encolar(lista, &c)) == EXITO, "Pude encolar en una lista con dos elementos");

	pa2m_afirmar((resultado =lista_encolar(lista, &d)) == EXITO, "Pude encolar en una lista con tres elementos");

	pa2m_afirmar((resultado =lista_encolar(lista, &e)) == EXITO, "Pude encolar en una lista con cuatro elementos");	

	pa2m_afirmar((lista_primero(lista)) == &a, "El primer elemento es el correcto");
	pa2m_afirmar((resultado =lista_desencolar(lista)) == EXITO, "Pude desencolar el elemento correctamente");

	pa2m_afirmar((lista_primero(lista)) == &b, "El primer elemento es el correcto");
	pa2m_afirmar((resultado =lista_desencolar(lista)) == EXITO, "Pude desencolar el elemento correctamente");

	pa2m_afirmar((lista_primero(lista)) == &c, "El primer elemento es el correcto");
	pa2m_afirmar((resultado =lista_desencolar(lista)) == EXITO, "Pude desencolar el elemento correctamente");

	pa2m_afirmar((lista_primero(lista)) == &d, "El primer elemento es el correcto");
	pa2m_afirmar((resultado =lista_desencolar(lista)) == EXITO, "Pude desencolar el elemento correctamente");

	pa2m_afirmar((lista_primero(lista)) == &e, "El primer elemento es el correcto");
	pa2m_afirmar((resultado =lista_desencolar(lista)) == EXITO, "Pude desencolar el elemento correctamente");

	pa2m_afirmar((lista_tope(lista)) == NULL, "El tope de una lista vacia es NULL");
	pa2m_afirmar((resultado = lista_desencolar(lista)) == ERROR, "Intentar desencolar una lista vacia debe devolver error");
	pa2m_afirmar((lista_tope(NULL)) == NULL, "El tope de una lista NULL es NULL");
	pa2m_afirmar((resultado = lista_desencolar(NULL)) == ERROR, "Intentar desencolar una lista NULL debe devolver error");

	lista_destruir(lista);							

}

void probar_iterador_externo(){
	lista_t* lista = lista_crear();

	lista_iterador_t* it = NULL;
	if(!lista) return;
	int resultado = 0;
	int contador = 0;
	int vector[10];

	for(int i = 0; i < 10 && resultado == EXITO;i++){
		vector[i] = i;
		resultado = lista_insertar(lista, &(vector[i]));
	}
	if(resultado == ERROR) return;

	pa2m_afirmar((it = lista_iterador_crear(lista)) != NULL, "Pude crear el iterador");

	while(lista_iterador_tiene_siguiente(it)){
		pa2m_afirmar(lista_iterador_elemento_actual(it) == &vector[contador], "El iterador apunta al nodo correcto");
		if(lista_iterador_elemento_actual(it) == lista_ultimo(lista)){
			pa2m_afirmar(lista_iterador_avanzar(it) == false, "Pudo avanzar correctamente");
		}else{
			pa2m_afirmar(lista_iterador_avanzar(it) == true, "Pudo avanzar correctamente");
		}
		
		contador++;
	}
	pa2m_afirmar(lista_iterador_tiene_siguiente(it) == false, "Como estamos al final, el iterador no tiene siguiente");
	pa2m_afirmar(lista_iterador_avanzar(it) == false, "Como estamos al final, intentar avanzar devuelve false");
	pa2m_afirmar(lista_iterador_elemento_actual(it) == NULL, "Como estamos al final, el elemento actual es NULL");
	lista_destruir(lista);
	lista_iterador_destruir(it);		
}
bool sumar_elemento(void* elemento, void* sumatoria){
    if(elemento && sumatoria)
       *(int*)sumatoria = *(int*)sumatoria + *(int*)elemento;
    return true;
}

void probar_iterador_interno(){
	lista_t* lista = lista_crear();
	if(!lista) return;
	int vector[10];
	int resultado = 0, sumatoria = 0;

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, NULL) == 0, "Mandar una lista vacia deberia devolver error");

	for(int i = 0; i < 10 && resultado == EXITO;i++){
		vector[i] = i;
		resultado = lista_insertar(lista, &(vector[i]));
	}
	if(resultado == ERROR) return;

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, NULL) == 0, "Mandar una funcion NULL deberia devolver error");
	pa2m_afirmar(lista_con_cada_elemento(lista, sumar_elemento, &sumatoria) == 10, "Pude iterar sobre toda al lista");
	pa2m_afirmar(sumatoria == 45, "La sumatoria de la lista es la correcta");

	lista_destruir(lista);
}

int main(){

	pa2m_nuevo_grupo("PRUEBAS DE CREACION LISTA");
	probar_creacion_lista();

	pa2m_nuevo_grupo("PRUEBAS INSERCION AL FINAL");
	probar_insercion_al_final();

	pa2m_nuevo_grupo("PRUEBAS ELEMENTOS EN POSICION");
	probar_elementos_en_posicion();

	pa2m_nuevo_grupo("PRUEBAS INSERCION EN POSICION");
	probar_insercion_en_posicion();

	pa2m_nuevo_grupo("PRUEBAS EN CANTIDAD");
	probar_en_cantidad();

	pa2m_nuevo_grupo("PRUEBAS DE BORRADO");
	probar_borrar();

	pa2m_nuevo_grupo("PRUEBAS DE LISTA ELEMENTOS");
	probar_lista_elementos();

	pa2m_nuevo_grupo("PRUEBAS DE LISTA ULTIMO");
	probar_lista_ultimo();

	pa2m_nuevo_grupo("PRUEBAS DE BORRADO EN POSICION");
	probar_borrar_en_posicion();

	pa2m_nuevo_grupo("PRUEBAS EN CANTIDAD");
	probar_en_cantidad();

	pa2m_nuevo_grupo("PRUEBAS DE PILA");
	probar_pila();

	pa2m_nuevo_grupo("PRUEBAS DE COLA");
	probar_cola();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR EXTERNO");
	probar_iterador_externo();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO");
	probar_iterador_interno();

	pa2m_mostrar_reporte();
	return 0;
}