(Aclaro que mi teclado no tiene tildes)

El readme va a estar dividido en distintas secciones, para facilitar la lectura: 1)Introduccion y breve explicacion del funcionamiento del programa
                                                                                 2)Compilacion y ejecucion
                                                                                 3)Explicacion mas detallada del funcionamiento del programa.

1)Introduccion: El trabajo presentado es un programa que simula el trayecto de un entrenador pokemon en su busqueda de derrotar a todos los gimnasios y consagrarse como maestro pokemon. A su vez, va a ir acompaniado de distintos archivos de texto para cargar como gimnasios, y un archivo de texto para cargar como personaje principal. Por ultimo, tambien esta acompaniado de algunas pruebas.

2)La linea para compilar es:
gcc main.c menu.c juego.c batallas.c estructuras.c administrativas.c heap.c lista.c -o main -Wall -g -std=c99 -Werror -Wconversion -Wtype-limits -pedantic -O0
Para ejecutar, la linea es ./main

La linea para compilar las pruebas del heap es:
gcc mis_pruebas_heap.c heap.c -o mis_pruebas_heap -Wall -g -Werror -std=c99 -Wconversion -Wtype-limits -pedantic -O0
Y para ejecutar: valgrind --show-reachable=yes --leak-check=full --track-origins=yes ./mis_pruebas_heap

La linea para compilar las pruebas de las estructuras es:
gcc mis_pruebas_estructura.c lista.c estructuras.c -o mis_pruebas_estructuras -Wall -g -Werror -std=c99 -Wconversion -Wtype-limits -pedantic -O0
Y para ejecutar: valgrind --show-reachable=yes --leak-check=full --track-origins=yes ./mis_pruebas_estructuras

En cuanto a la ejecucion del programa principal, recomiendo usar los archivos personaje.txt y gimnasios.txt

3) En este apartado explicare mas en detalle el desarrollo y funcionamiento del programa. Lo hare en el mismo orden en el que yo lo fui haciendo.
Lo primero que hice, como fue aconsejado en las clases, fue el heap.c. Al tener que ser con void*, tuve que agregarle un comparador y un destructor. Tambien esta implementado en memoria dinamica.
Luego, empece con el programa propiamente dicho. Este esta dividido en 3 partes. Estructuras, juego y menu.
a) Las estructuras son distintos tipos de dato que necesite crear para el funcionamiento del juego. Estos son Pokemon, Entrenador y Gimnasio. Intente crearlos como si fuesen TDAs, con pruebas incluidas. Los pokemones que posee un entrenador estan guardados en una lista. La decision fue tomada simplemente por comidad. Podria haber usado un vector estatico de tamanio 6, pero teniendo ya la lista implementada, creo haber ahorrado tiempo. A su vez, al TDA lista le agregue un destructor. Esto facilito mucho el manejo de memoria, ya que al destruir un entrenador simplemente tenia que destruir la lista, y esta se encargaba del manejo de memoria. En el caso del gimnasio, para los entrenadores que estan el mismo use una pila. Esto fue por varias razones. Primero, debido a como se desarrollan las peleas en el gimnasio. Como el personaje principal solo debe pelear contra cada entrenador 1 vez hasta vencerlo, y luego avanzar al siguiente, este pelea con el entrenador que esta en el tope de la pila, y si lo vence, desapilamos y peleamos con el que esta en el tope. Ademas, como el formato del archivo de gimnasios tiene al lider inmediatamente abajo del nombre del gimnasio, el lider sera el entrenador que este mas abajo en la pila.

b) En el juego hice las estructuras que tenian que ver con este mismo. El personaje principal, y el juego. El personaje principal tiene sus medallas, la cantidad de enemigos derrotados, su nombre y sus pokemones. Estos estan guardados en dos listas distintas, una lista de pokemones de batalla y una lista de pokemones capturados.
Otra vez, utilice listas ya que son comodas de utilizar, y con el destructor implementado facilitan mucho el manejo de memoria. A su vez, pude aprovecharme del iterador interno para imprimir los pokemones del personaje. El juego per se, tiene un personaje principal, un heap de gimnasios, un gimnasio actual y un oponente actual. Como dificultad que tuve en esta parte del desarrollo estuvieron las funciones de cargar desde archivo. Si bien funcionan (O eso creo), no pude lograr que esten modularizadas.

c) Por ultimo estan los menues. Estos son los que interactuan con el usuario. Se tiene las opciones de jugar una partida, o simularla.
