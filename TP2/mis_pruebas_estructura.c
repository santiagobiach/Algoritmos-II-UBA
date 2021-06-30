#include "estructuras.h"
#include <stdio.h>
#include <string.h>
#include "pa2mm.h"


void probar_creacion_y_mejora_pokemon(){
	pokemon_t* pokemon = NULL;

	pa2m_afirmar((pokemon=crear_pokemon(-1, 0,2, "Paco")) == NULL, "Si alguna de sus caracteristicas es negativa, devuelve NULL");
	pa2m_afirmar((pokemon=crear_pokemon(4, 10,2,"Pikachu")) != NULL, "Pudo crear un pokemon");
	pa2m_afirmar(strcmp(pokemon->especie, "Pikachu") == 0, "El nombre es el correcto");
	pa2m_afirmar(pokemon->velocidad == 4, "La velocidad es la correcta");
	pa2m_afirmar(pokemon->defensa == 10, "La defensa es la correcta");
	pa2m_afirmar(pokemon->ataque == 2, "El ataque es la correcta");
	pa2m_afirmar(mejorar_pokemon(pokemon) == 0, "Se pudo mejorar al pokemon");
	pa2m_afirmar(pokemon->velocidad == 5, "La velocidad es la correcta");
	pa2m_afirmar(pokemon->defensa == 11, "La defensa es la correcta");
	pa2m_afirmar(pokemon->ataque == 3, "El ataque es la correcta");
	pa2m_afirmar(pokemon->contador == 1, "El contador es 1");
	pokemon->contador = 63; 
	pa2m_afirmar(mejorar_pokemon(pokemon) == -1, "No se puede mejorar al pokemon si este fue mejorado al maximo");
	pa2m_afirmar(pokemon->velocidad == 5, "La velocidad es la correcta");
	pa2m_afirmar(pokemon->defensa == 11, "La defensa es la correcta");
	pa2m_afirmar(pokemon->ataque == 3, "El ataque es la correcta");

	eliminar_pokemon(pokemon);
}

void probar_creacion_entrenador(){
	entrenador_t* entrenador = NULL;
	
	pa2m_afirmar((entrenador=crear_entrenador("", false)) == NULL, "Si el entrenador no tiene nombre, no se crea");
	pa2m_afirmar((entrenador=crear_entrenador("Jose", false)) != NULL, "Pudo crear al entrenador");
	pa2m_afirmar(strcmp(entrenador->nombre_entrenador, "Jose") == 0, "Su nombre es el correcto");
	pa2m_afirmar((entrenador->es_lider == false), "El entrenador creado no es lider");

	eliminar_entrenador(entrenador);
}

void probar_cargar_pokemones_en_lista(){
	entrenador_t* entrenador = crear_entrenador("Jose", false);
	pokemon_t* pokemon_1 = crear_pokemon(4, 10,2,"Pikachu");
	pokemon_t* pokemon_2 = crear_pokemon(4, 10,2,"Squirtle");
	pokemon_t* pokemon_3 = crear_pokemon(4, 10,2,"Eevee");
	if(!entrenador || !pokemon_1 || !pokemon_2 || !pokemon_3){
		return;
	}
	pa2m_afirmar(cargar_pokemones_en_entrenador(entrenador, pokemon_1) == 0, "Pude cargar un pokemon en la lista del entrenador");
	pa2m_afirmar(cantidad_pokemones(entrenador) == 1, "El entrenador tiene 1 pokemon");
	pa2m_afirmar(cargar_pokemones_en_entrenador(entrenador, pokemon_2) == 0, "Pude cargar un pokemon en la lista del entrenador");
	pa2m_afirmar(cantidad_pokemones(entrenador) == 2, "El entrenador tiene 2 pokemon");
	pa2m_afirmar(cargar_pokemones_en_entrenador(entrenador, pokemon_3) == 0, "Pude cargar un pokemon en la lista del entrenador");
	pa2m_afirmar(cantidad_pokemones(entrenador) == 3, "El entrenador tiene 3 pokemon");
	pa2m_afirmar(pokemon_en_posicion(entrenador, 0) == pokemon_1, "El primer pokemon es el correcto");
	pa2m_afirmar(pokemon_en_posicion(entrenador, 1) == pokemon_2, "El segundo pokemon es el correcto");
	pa2m_afirmar(pokemon_en_posicion(entrenador, 2) == pokemon_3, "El tercer pokemon es el correcto");

	eliminar_entrenador(entrenador);
}
int funcion_batalla_prueba(void* pokemon_1, void* pokemon_2){
	return 1;
}
void probar_creacion_gimnasio(){
	gimnasio_t* gimnasio = NULL;

	pa2m_afirmar((gimnasio=crear_gimnasio("", 5, NULL,"A")) == NULL, "Si el gimnasio no tiene nombre, no se crea");
	pa2m_afirmar((gimnasio=crear_gimnasio("Tierra", 5, NULL,"A")) == NULL, "Si el gimnasio no funcion de batalla, no se crea");
	pa2m_afirmar((gimnasio=crear_gimnasio("Tierra", -5, funcion_batalla_prueba,"A")) == NULL, "Si la dificultad es negativa, no se crea");
	pa2m_afirmar((gimnasio=crear_gimnasio("Tierra", 5, funcion_batalla_prueba,"")) == NULL, "Si no tiene descripcion de batalla, no se crea");
	pa2m_afirmar((gimnasio=crear_gimnasio("Tierra", 5, funcion_batalla_prueba, "Hola")) != NULL, "Pude crear un gimnasio");
	pa2m_afirmar(strcmp(gimnasio->nombre_gimnasio, "Tierra") == 0, "El nombre es el correcto");
	pa2m_afirmar(strcmp(gimnasio->descripcion_batalla, "Hola") == 0, "La descripcion es la correcta");
	pa2m_afirmar(gimnasio->dificultad == 5, "La dificultad es la correcta");
	pa2m_afirmar(gimnasio->batalla == funcion_batalla_prueba, "La funcion de batallas es la correcta");

	eliminar_gimnasio(gimnasio);
}

