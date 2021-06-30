#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

const char ENTRENADOR = 'E';
const char ARBOL_GIMNASIO = 'A';
const char INICIAR_PARTIDA = 'I';
const char SIMULAR_PARTIDA = 'S';
const char LARGO_ERRONEO = 'L';
const char FINALIZAR = 'F';
const char GIMNASIO = 'G';
const char BATALLA = 'B';
const char CAMBIAR_POKEMONES = 'C';
const char SIGUIENTE = 'N';
const char TOMAR_POKEMON = 'T';
const char REINTENTAR = 'R';


//Pre: El juego es valido.
//Post: Simula la partida.
void simular_partida(juego_t* juego);

//Pre:-
//Post: Devuelve un caracter. Si el largo de la linea es mayor que el requerido, devuelve error.
char respuesta_usuario(){
	char buffer[MAX_LECTURA];
	char* linea = leer_linea(buffer, MAX_LECTURA, stdin);
	if(!linea){
		printf("Error al leer la linea");
		return 'V'; //Letra al azar que es invalida, para que tenga que ingresar una linea de nuevo.
	}
	if(strlen(linea) > 1){
		return LARGO_ERRONEO;
	}
	return linea[0];
}
//Pre:
//Post: PIde al usuario que ingrese un caracter y lo devuelve.
char pedir_ingreso_caracter(){
	char respuesta;
	printf("\nIngrese un caracter: ");
	respuesta = respuesta_usuario();
	system("clear");
	return respuesta;
}

//PRe:
//POst: Devuelve true si el caracter es un caracter valido para el menu inicio
bool es_caracter_valido_menu_inicio(char caracter){
	return (caracter == ENTRENADOR || caracter == ARBOL_GIMNASIO || caracter == INICIAR_PARTIDA || caracter == SIMULAR_PARTIDA ||
	 		caracter == FINALIZAR);
}

//Pre:
//Post: Imprime por pantalla las opciones validas que puede elegir el usuario para el menu de inicio.
void imprimir_opciones_menu_de_inicio(){
	printf("\nE:Ingresar el archivo del entrenador principal.\n");
	printf("A:Agrega un gimnasio al arbol de gimnasios.\n");
	printf("I:Comenzar la partida.\n");
	printf("S:Simular la partida.\n");
	printf("F:Finalizar.\n");

}

//Pre:
//Post:Lee la ruta de un archivo ingresada por el usuario y la devuelve.
char* leer_ruta_archivo(){
	char buffer[MAX_RUTA];
	char* linea = leer_linea(buffer, MAX_RUTA, stdin);
	if(!linea){
		printf("Error al leer la linea");
		return NULL;
	}
	return linea;

}

//Pre: El juego es valido.
//Post: Pide al usuario la ruta del archivo de personaje y luego lo procesa.
void pedir_ruta_archivo_personaje(juego_t* juego){
	char* ruta_archivo;
	printf("\nIngrese la ruta del archivo del entrenador principal: ");
	ruta_archivo = leer_ruta_archivo();
	if(!ruta_archivo){
		printf("\nError al leer la ruta del archivo\n");
	}else{
		juego->protagonista = cargar_personaje_desde_archivo(ruta_archivo);
		if(!juego->protagonista){
			printf("\nError al leer el archivo del entrenador principal\n");
		}
	}
}


//Pre: El juego es valido.
//Post: Pide al usuario la ruta del archivo de gimnasios y luego lo procesa.
void pedir_ruta_archivo_gimnasios(juego_t* juego){
	char* ruta_archivo;
	printf("\nIngrese la ruta del archivo del gimnasio: ");
	ruta_archivo = leer_ruta_archivo();
	if(!ruta_archivo){
		printf("\nError al leer la ruta del archivo\n");
	}else{
		int aux = cantidad_gimnasios(juego);
		juego->gimnasios = cargar_gimnasios_desde_archivos(ruta_archivo, juego->gimnasios);
		if(cantidad_gimnasios(juego) == aux){
			printf("\nError al leer el archivo de gimnasios principal\n");
		}
	}
}

