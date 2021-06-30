(Aclaro que mi teclado no tiene tildes)

El readme va a estar dividido en distintas secciones, para facilitar la lectura: 1)Introduccion y breve explicacion del funcionamiento del programa
                                                                                 2)Compilacion y ejecucion
                                                                                 3)Breve explicacion de como fue implementado el programa
                                                                                 4)Explicacion de los conceptos pedidos en el pdf

1)Introduccion: El trabajo presentado es un tipo de dato abstracto (desde ahora TDA) lista, con funcionalidades de pila y cola. Esto quiere decir que nuestro TDA puede ser utilizado como lista, cola o pila segun se convenga. Ampliaremos mas sobre que son y cual es su utilidad en el inciso 4. A su vez, tambien tiene implementado un iterador interno y uno externo. Tambien ampliaremos sobre este tema en el inciso 4. Junto con el trabajo presentado vienen pruebas creadas por el alumno (Vease yo) para asegurar que el TDA funciona de la manera esperada para cualquier caso requerido.

En cuanto a la funcionalidad del programa, fue decidido por la catedra que el TDA sea implementado con nodos simplemente enlazados, esto quiere decir que los elementos de la lista estan guardados en nodos en la memoria, y estos a su vez guardan la direccion de memoria del siguiente nodo. Esto permite que los distintos elementos pertenecientes a la lista no tengan que estar contiguos en la memoria.
Procedere a explicar las distintas funciones utilizadas para la realizacion del trabajo. Para esto, las dividiremos en cuatro grupos:
A)Funciones de lista: a)lista_crear: Crea la lista e inicializa sus valores. 
                      b)lista_insertar: Inserta un elemento al final de la lista. 
                      c)lista_insertar_en_posicion: Inserta un elemento en una posicion determinada de la lista.
                      d)lista_borrar: Borra el elemento final de la lista.
                      e)lista_borrar_de_posicion: Borra el elemento que esta en la posicion elegida.
                      f)lista_elemento_en_posicion: Devuelve el elemento de la posicion pedida.
                      g)lista_ultimo: Devuelve el ultimo elemento de la lista.
                      h)lista_vacia: Devuelve true si la lista esta vacia, false si no.
                      i)lista_elementos: Devuelve la cantidad de elementos que tiene la lista.
                      j)lista_destruir: Destruye la lista y todos sus nodos.

B)Funciones de pila: a)lista_apilar: Apila un elemento.
                     b)lista_desapilar: Desapila un elemento.
                     c)lista_tope: Devuelve el elemento que esta en el tope de la pila.
    
C)Funciones de cola: a)lista_encolar: Encola un elemento.
                     b)lista_desencolar: Desencola un elemento.
                     c)lista_primero: Devuelve el primer elemento de la cola.

D)Funciones del iterador: a)lista_iterador_crear: Crea el iterador para una lista determinada. Inicializa sus valores.
                          b)lista_iterador_tiene_siguiente: True si hay mas elementos sobre los que iterar, false si no.
                          c)lista_iterador_avanzar: Avanza el iterador al siguiente elemento de la lista.
                          d)lista_iterador_elemento_actual: Devuelve el elemento del nodo en el que esta el iterador.
                          e)lista_iterador_destruir: Destruye el iterador, liberando la memoria que tenia reservada.
                          f)lista_con_cada_elemento: Recorre la lista y le aplica a cada elemento la funcion que le llega por parametro. Esta funcion devuelve 
                            true si hay que seguir recorriendo, false si no. Devuelve la cantidad de elementos sobre los que itero.

2)Compilacion y ejecucion: El programa debera ser compilado con la linea: 
  gcc lista.c mis_pruebas.c pa2mm.h -o mis_pruebas -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
Para su ejecucion se debera usar ./mis_pruebas para una ejecucion normal, y para ejecutar con valgrind se debera usar: 
  valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./mis_pruebas

3)En este inciso voy a explicar brevemente como implemente las distintas funciones. Primero que nada, durante todo el programa elegi un camino iterativo, en vez de uno recursivo. La razon es simplemente estilo propio. Ahora procedo a comentar algunas funciones que me parecieron interesantes:
    a)lista_insertar:Me aproveche de que la lista tiene un puntero al nodo final para poder hacer la funcion O(1)
    b)lista_insertar_en_posicion: Dividi la funcion en 3 casos. Si la posicion era la ultima o mayor(es decir afuera), llamo a lista_insertar. Si es la primera, inserto
                                  al principio. Si es en el medio, itero hasta llegar al nodo en la posicion anterior y hago las operaciones correspondientes.
    c)lista_borrar: En esta ocasion no me pude aprovechar del puntero al nodo final, ya que luego no podriamos fijar al nodo final como el nodo anterior al borrado.
                    Por ende, iteramos hasta llegar al anteultimo, lo elegimos como nodo final y borramos su siguiente.
    d)lista_borrar_en_posicion: Al igual que en el caso de insertar, la dividi en 3 casos. Estos son los mismos que en el caso de insertar.

4)a)Lista: Una lista es un conjunto ordenado de elementos. En nuestro caso, estos elementos estan almacenados en nodos, los cuales estan almacenados en la memoria 
           dinamica, y poseen un puntero al nodo siguiente. Esto quiere decir que nuestra lista es "simplemente enlazada". Si fuese "doblemente enlazada", tendria un
           puntero al nodo anterior y uno al nodo siguiente.
  b)Pila: Una pila tambien es un conjunto ordenado de elementos, pero con la particularidad de que tiene una politica "LIFO". Esto quiere decir Last In First Out.
          Por ende, el ultimo elemento que se inserto va a ser el primero que salga.
    Cola:La unica diferencia entre una pila y una cola es su politica. La cola tiene una politica "FIFO", First in First Out. Esto significa que, dado un conjunto
         de elementos, el primero que entro a la cola es el primero que sale.
  c)Iteradores: Los iteradores nos permiten recorrer nuestra lista de una manera mas "eficiente". Sin la existencia de ellos, si quisieramos recorrer nuestra lista 
                para procesar cada elemento, tendriamos que hacer un loop y a su vez llamar a lista_elemento_en_posicion(). Esto significaria una complejidad O(N2).
                Con los iteradores, la complejidad seria O(N), ya que estos recorren la lista elemento por elemento solo una vez. Hay dos tipos de iteradores:
                I)Externo: El iterador externo es un TDA aparte, con sus propias funciones que pone a disposicion del usuario para que el mismo lo utilice como le 
                            convenga.
                II)Interno: El iterador interno es una funcion a la cual el usuario le tiene que pasar una funcion propia para que esta procese los datos. El iterador
                            va a recorrer toda la lista por si mismo o hasta que la funcion lo pare, y le va a aplicar la funcion creada por el usuario a todos los
                            elementos recorridos. A diferencia del iterador externo, simplemente con llamar al iterador interno y pasarle la funcion, el solo va a 
                            recorrer y procesar la lista.


