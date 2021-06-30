#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "evento_pesca.h"

#define RESET_COLOR    "\x1b[0m"
#define NEGRO        "\x1b[30m"
#define ROJO     "\x1b[31m"
#define VERDE        "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define AZUL     "\x1b[34m"
#define MAGENTA  "\x1b[35m"
#define CYAN     "\x1b[36m"
#define BLANCO  "\x1b[37m"
#define COLOR_AZUL     "azul"
#define COLOR_MORADO     "morado"
#define COLOR_ROJO     "rojo"
#define COLOR_VERDE     "verde"
#define COLOR_NEGRO     "negro"
#define COLOR_AMARILLO     "amarillo"
#define COLOR_MARRON     "marron"
#define COLOR_ROSA     "rosa"

const int IGUALES = 0;
const int VELOCIDAD_BAJA = 40;
const int VELOCIDAD_ALTA = 70;
const int PESO_PESADO = 20;
const int NOMBRE_ESPECIE_CORTO = 5;
const int LETRA_S = 'S';


//Pre: Recibe un pokemon con caracteristicas validas.
//Post: TRUE si su color es azul y pesa mas que 20, FALSE si no.
bool es_color_azul_y_peso_pesado(pokemon_t* pokemon){
	if((strcmp(pokemon->color, COLOR_AZUL) == IGUALES) && (pokemon->peso > PESO_PESADO)){
		return true;
	}
	return false;
}
//Pre: Recibe un pokemon con caracteristicas validas.
//Post: TRUE si su primera letra es S y su velocidad esta entre 40 y 70, FALSE si no.
bool es_primera_letra_s_y_velocidad_media(pokemon_t* pokemon){
	if((pokemon->especie[0]==LETRA_S) && (pokemon->velocidad > VELOCIDAD_BAJA) && (pokemon->velocidad > VELOCIDAD_ALTA)){
		return true;
	}

	return false;
}

//Pre: Recibe un pokemon con caracteristicas validas.
//Post: TRUE si su primera letra es par y su ultima impar, FALSE si no.
bool es_primera_letra_par_y_ultima_impar(pokemon_t* pokemon){
	unsigned int largo = strlen(pokemon->especie);
	if(((int)pokemon->especie[0])%2==0 && ((int)pokemon->especie[largo-1])%2!=0){
		return true;
	}
	return false;
}

//Pre: Recibe un pokemon con caracteristicas validas.
//Post:TRUE si el largo de su especie es menor a 5, FALSE si no.
bool es_nombre_especie_corto(pokemon_t* pokemon){
	unsigned int largo = strlen(pokemon->especie);
	if(largo <= NOMBRE_ESPECIE_CORTO){
		return true;
	}

	return false;
}

//Pre: Recibe un pokemon con caracteristicas validas.
//Post:TRUE si su color es morado y su peso par, FALSE si no.
bool es_color_morado_y_peso_par(pokemon_t* pokemon){
	if((strcmp(pokemon->color, COLOR_MORADO)==IGUALES) && ((pokemon->peso)%2 == 0)){
		return true;
	}

	return false;
}
//Pre: El pokemon tiene una especie valida.
//Post: Imprime por consola la especie del pokemon.
void listar_por_nombre(pokemon_t* pokemon){
	printf("%s\n", pokemon->especie);
}

//Pre: El pokemon tiene una color y especie valida.
//Post: Imprime por consola la especie del pokemon con letra de su color.
void listar_por_nombre_con_color(pokemon_t* pokemon){
	if(strcmp(pokemon->color, COLOR_AZUL) == IGUALES){
		printf(AZUL "%s\n" RESET_COLOR, pokemon->especie);
	}else if(strcmp(pokemon->color, COLOR_ROJO) == IGUALES){
		printf(ROJO "%s\n" RESET_COLOR, pokemon->especie);
	}else if(strcmp(pokemon->color, COLOR_VERDE) == IGUALES){
		printf(VERDE "%s\n" RESET_COLOR, pokemon->especie);
	}else if(strcmp(pokemon->color, COLOR_NEGRO) == IGUALES || strcmp(pokemon->color, COLOR_MARRON) == IGUALES){
		printf(NEGRO "%s\n" RESET_COLOR, pokemon->especie);
	}else if(strcmp(pokemon->color, COLOR_MORADO) == IGUALES || strcmp(pokemon->color, COLOR_ROSA) == IGUALES){
		printf(MAGENTA "%s\n" RESET_COLOR, pokemon->especie);
	}else if(strcmp(pokemon->color, COLOR_AMARILLO) == IGUALES){
		printf(AMARILLO "%s\n" RESET_COLOR, pokemon->especie);
	}else{
		printf("%s\n", pokemon->especie);
	}
}

//Pre: El pokemon tiene una caracteristicas validas.
//Post: Imprime por consola las caracteristicas del pokemon.
void listar_por_caracteristicas(pokemon_t* pokemon){
	printf("\n---------------------------------\n");
	printf("|  Especie: %s                     \n", pokemon->especie);
	printf("|  Velocidad: %i                   \n", pokemon->velocidad);
	printf("|  Peso: %i                        \n", pokemon->peso);
	printf("|  Color: %s                       \n", pokemon->color);
	printf("\n---------------------------------\n");

}