void menu_de_inicio(juego_t* juego){

	char respuesta;
	

	printf("-------------Bienvenido a tu propia aventura pokemon!-------------\n");
	imprimir_opciones_menu_de_inicio();
	
	respuesta = pedir_ingreso_caracter();
	while(respuesta == ENTRENADOR || respuesta == ARBOL_GIMNASIO || !es_caracter_valido_menu_inicio(respuesta)){

		if(respuesta == ENTRENADOR){
			pedir_ruta_archivo_personaje(juego);
		}
		if(respuesta == ARBOL_GIMNASIO){
			pedir_ruta_archivo_gimnasios(juego);
		}
	
		if(!es_caracter_valido_menu_inicio(respuesta)){
			printf("\nEl caracter ingresado es invalido.\n");
		}

		imprimir_opciones_menu_de_inicio();

		respuesta = pedir_ingreso_caracter();
	}

	if(respuesta == INICIAR_PARTIDA){

		if(!juego->protagonista || cantidad_gimnasios(juego) == 0){
			printf("\nNo se puede empezar a jugar sin un personaje principal o sin gimnasios!!\n");
			return;
		}
		juego->gimnasio_actual = proximo_gimnasio(juego);
		menu_de_gimnasio(juego);
	}else if(respuesta == SIMULAR_PARTIDA){
		if(!juego->protagonista || cantidad_gimnasios(juego) == 0){
			printf("\nNo se puede empezar a jugar sin un personaje principal o sin gimnasios!!\n");
			return;
		}
		simular_partida(juego);
	}else if(respuesta == FINALIZAR){
		printf("\nGracias por haber jugado nuestro juego!\n");
	}
}
//Pre: 
//Post: Imprime por pantalla las opciones que puede elegir el usuario para el menu de gimnasio.
void imprimir_opciones_menu_de_gimnasio(){
	
	printf("\nE:Informacion del entrenador principal.\n");
	printf("G:Informacion del gimnasio actual.\n");
	printf("C:Cambiar pokemones de batalla.\n");
	printf("B:Proxima batalla.\n");
	printf("F:Finalizar.\n");
	
}
//Pre:
//Post: Devuelve true si el caracter es valido, false si no.
bool es_caracter_valido_menu_gimnasio(char caracter){
	return (caracter == ENTRENADOR || caracter == GIMNASIO || caracter == CAMBIAR_POKEMONES || caracter == BATALLA || 
			caracter == FINALIZAR);
}

//Pre:
//Post: Lee lo que ingreso el usuario. Si es un numero, lo devuelve. Si no, devuelve error.
int respuesta_usuario_numerica(){
	char buffer[MAX_LECTURA];
	char* linea = leer_linea(buffer, MAX_LECTURA, stdin);
	if(!linea){
		printf("\nError al leer la linea\n");
		return -1;
	}
	for(int i = 0; i < (strlen(linea) - 1);i++){
		if(!isdigit(linea[i])){
			printf("\nNo ingresaste un numero\n");
			return -1;
		}
	}
	return atoi(linea);
}

//Pre: EL personaje es valido.
//Post: Cambia la posicion de dos pokemones en las listas correspondientes.
int cambiar_pokemones(personaje_t* personaje){
	int respuesta;
	int posicion_1, posicion_2;
	printf("\nIngrese la posicion del pokemon del equipo batalla a cambiar: \n");
	respuesta = respuesta_usuario_numerica();
	if(respuesta <= 0){
		printf("\nLa posicion ingresada es invalida\n");
		return -1;
	}
	posicion_1 = respuesta - 1;
	printf("\nIngrese la posicion del pokemon que quiere ingresar al equipo: \n");
	respuesta = respuesta_usuario_numerica();
	if(respuesta <= 0){
		printf("\nLa posicion ingresada es invalida\n");
		return -1;
	}
	posicion_2 = respuesta - 1;

	
	if(cambiar_pokemones_de_batalla(personaje, posicion_1, posicion_2) == -1){
		printf("Error al cambiar los pokemones");
		return -1;
	}
	return 0;
}

