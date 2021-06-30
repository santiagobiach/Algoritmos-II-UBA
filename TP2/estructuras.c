#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


pokemon_t* crear_pokemon(int velocidad, int defensa, int ataque,char especie[MAX_NOMBRE]){
	if(velocidad <= 0 || defensa <= 0 || ataque <= 0 || strlen(especie) == 0){
		return NULL;
	}
	pokemon_t* aux = malloc(sizeof(pokemon_t));
	if(!aux){
		return NULL;
	}
	strcpy(aux->especie, especie);
	aux->velocidad = velocidad;
	aux->defensa = defensa;
	aux->ataque = ataque;
	aux->contador = 0;
	return aux;
}

int mejorar_pokemon(pokemon_t* pokemon){
	if(pokemon->contador < 63){
		pokemon->velocidad +=1;
		pokemon->defensa +=1;
		pokemon->ataque +=1;
		pokemon->contador +=1;
		return 0;
	}
	return -1;
}

void eliminar_pokemon(void* pokemon){
	if(!pokemon){
		return;
	}
	free(pokemon);
}

entrenador_t* crear_entrenador(char nombre[MAX_NOMBRE], bool es_lider){
	if(strlen(nombre) == 0){
		return NULL;
	}
	entrenador_t* aux = malloc(sizeof(entrenador_t));
	if(!aux){
		return NULL;
	}
	strcpy(aux->nombre_entrenador, nombre);
	aux->es_lider = es_lider;
	aux->pokemones = lista_crear(eliminar_pokemon);

	return aux;
}

int cargar_pokemones_en_entrenador(entrenador_t* entrenador, pokemon_t* pokemon){
	if(!entrenador || !pokemon || cantidad_pokemones(entrenador) >=6){
		return -1;
	}
	return lista_insertar(entrenador->pokemones, pokemon);
}
size_t cantidad_pokemones(entrenador_t* entrenador){
	if(!entrenador){
		return 0;
	}
	return lista_elementos(entrenador->pokemones);
}
pokemon_t* pokemon_en_posicion(entrenador_t* entrenador, size_t posicion){
	if(!entrenador){
		return NULL;
	}
	return lista_elemento_en_posicion(entrenador->pokemones, posicion);
}

void eliminar_entrenador(void* entrenador){
	if(!entrenador){
		return;
	}
	entrenador_t* aux = entrenador;
	lista_destruir(aux->pokemones, true);
	free(entrenador);
}


gimnasio_t* crear_gimnasio(char nombre[MAX_NOMBRE], int dificultad, funcion_batalla batalla, char descripcion_batalla[MAX_DESCRIPCION]){
	if(strlen(nombre) == 0 || dificultad < 0 || !batalla || strlen(descripcion_batalla) == 0){
		return NULL;
	}
	gimnasio_t* aux = malloc(sizeof(gimnasio_t));
	if(!aux){
		return NULL;
	}
	strcpy(aux->nombre_gimnasio, nombre);
	aux->dificultad = dificultad;
	aux->batalla = batalla;
	aux->entrenadores = lista_crear(eliminar_entrenador);
	strcpy(aux->descripcion_batalla, descripcion_batalla);
	return aux;
}

int cargar_entrenadores_en_gimnasio(gimnasio_t* gimnasio, entrenador_t* entrenador){
	if(!gimnasio || !entrenador){
		return -1;
	}
	return lista_apilar(gimnasio->entrenadores, entrenador);
}
int desapilar_entrenadores_de_gimnasio(gimnasio_t* gimnasio, bool destruir_entrenador){
	if(!gimnasio){
		return -1;
	}
	return lista_desapilar(gimnasio->entrenadores, destruir_entrenador);
}

entrenador_t* entrenador_en_tope(gimnasio_t* gimnasio){
	if(!gimnasio){
		return NULL;
	}
	return lista_tope(gimnasio->entrenadores);
}
size_t cantidad_entrenadores(gimnasio_t* gimnasio){
	if(!gimnasio){
		return 0;
	}
	return lista_elementos(gimnasio->entrenadores);
}
bool mostrar_pokemon_entrenador(void* pokemon, void* contador){
    if(pokemon && contador){
    	pokemon_t* aux = pokemon;
    	(*(int*)contador)++;
        printf("%i: %s // Velocidad: %i Defensa: %i Ataque: %i", (*(int*)contador), aux->especie, aux->velocidad, aux->defensa, 
        	   aux->ataque);
        
        if(*(int*)contador <= 6){
    		
   		}
   		printf("\n");
    }
    return true;
}

void mostrar_informacion_entrenador(entrenador_t* entrenador){
	if(!entrenador){
		return;
	}
	printf("\nInformacion del entrenador: \n");
	printf("Nombre: %s\n", entrenador->nombre_entrenador);
	printf("Lista de pokemones:\n");
	int contador=0;
    size_t elementos_recorridos = 0;
    elementos_recorridos = lista_con_cada_elemento(entrenador->pokemones, mostrar_pokemon_entrenador, (void*)&contador);
    printf("Total pokemones : %i\n", elementos_recorridos);
}

void mostrar_informacion_gimnasio(gimnasio_t* gimnasio){
	if(!gimnasio || entrenador_en_tope(gimnasio) == NULL){
		return;
	}
	printf("\nInformacion del gimnasio: \n");
	printf("Nombre: %s\n", gimnasio->nombre_gimnasio);
	printf("Dificultad: %i\n", gimnasio->dificultad);
	printf("Descripcion de las batallas: %s", gimnasio->descripcion_batalla);
	lista_t* pila_auxiliar = lista_crear(NULL);
	entrenador_t* entrenador_aux;

	while(entrenador_en_tope(gimnasio)){
		
		entrenador_aux = entrenador_en_tope(gimnasio);
		mostrar_informacion_entrenador(entrenador_aux);
		lista_apilar(pila_auxiliar, entrenador_aux);
		desapilar_entrenadores_de_gimnasio(gimnasio, false);
	}
	
	while(lista_tope(pila_auxiliar)){
		
		entrenador_aux = lista_tope(pila_auxiliar);
		cargar_entrenadores_en_gimnasio(gimnasio,  entrenador_aux);
		lista_desapilar(pila_auxiliar, false);
	}
	

	lista_destruir(pila_auxiliar, false);

}
void eliminar_gimnasio(void* gimnasio){
	if(!gimnasio){
		return;
	}
	gimnasio_t* aux = gimnasio;
	lista_destruir(aux->entrenadores, true);
	free(gimnasio);
}