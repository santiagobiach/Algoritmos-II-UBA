#include "batallas.h"
#include "estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const double PI = 3.1415;

/*Este gimnasio se rige segun la simetria. El pokemon que tenga el promedio de stats mas alto ganara!*/
int funcion_batalla_1(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2){
		return -1;
	}
	pokemon_t* pokemon_1 = pkm_1;
	pokemon_t* pokemon_2 = pkm_2;
	int promedio_1 = (pokemon_1->velocidad +  pokemon_1->ataque + pokemon_1->defensa)/3;
	int promedio_2 = (pokemon_2->velocidad +  pokemon_2->ataque + pokemon_2->defensa)/3;
	if(promedio_1 >= promedio_2){
		return GANO_PRIMERO;
	}
	return GANO_SEGUNDO;
}

int contar_vocales(char string[MAX_NOMBRE]){
	int vocales = 0;
	for(int i = 0; i < strlen(string); i++){
		char letra_actual = (char)tolower(string[i]);
		if( letra_actual == 'a' || letra_actual == 'e' || letra_actual == 'i' || letra_actual == 'o' || letra_actual == 'u'){
			vocales++;
		}
	}
	return vocales;
}

/*En este gimnasio estan muy interesados en el analisis de los nombres. Ganara el pokemon cuya especie tenga mas vocales.*/
int funcion_batalla_2(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2){
		return -1;
	}
	pokemon_t* pokemon_1 = pkm_1;
	pokemon_t* pokemon_2 = pkm_2;
	int cantidad_vocales_1 = contar_vocales(pokemon_1->especie);
	int cantidad_vocales_2 = contar_vocales(pokemon_2->especie);

	if(cantidad_vocales_1 >= cantidad_vocales_2){
		return GANO_PRIMERO;
	}

	return GANO_SEGUNDO;
}
/*En este gimnasio les gustan mucho las esferas. Esta comprobado cientificamente que mientras mas cerca este la relacion entre la 
  defensa y la velocidad de PI, mas redondeado sera el pokemon.*/
int funcion_batalla_3(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2){
		return -1;
	}
	pokemon_t* pokemon_1 = pkm_1;
	pokemon_t* pokemon_2 = pkm_2;
	double relacion_1 = (double)((double)pokemon_1->defensa)/((double)pokemon_1->velocidad);
	double relacion_2 = (double)((double)pokemon_2->defensa)/((double)pokemon_2->velocidad);
	
	double distancia_a_pi_1 = fabs(PI-relacion_1);
	double distancia_a_pi_2 = fabs(PI-relacion_2);
	if(distancia_a_pi_1 <= distancia_a_pi_2){
		return GANO_PRIMERO;
	}

	return GANO_SEGUNDO;
}

int calcular_diferencia_estadisticas(pokemon_t* pokemon){
	int defensa = pokemon->velocidad;
	int ataque = pokemon->ataque;
	int velocidad = pokemon->defensa;
	if(velocidad >= defensa && velocidad >=ataque){
		return (velocidad - defensa - ataque);
	}else if(velocidad >= defensa && velocidad <=ataque){
		return (ataque - velocidad - defensa);
	}else if(velocidad >= ataque && velocidad <=defensa){
		return (defensa - velocidad - ataque);
	}else{
		if(defensa >= ataque){
			return (defensa - velocidad - ataque);
		}else{
			return (ataque - velocidad - defensa);
		}
	}
}

/*En este gimnasio les gusta el caos y la asimetria. Ganara el pokemon que tenga la mayor diferencia entre su mejor stats y las demas*/
int funcion_batalla_4(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2){
		return -1;
	}
	pokemon_t* pokemon_1 = pkm_1;
	pokemon_t* pokemon_2 = pkm_2;
	int diferencia_estadistica_1 = calcular_diferencia_estadisticas(pokemon_1);
	int diferencia_estadistica_2 = calcular_diferencia_estadisticas(pokemon_2);
	if(diferencia_estadistica_1 >= diferencia_estadistica_2){
		return GANO_PRIMERO;
	}
	return GANO_SEGUNDO;
}
/*Este gimnasio se rige segun la ley de Mewtwo, que Fuerza es igual a Ataque por Velocidad. Ganara el que golpee con mayor fuerza.*/
int funcion_batalla_5(void* pkm_1, void* pkm_2){
	if(!pkm_1 || !pkm_2){
		return -1;
	}
	pokemon_t* pokemon_1 = pkm_1;
	pokemon_t* pokemon_2 = pkm_2;
	int fuerza_1 = pokemon_1->velocidad * pokemon_1->ataque;
	int fuerza_2 = pokemon_2->velocidad * pokemon_2->ataque;
	if(fuerza_1 >= fuerza_2){
		return GANO_PRIMERO;
	}
	return GANO_SEGUNDO;
}