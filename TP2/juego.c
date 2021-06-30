#include "juego.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FORMATO_LECTURA "%c;%99[^\n]\n"
#define FORMATO_LECTURA_POKEMONES "%c;%50[^;];%i;%i;%i\n"
#define FORMATO_LECTURA_POKEMONES_AUX "%50[^;];%i;%i;%i\n"
#define FORMATO_GIMNASIO "%99[^;];%i;%i\n"


personaje_t* crear_personaje(char nombre[MAX_NOMBRE]){
	if(strlen(nombre) == 0){
		return NULL;
	}
	personaje_t* aux = malloc(sizeof(personaje_t));
	if(!aux){
		return NULL;
	}
	strcpy(aux->nombre, nombre);
	aux->pokemones_de_batalla = lista_crear(eliminar_pokemon);
	aux->pokemones_capturados = lista_crear(eliminar_pokemon);
	aux->medallas_obtenidas = 0;
	aux->entrenadores_derrotados = 0;

	return aux;
}

int cargar_pokemon_de_batalla(personaje_t* personaje, pokemon_t* pokemon){
	if(!personaje || !pokemon){
		return -1;
	}
	return lista_insertar(personaje->pokemones_de_batalla, pokemon);
}

int cargar_pokemon_capturado(personaje_t* personaje, pokemon_t* pokemon){
	if(!personaje || !pokemon){
		return -1;
	}
	return lista_insertar(personaje->pokemones_capturados, pokemon);
}




personaje_t* cargar_personaje_desde_archivo(char ruta_archivo[MAX_RUTA]){
	FILE* archivo_personaje = fopen(ruta_archivo, "r");
	if(!archivo_personaje){
		return NULL;
	}
	personaje_t* personaje_aux = NULL;

	char buffer[MAX_LECTURA];
	char* linea = leer_linea(buffer, MAX_LECTURA, archivo_personaje);
	if(!linea){
		fclose(archivo_personaje);
		return NULL;
	}
	char etiqueta;
	char string_aux[MAX_LECTURA];
	int leidos = sscanf(linea, FORMATO_LECTURA, &etiqueta, string_aux);
	if(leidos!=2 || etiqueta != 'E'){  //La primera linea debe decir el nombre del entrenador
		fclose(archivo_personaje);
		return NULL;
	}
	personaje_aux = crear_personaje(string_aux);
	if(!personaje_aux){
		fclose(archivo_personaje);
		return NULL;
	}
	pokemon_t* pokemon_aux;
	int velocidad_aux, defensa_aux, ataque_aux;
	int contador = 0;
	linea = leer_linea(buffer, MAX_LECTURA, archivo_personaje);
	if(!linea){
		fclose(archivo_personaje);
		return personaje_aux;
	}
	leidos = sscanf(linea, FORMATO_LECTURA_POKEMONES, &etiqueta, string_aux, &velocidad_aux, &defensa_aux, &ataque_aux);

	while(leidos==5 && etiqueta == 'P'){ //Luego de leer el nombre del entrenador, todas las lineas deberian empezar con P

		pokemon_aux = crear_pokemon(velocidad_aux, defensa_aux, ataque_aux, string_aux);
		if(contador < 6){
			cargar_pokemon_de_batalla(personaje_aux, pokemon_aux);
			contador++;
		}
		cargar_pokemon_capturado(personaje_aux, pokemon_aux);

		linea = leer_linea(buffer, MAX_LECTURA, archivo_personaje);
		if(!linea){
			fclose(archivo_personaje);
			return personaje_aux;
		}
		leidos = sscanf(linea, FORMATO_LECTURA_POKEMONES, &etiqueta, string_aux, &velocidad_aux, &defensa_aux, &ataque_aux);
	}
	fclose(archivo_personaje);
	return personaje_aux;
}