void probar_apilado_y_desapilado_entrenadores(){
	int resultado = 0;
	gimnasio_t* gimnasio = crear_gimnasio("Tierra", 5, funcion_batalla_prueba, "Hola");
	entrenador_t* entrenador_1 = crear_entrenador("Lider Jose", true);
	pokemon_t* pokemon_1 = crear_pokemon(4, 10,2,"Pikachu");
	resultado = cargar_pokemones_en_entrenador(entrenador_1, pokemon_1);
	entrenador_t* entrenador_2 = crear_entrenador("Manuel", false);
	pokemon_t* pokemon_2 = crear_pokemon(4, 10,2,"Ratatta");
	resultado = cargar_pokemones_en_entrenador(entrenador_2, pokemon_2);
	entrenador_t* entrenador_3 = crear_entrenador("Juan", false);
	pokemon_t* pokemon_3 = crear_pokemon(4, 10,2,"Pidgey");
	resultado = cargar_pokemones_en_entrenador(entrenador_3, pokemon_3);
	if(resultado != 0){
		return;
	}
	pa2m_afirmar(cargar_entrenadores_en_gimnasio(gimnasio, entrenador_1) == 0, "Pude cargar al entrenador en la pila del gimnasio");
	pa2m_afirmar(entrenador_en_tope(gimnasio) == entrenador_1, "El entrenador en el tope es el correcto");
	pa2m_afirmar(cantidad_entrenadores(gimnasio) == 1, "La cantidad de entrenadores es la correcta");
	pa2m_afirmar(cargar_entrenadores_en_gimnasio(gimnasio, entrenador_2) == 0, "Pude cargar al entrenador en la pila del gimnasio");
	pa2m_afirmar(entrenador_en_tope(gimnasio) == entrenador_2, "El entrenador en el tope es el correcto");
	pa2m_afirmar(cantidad_entrenadores(gimnasio) == 2, "La cantidad de entrenadores es la correcta");
	pa2m_afirmar(cargar_entrenadores_en_gimnasio(gimnasio, entrenador_3) == 0, "Pude cargar al entrenador en la pila del gimnasio");
	pa2m_afirmar(entrenador_en_tope(gimnasio) == entrenador_3, "El entrenador en el tope es el correcto");
	pa2m_afirmar(cantidad_entrenadores(gimnasio) == 3, "La cantidad de entrenadores es la correcta");
	pa2m_afirmar(desapilar_entrenadores_de_gimnasio(gimnasio, true) == 0, "Pude desapilar al entrenador en la pila del gimnasio");
	pa2m_afirmar(entrenador_en_tope(gimnasio) == entrenador_2, "El entrenador en el tope es el correcto");
	pa2m_afirmar(cantidad_entrenadores(gimnasio) == 2, "La cantidad de entrenadores es la correcta");
	pa2m_afirmar(desapilar_entrenadores_de_gimnasio(gimnasio, true) == 0, "Pude desapilar al entrenador en la pila del gimnasio");
	pa2m_afirmar(entrenador_en_tope(gimnasio) == entrenador_1, "El entrenador en el tope es el correcto");
	pa2m_afirmar(cantidad_entrenadores(gimnasio) == 1, "La cantidad de entrenadores es la correcta");
	pa2m_afirmar(desapilar_entrenadores_de_gimnasio(gimnasio, true) == 0, "Pude desapilar al entrenador en la pila del gimnasio");
	pa2m_afirmar(entrenador_en_tope(gimnasio) == NULL, "Como no hay entrenadores, el entrenador en tope es NULL");
	pa2m_afirmar(cantidad_entrenadores(gimnasio) == 0, "La cantidad de entrenadores es la correcta");
	pa2m_afirmar(desapilar_entrenadores_de_gimnasio(gimnasio, true) == -1, "Intentar desapilar sin entrenadores devuelve NULL");
	eliminar_gimnasio(gimnasio);
}

int main(){
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y MEJORA DE POKEMON");
	probar_creacion_y_mejora_pokemon();

	pa2m_nuevo_grupo("PRUEBAS DE CREACION DE ENTRENADOR");
	probar_creacion_entrenador();

	pa2m_nuevo_grupo("PRUEBAS DE CARGAR POKEMONS EN LISTA");
	probar_cargar_pokemones_en_lista();

	pa2m_nuevo_grupo("PRUEBAS DE CREACION DE GIMNASIO");
	probar_creacion_gimnasio();

	pa2m_nuevo_grupo("PRUEBAS DE APILADO Y DESAPILADO DE ENTRENADORES");
	probar_apilado_y_desapilado_entrenadores();

	pa2m_mostrar_reporte();
	return 0;
}