//Pre: Tanto los pokemones como la funcion batallas son validas.
//Post: Realiza la batalla y muestra el resultado por pantalla.
int realizar_batalla_pokemon(pokemon_t* pokemon_1, pokemon_t* pokemon_2, funcion_batalla batalla){
	printf("\n%s               vs.                    %s\n", pokemon_1->especie, pokemon_2->especie);
	int resultado = batalla_entre_pokemones(pokemon_1, pokemon_2, batalla);
	if(resultado == GANO_PRIMERO){
		mejorar_pokemon(pokemon_1);
		printf("Gano %s\n", pokemon_1->especie);
	}else{
		printf("Gano %s", pokemon_2->especie);
	}
	return resultado;
}

//Pre: Tanto los entrenadores(personaje y oponente) como la funcion batallas son validas.
//Post: Realiza la batalla y muestra el resultado por pantalla.
int batalla_entre_entrenadores(personaje_t* personaje, entrenador_t* oponente, funcion_batalla batalla, char modo){
	int pokemones_restantes_protagonista = (int)cantidad_pokemones_de_batalla(personaje);
	int pokemones_restantes_oponente = (int)cantidad_pokemones(oponente);
	int i = 0, j = 0;
	int resultado_batalla;
	char respuesta;
	pokemon_t* pokemon_protagonista;
	pokemon_t* pokemon_oponente;

	while(pokemones_restantes_protagonista > 0 && pokemones_restantes_oponente > 0){
		system("clear");
		printf("\n%s               vs.                  %s\n", personaje->nombre,oponente->nombre_entrenador);
		
		printf("Pokemones restantes : %i                  Pokemones restantes: %i", pokemones_restantes_protagonista, 
			   pokemones_restantes_oponente);

		pokemon_protagonista = pokemon_de_batalla_en_posicion(personaje, i);
		pokemon_oponente = pokemon_en_posicion(oponente, (unsigned int)j);
		resultado_batalla = realizar_batalla_pokemon(pokemon_protagonista, pokemon_oponente, batalla);
		if(resultado_batalla == 1){
			j++;
			pokemones_restantes_oponente--;
		}else{
			i++;
			pokemones_restantes_protagonista--;
		}
		if(modo == BATALLA){
			printf("\nPresione N para continuar: ");
			respuesta = respuesta_usuario();
			while(respuesta != SIGUIENTE){
				printf("\nPresione N para continuar: ");
				respuesta = respuesta_usuario();
			}
		}
		
	}
	if(pokemones_restantes_oponente <= 0 ){
		return 0;
	}
	return -1;
}
//Pre: El juego y el modo son validos.
//Post: Realiza la batalla, muestra quien gano y devuelve los valores correspondientes.
int realizar_batalla_entrenadores(juego_t* juego, char modo){
	
	int resultado_batalla = batalla_entre_entrenadores(juego->protagonista,juego->oponente_actual,juego->gimnasio_actual->batalla,
	 												   modo);

	if(resultado_batalla == -1){
		return resultado_batalla;
	}
	printf("\nDerrotaste a %s\n", juego->oponente_actual->nombre_entrenador);
	juego->protagonista->entrenadores_derrotados =  juego->protagonista->entrenadores_derrotados + 1;
	if(juego->oponente_actual->es_lider){
		juego->protagonista->medallas_obtenidas =  juego->protagonista->medallas_obtenidas + 1;
		return 1;
	}
	return 0;
}

int menu_de_batalla(juego_t* juego){
	return realizar_batalla_entrenadores(juego, BATALLA);
}