//Pre: El pokemon tiene una caracteristicas validas.
//Post: Imprime por consola las caracteristicas del pokemon.

void listar_por_caracteristicas_en_renglon(pokemon_t* pokemon){
	printf("\nEspecie: %s | Velocidad: %i | Peso: %i | Color: %s\n", pokemon->especie, pokemon->velocidad,
		   pokemon->peso, pokemon->color);
}

//Pre: El pokemon tiene una caracteristicas validas.
//Post: Imprime por consola las caracteristicas del pokemon con el color correspondiente.
void listar_por_caracteristicas_con_color(pokemon_t* pokemon){
	if(strcmp(pokemon->color, "azul") == IGUALES){
		printf(AZUL "\nEspecie: %s | Velocidad: %i | Peso: %i" RESET_COLOR, pokemon->especie, pokemon->velocidad, 
			   pokemon->peso);
	}else if(strcmp(pokemon->color, "rojo") == IGUALES){
		printf(ROJO "\nEspecie: %s | Velocidad: %i | Peso: %i" RESET_COLOR, pokemon->especie, pokemon->velocidad, 
			   pokemon->peso);
	}else if(strcmp(pokemon->color, "verde") == IGUALES){
		printf(VERDE "\nEspecie: %s | Velocidad: %i | Peso: %i" RESET_COLOR, pokemon->especie, pokemon->velocidad, 
			   pokemon->peso);
	}else if(strcmp(pokemon->color, "negro") == IGUALES || strcmp(pokemon->color, "marron") == IGUALES){
		printf(NEGRO "\nEspecie: %s | Velocidad: %i | Peso: %i" RESET_COLOR, pokemon->especie, pokemon->velocidad, 
			   pokemon->peso);
	}else if(strcmp(pokemon->color, "morado") == IGUALES|| strcmp(pokemon->color, "rosa") ==IGUALES){
		printf(MAGENTA "\nEspecie: %s | Velocidad: %i | Peso: %i" RESET_COLOR, pokemon->especie, pokemon->velocidad, 
			   pokemon->peso);
	}else if(strcmp(pokemon->color, "amarillo") == IGUALES){
		printf(AMARILLO "\nEspecie: %s | Velocidad: %i | Peso: %i" RESET_COLOR, pokemon->especie, pokemon->velocidad, 
			   pokemon->peso);
	}else{
		printf("\nEspecie: %s | Velocidad: %i | Peso: %i", pokemon->especie, pokemon->velocidad, pokemon->peso);
	}
}



//Pre: El resultado es valido (0 o 1)
//Post: Imprime por consola el resultado del traslado.
void imprimir_resultado(int resultado){
	if(resultado == -1){
		printf("\nHubo un error al trasladar los pokemones\n");
	}else{
		printf("\nTraspaso realizado con exito\n");
	}
}

int main(int argc, char* argv[]){

	if(argc != 3){
		printf("Los argumentos son invalidos");
		return 0;
	}

	arrecife_t* arrecife = crear_arrecife(argv[1]);
	acuario_t* acuario = crear_acuario();
	if(arrecife == NULL || acuario == NULL){
		liberar_acuario(acuario);
		liberar_arrecife(arrecife);
		return 0;
	}


	bool (*ptr_traslado)(pokemon_t*);
	void (*ptr_listado)(pokemon_t*);
	int resultado = 0;

	ptr_traslado = es_color_azul_y_peso_pesado;
	ptr_listado = listar_por_nombre;
	resultado = trasladar_pokemon(arrecife, acuario, ptr_traslado, 3);
	censar_arrecife(arrecife, ptr_listado);
	imprimir_resultado(resultado);

	ptr_traslado = es_primera_letra_s_y_velocidad_media;
	ptr_listado = listar_por_caracteristicas;
	resultado = trasladar_pokemon(arrecife, acuario, ptr_traslado, 1);
	censar_arrecife(arrecife, ptr_listado);
	imprimir_resultado(resultado);

	ptr_traslado = es_nombre_especie_corto;
	ptr_listado = listar_por_nombre_con_color;
	resultado = trasladar_pokemon(arrecife, acuario, ptr_traslado, 1);
	censar_arrecife(arrecife, ptr_listado);
	imprimir_resultado(resultado);

	ptr_traslado = es_primera_letra_par_y_ultima_impar;
	ptr_listado = listar_por_caracteristicas_en_renglon;
	resultado = trasladar_pokemon(arrecife, acuario, ptr_traslado, 1);
	censar_arrecife(arrecife, ptr_listado);
	imprimir_resultado(resultado);

	ptr_traslado = es_color_morado_y_peso_par;
	ptr_listado = listar_por_caracteristicas_con_color;
	resultado = trasladar_pokemon(arrecife, acuario, ptr_traslado, 1);
	censar_arrecife(arrecife, ptr_listado);
	imprimir_resultado(resultado);

	resultado = guardar_datos_acuario(acuario, argv[2]);
	liberar_acuario(acuario);
	liberar_arrecife(arrecife);

	return 0;
}