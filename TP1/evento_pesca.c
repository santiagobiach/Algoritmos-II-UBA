#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "evento_pesca.h"

#define FORMATO_ARRECIFE_LECTURA "%99[^;];%i;%i;%99[^\n]\n"
#define FORMATO_ACUARIO_ESCRITURA "%s;%i;%i;%s\n"

const int CANTIDAD_CARACTERISTICAS = 4;
const int ERROR = -1;
const int EXITO = 0;
const int MAX_RUTA_ARCHIVO = 100;


//Pre:
//Post: TRUE si el string es un txt, FALSE si no.
bool es_txt(char* string){
	char *token;
	char separador = '.';
	bool es_txt = true;
	token = strrchr(string, separador);
	if(token == NULL){
		es_txt = false;
	}else if(strcmp(token, ".txt") == 0){
		es_txt = true;
	}else{
		es_txt = false;
	}
	return es_txt;	
}


//Pre: La cantidad de pokemones debe ser positiva o 0, el pokemon debe estar inicializado.
//Post: TRUE si agrego con exito al pokemon, FALSE si hubo un error.
bool agregar_pokemon(pokemon_t pokemon, pokemon_t** habitat, int *cantidad_pokemones){

	pokemon_t* nuevo_puntero_pokemones = realloc(*habitat, sizeof(pokemon_t) * (unsigned)(*cantidad_pokemones + 1));
	if(nuevo_puntero_pokemones == NULL){
		//Si no hay espacio, el habitat queda como estaba antes.
		printf("\nNo hay espacio en el heap para agregar mas pokemones\n");
		return false;
	}
	
	*habitat = nuevo_puntero_pokemones;
	habitat[0][*cantidad_pokemones] = pokemon;
	
	*cantidad_pokemones = *cantidad_pokemones + 1;
	
	return true;
}

arrecife_t* crear_arrecife(const char* ruta_archivo){

	char ruta_archivo_aux[MAX_RUTA_ARCHIVO];
	strcpy(ruta_archivo_aux, ruta_archivo);
	if(!es_txt(ruta_archivo_aux)){
		printf("La ruta del archivo arrecife no es txt");
		return NULL;
	}
	FILE* archivo_arrecife = fopen(ruta_archivo, "r");
	if(!archivo_arrecife){
		printf("Error al abrir el archivo de arrecifes");
		return NULL;
	}


	
	pokemon_t pokemon_aux;
	int leidos = fscanf(archivo_arrecife, FORMATO_ARRECIFE_LECTURA, pokemon_aux.especie, &pokemon_aux.velocidad,
						&pokemon_aux.peso, pokemon_aux.color);
	if(leidos!=CANTIDAD_CARACTERISTICAS){
		fclose(archivo_arrecife);
		return NULL;
	}

	arrecife_t* arrecife = malloc(sizeof(arrecife_t));
	if(arrecife == NULL){
		printf("No hay espacio en la memoria");
		fclose(archivo_arrecife);
		return NULL;
	}
	arrecife->pokemon = NULL;
	arrecife->cantidad_pokemon = 0;

	while(leidos==CANTIDAD_CARACTERISTICAS){
		//Procesar

		/*Si devuelve false, es que nos quedamos sin espacio en el heap. Entonces, cierra el archivo y
		 *devuelve el arrecife hasta ahora.*/
		if(!agregar_pokemon(pokemon_aux, &(arrecife->pokemon) , &(arrecife->cantidad_pokemon))){
			fclose(archivo_arrecife);
			return arrecife;
		}
		//Leer
		leidos = fscanf(archivo_arrecife, FORMATO_ARRECIFE_LECTURA, pokemon_aux.especie, &pokemon_aux.velocidad,
						&pokemon_aux.peso, pokemon_aux.color);
	}
	
	fclose(archivo_arrecife);

	return arrecife;
}

acuario_t* crear_acuario(){

	acuario_t* acuario = malloc(sizeof(acuario_t));
	if(acuario == NULL){
		printf("No hay espacio en memoria dinamica para el acuario.");
		return NULL;
	}
	//De paso inicializamos sus variables
	acuario->pokemon = NULL;
	acuario->cantidad_pokemon = 0;

	return acuario;
}