void menu_de_gimnasio(juego_t* juego){
	char respuesta;
	printf("\n-------------- Gimnasio---------------\n");
	imprimir_opciones_menu_de_gimnasio();
	respuesta = pedir_ingreso_caracter();
	while(respuesta == ENTRENADOR || respuesta == GIMNASIO || respuesta == CAMBIAR_POKEMONES || 
		  !es_caracter_valido_menu_gimnasio(respuesta)){
		if(respuesta == ENTRENADOR){
			mostrar_informacion_personaje(juego->protagonista);
		}
	
		if(respuesta == GIMNASIO){
			mostrar_informacion_gimnasio(juego->gimnasio_actual);
		}
		if(respuesta == CAMBIAR_POKEMONES){
			cambiar_pokemones(juego->protagonista);
		}

		if(!es_caracter_valido_menu_gimnasio(respuesta)){
			printf("\nEl caracter ingresado es invalido.\n");
		}

		imprimir_opciones_menu_de_gimnasio();

		respuesta = pedir_ingreso_caracter();
	}
	if(respuesta == BATALLA){
		if(!juego->oponente_actual){
			juego->oponente_actual = entrenador_en_tope(juego->gimnasio_actual);
		}
		int resultado_batalla = menu_de_batalla(juego);
		if(resultado_batalla == 0){
			desapilar_entrenadores_de_gimnasio(juego->gimnasio_actual, true);
			juego->oponente_actual = entrenador_en_tope(juego->gimnasio_actual);
			menu_de_gimnasio(juego);
		}else if(resultado_batalla == 1){
			menu_de_victoria(juego);
		}else{
			menu_de_derrota(juego);
		}
	}
	if(respuesta == FINALIZAR){
		printf("\nGracias por haber jugado nuestro juego!\n");
	}
}

//Pre: El juego es valido.
//Post: Imprime el mensaje de victoria.
void imprimir_mensaje_victoria(juego_t* juego){
	printf("\nFelicidades, has demostrado ser un maestro pokemon!!\n");
	printf("\nEstos son tus datos:\n");
	mostrar_informacion_personaje(juego->protagonista);
}
//Pre:
//Post: Imprime las opciones que el usuario tiene al vencer a un lider.
void imprimir_opciones_menu_de_victoria(bool tomo_pokemon){
	if(!tomo_pokemon){
		printf("\nT:Tomar prestado un pokemon del lider.\n");
	}
	printf("C:Cambiar pokemones de batalla.\n");
	printf("N:Proximo gimnasio.\n");
	printf("F:Finalizar.\n");
}

//Pre:
//Post:Devuelve true si el caracter es valido y false si no.
bool es_caracter_valido_menu_victoria(char caracter){
	return (caracter == CAMBIAR_POKEMONES || caracter == TOMAR_POKEMON|| caracter == SIGUIENTE || 
			caracter == FINALIZAR);
}

//Pre: EL personaje y el entrenador son validos.
//Post:Agrega un pokemon del entrenador a los pokemones capturados del personaje.
int tomar_pokemon_de_lider(personaje_t* personaje, entrenador_t* entrenador){
	int respuesta;
	int posicion_1;
	pokemon_t* aux = malloc(sizeof(pokemon_t));
	system("clear");

	mostrar_informacion_entrenador(entrenador);
	printf("\nIngrese la posicion del pokemon del lider que quiere tomar prestado: ");
	respuesta = respuesta_usuario_numerica();
	if(respuesta <= 0){
		printf("\nLa posicion ingresada es invalida\n");
		return -1;
	}
	posicion_1 = respuesta - 1;
	*aux = *(pokemon_en_posicion(entrenador, (unsigned int)posicion_1));
	if(!aux){
		return -1;
	}
	cargar_pokemon_capturado(personaje, aux);
	return 0;
}