/*Muestra por pantalla al pokemon y sus caracteristicas*/
bool mostrar_pokemon(void* pokemon, void* contador){
    if(pokemon && contador){
    	pokemon_t* aux = pokemon;
    	(*(int*)contador)++;
        printf("%i: %s // Velocidad: %i Defensa: %i Ataque: %i", (*(int*)contador), aux->especie, aux->velocidad, aux->defensa, 
        	   aux->ataque);
        if(*(int*)contador <= 6){
    		printf("(De batalla)");
   		}
   		printf("\n");
    }
    return true;
}
/*Nos aprovechamos del iterador interno de la lista para mandarle la funcion mostrar pokemon*/
void mostrar_informacion_personaje(personaje_t* personaje){
	printf("\nInformacion del personaje: \n");
	printf("Nombre: %s\n", personaje->nombre);
	printf("Medallas obtenidas : %i - Entrenadores derrotados: %i\n", personaje->medallas_obtenidas,  personaje->entrenadores_derrotados);
	printf("Lista de pokemones:\n");
	int contador=0;
    size_t elementos_recorridos = 0;
    elementos_recorridos = lista_con_cada_elemento(personaje->pokemones_capturados, mostrar_pokemon, (void*)&contador);
    printf("Total pokemones : %i\n", elementos_recorridos);
}

void eliminar_personaje(personaje_t* personaje){
	if(!personaje){
		return;
	}
	lista_destruir(personaje->pokemones_de_batalla, false);
	lista_destruir(personaje->pokemones_capturados, true);
	free(personaje);
}
//Pre: El id es valido.
//Post:Devuelve la funcion batalla que corresponde segun el id recibido por parametro.
funcion_batalla batalla_segun_id(int id){
	if(id == 1){
		return funcion_batalla_1;
	}else if(id == 2){
		return funcion_batalla_2;
	}else if(id == 3){
		return funcion_batalla_3;
	}else if(id == 4){
		return funcion_batalla_4;
	}else if(id == 5){
		return funcion_batalla_5;
	}
	return NULL;	
}

char* descripcion_segun_id(int id){
	if(id == 1){
		return "Este gimnasio se rige segun la simetria. El pokemon que tenga el promedio de stats mas alto ganara!";
	}else if(id == 2){
		return "En este gimnasio estan muy interesados en el analisis de los nombres. Ganara el pokemon cuya especie tenga mas vocales.";
	}else if(id == 3){
		return "En este gimnasio les gustan mucho las esferas. Esta comprobado cientificamente que mientras mas cerca este la relacion entre la defensa y la velocidad de PI, mas redondeado sera el pokemon.";
	}else if(id == 4){
		return "En este gimnasio les gusta el caos y la asimetria. Ganara el pokemon que tenga la mayor diferencia entre su mejor stats y las demas";
	}else if(id == 5){
		return "Este gimnasio se rige segun la ley de Mewtwo, que Fuerza es igual a Ataque por Velocidad. Ganara el que golpee con mayor fuerza.";
	}
	return NULL;	
}

