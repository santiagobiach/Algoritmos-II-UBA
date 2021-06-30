#ifndef __JUEGO_H__
#define __JUEGO_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "heap.h"
#include "batallas.h"
#include "administrativas.h"

#define MAX_RUTA 100
#define MAX_LECTURA 100

typedef struct personaje{
	char nombre[MAX_NOMBRE];
	lista_t* pokemones_de_batalla;
	lista_t* pokemones_capturados;
	int medallas_obtenidas;
	int entrenadores_derrotados;
}personaje_t;

typedef struct juego{
	personaje_t* protagonista;
	heap_t* gimnasios;
	gimnasio_t* gimnasio_actual;
	entrenador_t* oponente_actual;
}juego_t;


//Pre: El nombre debe ser valido
//Post: Crea un personaje, reservando la memoria necesaria para todos sus componentes
personaje_t* crear_personaje(char nombre[MAX_NOMBRE]);


//Pre: El personaje y el pokemon son validos.
//Post: Carga un pokemon en la lista de batalla del personaje
int cargar_pokemon_de_batalla(personaje_t* personaje, pokemon_t* pokemon);


//Pre: El personaje y el pokemon son validos.
//Post: Carga un pokemon en la lista de pokemones capturados del personaje
int cargar_pokemon_capturado(personaje_t* personaje, pokemon_t* pokemon);


//Pre:
//Post:Carga desde un archivo al personaje, creandolo y reservando la memoria necesaria.
personaje_t* cargar_personaje_desde_archivo(char ruta_archivo[MAX_RUTA]);


//Pre: El personaje es valido.
//Post: Muestra por pantalla la informacion del personaje.
void mostrar_informacion_personaje(personaje_t* personaje);


//Pre: El personaje es valido.
//Post: Cambia de lugar a los pokemones en las posiciones pedidas.
int cambiar_pokemones_de_batalla(personaje_t* personaje, int posicion_1, int posicion_2);


//Pre: El personaje es valido.
//Post: La cantidad de pokemones de batalla del personaje.
int cantidad_pokemones_de_batalla(personaje_t* personaje);


//Pre: El personaje es valido.
//Post: Devuelve el pokemon que esta en la lista de batalla en la posicion pedida.
pokemon_t* pokemon_de_batalla_en_posicion(personaje_t* personaje, int posicion);


//Pre: El heap de gimnasios es valido.
//Post: Carga en el heap los gimnasios que habia en el archivo dado por la ruta, devuelve el heap.
heap_t* cargar_gimnasios_desde_archivos(char ruta_archivo[MAX_RUTA], heap_t* gimnasios);


//Pre: El juego es valido, con un heap valido.
//Post: Devuelve el proximo gimnasio a ser retado.
gimnasio_t* proximo_gimnasio(juego_t* juego);


//Pre: El juego y su heap son validos.
//Post: La cantidad de gimnasios.
int cantidad_gimnasios(juego_t* juego);


//Pre:
//Post: Elimina al personaje liberando la memoria reservada por el.
void eliminar_personaje(personaje_t* personaje);


//Pre:
//Post:Crea el juego, reservando la memoria necesaria
juego_t* crear_juego();


//Pre:Tanto los pokemones como la funcion batalla son validos.
//Post: Realiza la batalla entre los pokemones, devolviendo 1 si gano el primero y -1 si gano el segundo.
int batalla_entre_pokemones(pokemon_t* pokemon_1, pokemon_t* pokemon_2, funcion_batalla batalla);

//Pre:
//Post: Elimina al juego liberando la memoria reservada por el.
void eliminar_juego(juego_t* juego);

#endif /* __JUEGO_H__*/