void menu_de_victoria(juego_t* juego){

	char respuesta;
	bool tomo_pokemon = false;
	system("clear");
	printf("\n-------------- Victoria!---------------\n");
	printf("\n-------------- Derrotaste el %s---------------\n", juego->gimnasio_actual->nombre_gimnasio);
	imprimir_opciones_menu_de_victoria(tomo_pokemon);
	respuesta = pedir_ingreso_caracter();
	while(respuesta == CAMBIAR_POKEMONES || respuesta == TOMAR_POKEMON || !es_caracter_valido_menu_victoria(respuesta)){
		if(!tomo_pokemon && respuesta == TOMAR_POKEMON){
			int resultado = tomar_pokemon_de_lider(juego->protagonista, juego->oponente_actual);	
			if(resultado == 0){
				tomo_pokemon = true;
			}
		}
		if(respuesta == CAMBIAR_POKEMONES){
			cambiar_pokemones(juego->protagonista);
		}
		imprimir_opciones_menu_de_victoria(tomo_pokemon);
		respuesta = pedir_ingreso_caracter();
	}

	desapilar_entrenadores_de_gimnasio(juego->gimnasio_actual, true);
	juego->oponente_actual = NULL;
	if(respuesta == SIGUIENTE){

		if(cantidad_gimnasios(juego) > 0){
			eliminar_gimnasio(juego->gimnasio_actual);
			juego->gimnasio_actual = proximo_gimnasio(juego);
			menu_de_gimnasio(juego);
		}else{
			imprimir_mensaje_victoria(juego);
		}
	}
	if(respuesta == FINALIZAR){
		printf("\nGracias por haber jugado nuestro juego!\n");
	}
}
//Pre: El juego es valido.
//Post:Imprime quien vencio al personaje y sus estadisticas
void imprimir_mensaje_derrota(juego_t* juego){
	printf("\n------------Perdiste!--------------\n");
	printf("Te vencio %s en  el %s\n", juego->oponente_actual->nombre_entrenador, juego->gimnasio_actual->nombre_gimnasio);
	printf("Tus estadisticas son: \n");
	mostrar_informacion_personaje(juego->protagonista);
}

//Pre:
//Post: Imprime por pantalla las opciones que tiene el usuario al ser derrotado
void imprimir_opciones_menu_de_derrota(){
	printf("C:Cambiar pokemones de batalla.\n");
	printf("R:Reintentar el gimnasio.\n");
	printf("F:Finalizar.\n");
}

//Pre:
//Post:TRue si el caracter es valido, false si no.
bool es_caracter_valido_menu_derrota(char caracter){
	return (caracter == REINTENTAR || caracter == CAMBIAR_POKEMONES|| caracter == FINALIZAR);
}
void menu_de_derrota(juego_t* juego){
	imprimir_mensaje_derrota(juego);
	imprimir_opciones_menu_de_derrota();
	char respuesta = pedir_ingreso_caracter();
	while(respuesta == CAMBIAR_POKEMONES || !es_caracter_valido_menu_derrota(respuesta)){
		if(respuesta == CAMBIAR_POKEMONES){
			cambiar_pokemones(juego->protagonista);
		}
		imprimir_opciones_menu_de_derrota();
		respuesta = pedir_ingreso_caracter();
	}
	if(respuesta == REINTENTAR){
		menu_de_gimnasio(juego);
	}
	if(respuesta == FINALIZAR){
		desapilar_entrenadores_de_gimnasio(juego->gimnasio_actual, true);
		juego->oponente_actual = NULL;
		printf("\nGracias por haber jugado nuestro juego!\n");
	}
}

//Pre:El juego es valido.
//Post: Simula la partida, mostrando por pantalla si logro vencer o no.
void simular_partida(juego_t* juego){
	int resultado_batalla = 0;
	while(resultado_batalla == 0 || (resultado_batalla == 1 && cantidad_gimnasios(juego) > 0)){
		if(!juego->gimnasio_actual || cantidad_entrenadores(juego->gimnasio_actual) == 0){
			eliminar_gimnasio(juego->gimnasio_actual);
			juego->gimnasio_actual = proximo_gimnasio(juego);
		}		
		juego->oponente_actual = entrenador_en_tope(juego->gimnasio_actual);
		resultado_batalla = realizar_batalla_entrenadores(juego, SIMULAR_PARTIDA);
		if(resultado_batalla != -1){
			desapilar_entrenadores_de_gimnasio(juego->gimnasio_actual, true);
			juego->oponente_actual = NULL;
		}	
	}
	if(resultado_batalla == -1){
		imprimir_mensaje_derrota(juego);
		desapilar_entrenadores_de_gimnasio(juego->gimnasio_actual, true);
		juego->oponente_actual = NULL;
	}
	if(resultado_batalla == 1){
		imprimir_mensaje_victoria(juego);
	}
}