#ifndef __ESTRUCTURAS_H__
#define __ESTRUCTURAS_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 500

typedef int (*funcion_batalla)(void*, void*);

typedef struct pokemon{
	char especie[MAX_NOMBRE];
	int velocidad;
	int defensa;
	int ataque;
	int contador;	
}pokemon_t;

typedef struct entrenador{
	char nombre_entrenador[MAX_NOMBRE];
	lista_t* pokemones;
	bool es_lider;
}entrenador_t;

typedef struct gimnasio{
	char nombre_gimnasio[MAX_NOMBRE];
	int dificultad;
	funcion_batalla batalla;
	lista_t* entrenadores; //Va a funcionar como una pila!
	char descripcion_batalla[MAX_DESCRIPCION];
}gimnasio_t;


//Pre:-
/*Post: Crea un pokemon,reservando la memoria necesaria. Devuelve su puntero o NULL si los parametros son invalidos.
  		(Velocidad, defensa y ataque tienen que ser mayores a 0, especie debe tener un largo mayor a 0)*/
pokemon_t* crear_pokemon(int velocidad, int defensa, int ataque, char especie[MAX_NOMBRE]);

//Pre:-
//Post: Devuelve 0 si pudo mejorar al pokemon, -1 si no lo pudo hacer.
int mejorar_pokemon(pokemon_t* pokemon);

//Pre:-
//Post: Elimina al pokemon, liberando la memoria que tenia reservada.
void eliminar_pokemon(void* pokemon);


//Pre:-
/*Post: Crea un entrenador,reservando la memoria necesaria. Devuelve su puntero o NULL si los parametros son invalidos.
  		(Su nombre debe tener un largo mayor a 0)*/
entrenador_t* crear_entrenador(char nombre[MAX_NOMBRE], bool es_lider);

//Pre: El pokemon y el entrenador deben ser validos.
//Post:Carga al pokemon en la lista de pokemones del entrenador. Devuelve 0 si lo hizo con exito, -1 si no.
int cargar_pokemones_en_entrenador(entrenador_t* entrenador, pokemon_t* pokemon);

//Pre: El entrenador es valido.
//Post: La cantidad de pokemones que tiene el entrenador.
size_t cantidad_pokemones(entrenador_t* entrenador);

//Pre: El entrenador es valido.
//Post: Devuelve el pokemon que esta en la posicion pedida, o el ultimo si la posicion es mayor a la cantidad de pokemones.
pokemon_t* pokemon_en_posicion(entrenador_t* entrenador, size_t posicion);


//Pre: El entrenador es valido.
//Post: Imprime por pantalla la informacion del entrenador.
void mostrar_informacion_entrenador(entrenador_t* entrenador);

//Pre:-
//Post:Elimina al entrenador, liberando la memoria reservada por el mismo, y por sus pokemones.
void eliminar_entrenador(void* entrenador);

//Pre:-
/*Post: Crea un gimnasio,reservando la memoria necesaria. Devuelve su puntero o NULL si los parametros son invalidos.
  		(Su nombre debe tener un largo mayor a 0, la dificultad debe ser positiva, la funcion batalla debe ser distinto de NULL)*/
gimnasio_t* crear_gimnasio(char nombre[MAX_NOMBRE], int dificultad, funcion_batalla batalla, char descripcion_batalla[MAX_DESCRIPCION]);

//Pre: El entrenador y el gimnasio son validos.
//Post:Apila un entrenador en la pila de entrenadores del gimnasio. Devuelve 0 si lo hizo con exito, -1 si no.
int cargar_entrenadores_en_gimnasio(gimnasio_t* gimnasio, entrenador_t* entrenador);

//Pre: El gimnasio es valido.
//Post: Desapila al entrenador en el tope de la pila. Devuelve 0 si lo hizo con exito, -1 si no.
int desapilar_entrenadores_de_gimnasio(gimnasio_t* gimnasio, bool destruir_entrenador);

//Pre: El gimnasio es valido.
//Post: Devuelve el entrenador que esta en el tope, o NULL si ya no quedan entrenadores.
entrenador_t* entrenador_en_tope(gimnasio_t* gimnasio);

//Pre: El gimnasio es valido.
//Post: La cantidad de entrenadores que tiene el gimnasio.
size_t cantidad_entrenadores(gimnasio_t* gimnasio);

//Pre: El gimnasio es valido.
//Post: Imprime por pantalla la informacion del gimnasio.
void mostrar_informacion_gimnasio(gimnasio_t* gimnasio);

//Pre:-
//Post:Elimina el gimnasio, liberando la memoria reservada por este, sus entrenadores y sus pokemones.
void eliminar_gimnasio(void* gimnasio);

#endif /* __ESTRUCTURAS_H__*/