//Pre: La cantidad de pokemones y la posicion del pokemon a sacar deben ser positivas o 0.
//Post: TRUE si saco con exito al pokemon, FALSE si hubo un error.
bool sacar_pokemon(int posicion_pokemon, pokemon_t** habitat, int *cantidad_pokemon){

	/* El pokemon que esta en la posicion del que queremos sacar sera el que esta al final del vector,
	 * ya que no nos importa que este ordenado.*/

	habitat[0][posicion_pokemon] = habitat[0][*cantidad_pokemon - 1];
	pokemon_t* nuevo_puntero_habitat = realloc(*habitat, sizeof(pokemon_t) * (unsigned)(*cantidad_pokemon - 1));

	*cantidad_pokemon = *cantidad_pokemon - 1;

	if(nuevo_puntero_habitat == NULL){
		//Si nuevo arrecife es NULL, puede ser porque no hay mas pokemones o porque hubo un error al achicar
		if(*cantidad_pokemon==0){
			*habitat = NULL;
			return true;
		}else{
			//Si el error fue por otra cosa, devolvemos false. y el habitat queda como estaba.
			return false;
		}
		
	}
	*habitat = nuevo_puntero_habitat;

	return true;
}


int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*),
 					  int cant_seleccion){

	int contador_auxiliar = 0;

	for(int i = 0; i < arrecife->cantidad_pokemon; i++){
		if((*seleccionar_pokemon)(&(arrecife->pokemon[i])) && (cant_seleccion > contador_auxiliar)){
			contador_auxiliar = contador_auxiliar + 1;
		}
	}
	if(contador_auxiliar >= cant_seleccion){
		contador_auxiliar = 0;
		for(int i = 0; i < arrecife->cantidad_pokemon; i++){

			if((*seleccionar_pokemon)(&(arrecife->pokemon[i])) && (cant_seleccion > contador_auxiliar)){
				//Intenta agregar un pokemon en el acuario. Si no lo logra, devuelve error.

				if(agregar_pokemon(arrecife->pokemon[i], &(acuario->pokemon), &(acuario->cantidad_pokemon))){
					if(sacar_pokemon(i, &(arrecife->pokemon), &(arrecife->cantidad_pokemon))){
						//Por como saco los pokemones, si no hago esto me salteo una comparacion.
						i = i - 1;
						contador_auxiliar = contador_auxiliar + 1;
					}else{
						return ERROR;
					}
					
				}else{
					return ERROR;
				}
				

			}
		}

	}else{
		printf("\nNo hay suficientes pokemones del tipo pedido\n");
		return ERROR;
	}
	return EXITO;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
	
	if(arrecife->cantidad_pokemon != 0){
		printf("\nEn el arrecife quedan\n");
		for(int i = 0; i < arrecife->cantidad_pokemon; i++){
			(*mostrar_pokemon)(&(arrecife->pokemon[i]));
		}
	}else{
		printf("Ya no quedan mas pokemones en el arrecife! Maldita sea Misty!\n");
	}
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){

	char nombre_archivo_aux[MAX_RUTA_ARCHIVO];
	strcpy(nombre_archivo_aux, nombre_archivo);
	if(!es_txt(nombre_archivo_aux)){
		printf("La ruta del archivo de acuario no es txt");
		return ERROR;
	}
	FILE* archivo_acuario = fopen(nombre_archivo, "w");
	if(!archivo_acuario){
		printf("Error al crear el archivo de texto con los pokemones del acuario");
		return ERROR;
	}

	for(int i = 0; i < acuario->cantidad_pokemon; i++){
		fprintf(archivo_acuario, FORMATO_ACUARIO_ESCRITURA, acuario->pokemon[i].especie, 
				acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
	}
	fclose(archivo_acuario);
	return EXITO;
}

void liberar_arrecife(arrecife_t* arrecife){
	if(arrecife == NULL){
		free(arrecife);
		return;
	}
	free(arrecife->pokemon);
	free(arrecife);
}

void liberar_acuario(acuario_t* acuario){
	
	if(acuario==NULL){
		free(acuario);
	}
	free(acuario->pokemon);
	
	free(acuario);
}