bool es_entrenador_valido(entrenador_t* entrenador){
	return (entrenador != NULL && cantidad_pokemones(entrenador) > 0);
}
bool es_gimnasio_valido(gimnasio_t* gimnasio){
	return (gimnasio != NULL && cantidad_entrenadores(gimnasio) > 0);
}
heap_t* cargar_gimnasios_desde_archivos(char ruta_archivo[MAX_RUTA], heap_t* gimnasios){
	FILE* archivo_gimnasio = fopen(ruta_archivo, "r");
	if(!archivo_gimnasio){
		return gimnasios;
	}
	char buffer[MAX_LECTURA];
	char* linea = leer_linea(buffer, MAX_LECTURA, archivo_gimnasio);
	if(!linea){
		fclose(archivo_gimnasio);
		return gimnasios;
	}

	char etiqueta;
	char string_aux[MAX_LECTURA];
	
	int leidos = sscanf(linea, FORMATO_LECTURA, &etiqueta, string_aux);
	if(leidos != 2 ||etiqueta != 'G'){
		fclose(archivo_gimnasio);
		return gimnasios;
	}
	gimnasio_t* gimnasio_aux = NULL;
	entrenador_t* entrenador_aux = NULL;
	pokemon_t* pokemon_aux = NULL;
	char nombre_aux[MAX_NOMBRE];
	int dificultad_aux, id_batalla_aux, velocidad_aux, defensa_aux, ataque_aux;
	bool hay_lider = false;
	bool hay_entrenador = false;

	leidos = sscanf(string_aux, FORMATO_GIMNASIO, nombre_aux, &dificultad_aux, &id_batalla_aux);
	gimnasio_aux = crear_gimnasio(nombre_aux, dificultad_aux, batalla_segun_id(id_batalla_aux), descripcion_segun_id(id_batalla_aux));


	if(!gimnasio_aux){
		fclose(archivo_gimnasio);
		return gimnasios;
	}

	linea = leer_linea(buffer, MAX_LECTURA, archivo_gimnasio);
	if(!linea){
		fclose(archivo_gimnasio);
		return gimnasios;
	}
	leidos = sscanf(linea, FORMATO_LECTURA, &etiqueta, string_aux);

	while(leidos == 2){
		if(etiqueta == 'G'){
			if(!gimnasio_aux){
				fclose(archivo_gimnasio);
				return gimnasios;
			}
			if(entrenador_aux && es_entrenador_valido(entrenador_aux)){
				cargar_entrenadores_en_gimnasio(gimnasio_aux, entrenador_aux);
			}
			if(!es_gimnasio_valido(gimnasio_aux)){
				eliminar_gimnasio(gimnasio_aux);
				fclose(archivo_gimnasio);
				return gimnasios;
			}else{
				heap_insertar(gimnasios, gimnasio_aux);
				leidos = sscanf(string_aux, FORMATO_GIMNASIO, nombre_aux, &dificultad_aux, &id_batalla_aux);
				gimnasio_aux = crear_gimnasio(nombre_aux, dificultad_aux, batalla_segun_id(id_batalla_aux), 
					                          descripcion_segun_id(id_batalla_aux));
				if(!gimnasio_aux){
					fclose(archivo_gimnasio);
					return gimnasios;
				}
				hay_lider = false,
				hay_entrenador = false;
			}
		}else if(etiqueta == 'L'){
			if(hay_lider || hay_entrenador){
				eliminar_gimnasio(gimnasio_aux);
				fclose(archivo_gimnasio);
				return gimnasios;
			}else{
				entrenador_aux = crear_entrenador(string_aux, true);
				if(!entrenador_aux){
					eliminar_gimnasio(gimnasio_aux);
					fclose(archivo_gimnasio);
					return gimnasios;
				}
				hay_lider = true;
			}
		}else if(etiqueta == 'E'){
			if(!hay_lider){
				eliminar_gimnasio(gimnasio_aux);
				fclose(archivo_gimnasio);
				return gimnasios;
			}else{
				if(hay_entrenador || hay_lider){
					if(es_entrenador_valido(entrenador_aux)){
						cargar_entrenadores_en_gimnasio(gimnasio_aux, entrenador_aux);
						entrenador_aux = crear_entrenador(string_aux, false);
						if(!entrenador_aux){
							eliminar_gimnasio(gimnasio_aux);
							fclose(archivo_gimnasio);
							return gimnasios;
						}						
					}else{
						eliminar_gimnasio(gimnasio_aux);
						eliminar_entrenador(entrenador_aux);
						fclose(archivo_gimnasio);
						return gimnasios;
					}
					
				}else{
					entrenador_aux = crear_entrenador(string_aux, false);
					if(!entrenador_aux){
						eliminar_gimnasio(gimnasio_aux);
						fclose(archivo_gimnasio);
						return gimnasios;
					}		
					hay_entrenador = true;
				}

			}
		}else if(etiqueta == 'P'){
			if(!hay_entrenador && !hay_lider){
				eliminar_gimnasio(gimnasio_aux);
				fclose(archivo_gimnasio);
				return gimnasios;
			}else{
				leidos = sscanf(string_aux, FORMATO_LECTURA_POKEMONES_AUX, nombre_aux,&velocidad_aux, &defensa_aux, &ataque_aux);
				pokemon_aux = crear_pokemon(velocidad_aux, defensa_aux, ataque_aux, nombre_aux);
				if(pokemon_aux == NULL || cargar_pokemones_en_entrenador(entrenador_aux, pokemon_aux) != 0){
					eliminar_entrenador(entrenador_aux);
					eliminar_gimnasio(gimnasio_aux);
					fclose(archivo_gimnasio);
					return gimnasios;
				}
			}
		}

		linea = leer_linea(buffer, MAX_LECTURA, archivo_gimnasio);
		if(!linea){
			if(es_entrenador_valido(entrenador_aux)){
				cargar_entrenadores_en_gimnasio(gimnasio_aux, entrenador_aux);											
			}else{
				eliminar_entrenador(entrenador_aux);					
			}
			if(es_gimnasio_valido(gimnasio_aux)){
				heap_insertar(gimnasios, gimnasio_aux);										
			}else{
				eliminar_gimnasio(gimnasio_aux);					
			}
			fclose(archivo_gimnasio);
			return gimnasios;
		}

		leidos = sscanf(linea, FORMATO_LECTURA, &etiqueta, string_aux);
	}
	if(es_entrenador_valido(entrenador_aux)){
		cargar_entrenadores_en_gimnasio(gimnasio_aux, entrenador_aux);											
	}else{
		eliminar_entrenador(entrenador_aux);					
	}
	if(es_gimnasio_valido(gimnasio_aux)){
		heap_insertar(gimnasios, gimnasio_aux);										
	}else{
		eliminar_gimnasio(gimnasio_aux);					
	}

	fclose(archivo_gimnasio);
	return gimnasios;
}

