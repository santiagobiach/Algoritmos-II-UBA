#ifndef __MENU_H__
#define __MENU_H__

#include "juego.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


//Pre: El juego es valido.
//Post: Muestra el menu de inicio al usuario. Interactua con el.
void menu_de_inicio(juego_t* juego);

//Pre: El juego es valido.
//Post: Muestra el menu de gimnasio al usuario. Interactua con el.
void menu_de_gimnasio(juego_t* juego);

//Pre: El juego es valido.
//Post: Muestra el menu de batalla al usuario. Interactua con el.
int menu_de_batalla(juego_t* juego);

//Pre: El juego es valido.
//Post: Muestra el menu de victoria al usuario. Interactua con el.
void menu_de_victoria(juego_t* juego);

//Pre: El juego es valido.
//Post: Muestra el menu de derrota al usuario. Interactua con el.
void menu_de_derrota(juego_t* juego);


#endif /* __MENU_H__*/