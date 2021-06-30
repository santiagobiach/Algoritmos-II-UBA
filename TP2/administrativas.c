#include "administrativas.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const int BUFFER = 1024;

char* leer_linea(char* memoria, int tamanio, FILE* archivo){
	char* linea_leida = NULL;
	linea_leida = fgets(memoria, tamanio, archivo);

	if(!linea_leida){
		return NULL;
	}
	size_t posicion_cero = strlen(memoria);
	if(posicion_cero == 0 || memoria[posicion_cero-1] !='\n'){
		char descartar[BUFFER];
		leer_linea(descartar, BUFFER, archivo);
	}

	memoria[posicion_cero-1] = 0;
	return memoria;
}