//Pre: Los gimnasios son validos.
//Post: Compara los gimnasios segun la dificultad, y devuelve 1 si el primero es mas dificil y -1 si es al reves.
int comparador_gimnasios(void* gimnasio_1, void* gimnasio_2){
	if(!gimnasio_1 || !gimnasio_2)
		return 0;
	gimnasio_t* aux_1 = gimnasio_1;
	gimnasio_t* aux_2 = gimnasio_2;
	if(aux_1->dificultad > aux_2->dificultad)
		return 1;
	return -1;
}

juego_t* crear_juego(){
	
	juego_t* aux = malloc(sizeof(juego_t));
	if(!aux)
		return NULL;
	aux->protagonista = NULL;
	aux->gimnasio_actual = NULL;
	aux->oponente_actual = NULL;
	aux->gimnasios = heap_crear(comparador_gimnasios, eliminar_gimnasio);
	return aux;
}

void eliminar_juego(juego_t* juego){
	if(!juego)
		return;

	eliminar_personaje(juego->protagonista);
	eliminar_gimnasio(juego->gimnasio_actual);
	//eliminar_entrenador(juego->oponente_actual);
	heap_destruir(juego->gimnasios);
	free(juego);
}

pokemon_t* pokemon_de_batalla_en_posicion(personaje_t* personaje, int posicion){
	if(!personaje){
		return NULL;
	}
	return lista_elemento_en_posicion(personaje->pokemones_de_batalla, (unsigned int) posicion);
}


//Pre: El personaje es valido.
//Post:El pokemon capturado en la posicion requerida.
pokemon_t* pokemon_capturado_en_posicion(personaje_t* personaje, int posicion){
	if(!personaje){
		return NULL;
	}
	return lista_elemento_en_posicion(personaje->pokemones_capturados, (unsigned int) posicion);
}

int cantidad_pokemones_de_batalla(personaje_t* personaje){
	if(!personaje){
		return 0;
	}
	return (int) lista_elementos(personaje->pokemones_de_batalla);
}

int cambiar_pokemones_de_batalla(personaje_t* personaje, int posicion_1, int posicion_2){
	if(!personaje){
		return -1;
	}
	pokemon_t aux;
	pokemon_t* pokemon_1 = pokemon_de_batalla_en_posicion(personaje, posicion_1);
	pokemon_t* pokemon_2 = pokemon_capturado_en_posicion(personaje, posicion_2);
	if(!pokemon_1 || !pokemon_2){
		return -1;
	}

	aux = *pokemon_1;
	
	*pokemon_1 = *pokemon_2;
	*pokemon_2 = aux;

	return 0;
}

int cantidad_gimnasios(juego_t* juego){
	if(!juego){
		return 0;
	}
	return heap_elementos(juego->gimnasios);
}

gimnasio_t* proximo_gimnasio(juego_t* juego){
	if(!juego){
		return NULL;
	}
	return heap_extraer_raiz(juego->gimnasios);
}

int batalla_entre_pokemones(pokemon_t* pokemon_1, pokemon_t* pokemon_2, funcion_batalla batalla){
	return batalla(pokemon_1, pokemon_2);
}