(Aclaro que mi teclado no tiene tildes)

El readme va a estar dividido en distintas secciones, para facilitar la lectura: 1)Introduccion y breve explicacion del funcionamiento del programa
                                                                                 2)Compilacion y ejecucion
                                                                                 3)Explicacion mas detallada de algunas funciones particulares
                                                                                 4)Explicacion de los conceptos pedidos en el pdf

1)Introduccion: El trabajo presentado es un Tipo de Dato Abstracto(Desde ahora TDA) de tipo Arbol Binario de Busqueda(Desde ahora ABB). Ampliaremos sobre que es un ABB  y cual es su diferencia con un arbol binario en la seccion 4 . Las funcionalidades del programa seran explicadas en la brevedad. A la par del TDA estan las pruebas creadas por el alumno(Vease yo) para garantizar el funcionamiento de este mismo en cualquier situacion que sea requerida por el usuario.

En cuanto a la funcionalidad del programa, fue decidido por la catedra que sea implementado con nodos que esten en la memoria dinamica, y que tengan punteros hacia sus hijos. Esto permite que los elementos no tengan que estar contiguos en la memoria.
Procedere a explicar las distintas funcionalidades implementadas:
    a)arbol_crear:Crea el arbol, reservando la memoria necesaria. Inicializa sus valores en NULL
    b)arbol_insertar: Guarda el elemento que llega por parametro en un nodo, y lo inserta en el arbol. Reserva la memoria correspondiente.
    c)arbol_borrar: Elimina el nodo que tenga al elemento pasado por parametro. Si no lo encuentra, devuelve error.
    d)arbol_buscar: Busca el elemento pasado por parametro. Si no lo encuentra, devuelve error.
    e)arbol_raiz: Devuelve el elemento que esta en el nodo raiz. Si la raiz o el arbol es nulo, devuelve NULL.
    f)arbol_vacio: Devuelve true si esta vacio o el arbol es nulo, false si no.
    g)arbol_recorrido_inorden/preorden/postorden: Recorre el arbol de la forma pedida, y va llenando un vector que le llega por parametro con los elementos del arbol.
    h)arbol_destruir: Libera la memoria del arbol, y de todos los nodos restantes. Si es necesario, aplica el destructor a los elementos de los nodos.
    i)abb_con_cada_elemento:Recorre el arbol y le aplica la funcion que le llega por parametro a cada elemento de este mismo.

2)Compilacion y ejecucion: El programa debera ser compilado con la linea: 
  gcc abb.c mis_pruebas.c pa2mm.h -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
Para su ejecucion se debera usar ./abb para una ejecucion normal, y para ejecutar con valgrind se debera usar: 
  valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb

3)En este inciso voy a explicar con un poco mas de detalle como implemente las distintas funciones. Primero que nada, intente realizar una implementacion del tipo recursivo. En general lo logre, menos en la funcion de buscar predecesor inorden, que es iterativa. Procedo a explicar algunas funciones interesantes:
    a)arbol_insertar, arbol_buscar, arbol_borrar: Agrupo estas tres ya que, a grandes rasgos, tienen la misma estructura. Solo difieren en lo que hacen al procesar.
      Recursivamente vamos comparando los nodos con el elemento pasado por parametro. Ahora explicamos:
      a.1)arbol_insertar:Cuando se compara con el elemento de un nodo, y el hijo izquierdo o derecho(segun el caso) de este es NULL, insertamos el elemento nuevo.
      a.2)arbol_buscar:Se compara con el elemento de cada nodo, y si esa comparacion da 0 lo devuelve. Si no, sigue iterando de forma recursiva hasta llegar a un nodo
          NULL.
      a.3)arbol_borrar:Hace lo mismo que arbol_buscar, pero al encontrar el nodo, lo elimina. Hay 3 casos para la eliminacion:
            1)Nodo sin hijos: Simplemente lo elimina y hace que su nodo padre apunte a NULL.
            2)Nodo con un hijo: LO elimina, y hace que su nodo padre apunte a su hijo.
            3)Nodo con dos hijos: Lo elimina, y hace que su nodo padre apunte a su predecesor inorden.
    b)arbol_recorrido_inorden/preorden/postorden: Hacen lo mismo, solo cambiando el orden de las operaciones. Recorren el arbol de forma recursiva, llenando un vector
      que llega por parametro con los elementos de cada nodo. Lo hace hasta llenar el vector o llegar al final del arbol. En el recorrido postorden, tuve que agregar
      un booleano, ya que si no seguia recorriendo el arbol aunque el vector estuviese lleno.
    c)abb_con_cada_elemento:Esta funcion recorre el arbol de 3 formas distintas, segun lo que le sea pedido, y le aplica la funcion a cada nodo por el que pasa hasta
      que esta devuelva true. Estos recorridos son, de alguna forma, un caso mas general de las funciones del inciso b), pero no pude llegar a implementarlo de esa 
      forma por falta de tiempo.
4)ABB: Un Arbol Binario de Busqueda es un tipo de dato abstracto que sirve para almacenar informacion de una manera mas eficiente. Cada nodo tiene una clave, y un 
  puntero hacia su hijo izquierdo y derecho. Su hijo izquierdo tendra una clave menor que la suya, y su hijo derecho una mayor. De esta forma, las operaciones de
  busqueda, insercion y borrado son mas eficientes. La diferencia con un arbol binario, es que estos no tienen el concepto de claves. Por ende, no estan ordenados
  y seria muy dificil encontrar un elemento en especifico, ya que habria que recorrer a mano todos los nodos.
 Funcion de destruccion: Tener una funcion de destruccion le permite al usuario crear elementos que esten guardados en memoria dinamica, o structs que tengan algunos
 campos en memoria dinamica y otros no, etc. Le da mas opciones al usuario al momento de usar nuestro TDA. Si esta funcion no existiese, el usuario estaria obligado a
 usar solo elementos que esten en el stack.
 Complejidades: 
    a)arbol_insertar/arbol_borrar/arbol_buscar: Las tres tienen dos casos: a)Si el arbol esta balanceado(NO degenero en lista) la complejidad es mas baja, ya
      que no tiene que recorrer todos los nodos, si no que se va comparando con cada nodo del arbol y dependiendo de si es mayor o menor, va hacia la derecha o hacia la 
      izquierda. Esto permite que llegar hasta el lugar del arbol donde queremos hacer la operacion sea mucho mas rapido. Su complejidad es O(log n). Si el arbol si 
      degenero en una lista, quiere decir que a fines practicos, es el arbol es basicamente una lista. Esto quiere decir que en el peor de los casos, al querer insertar
      un elemento, si tenemos que insertar al final de un arbol, tendriamos que pasar por N elementos antes de llegar. La complejidad seria O(n).
    b)arbol_crear/arbol_vacio/arbol_raiz: Son todas operaciones basicas, su complejidad es O(1)
    c)arbol_recorrido_inorden/preorden/postorden: Como esta funcion tiene que recorrer todos los nodos(un n numero de nodos) de nuestro arbol, su complejidad es O(n)
      Notese que da igual si degenero en lista o no nuestro arbol, ya que tiene que recorre todo igualmente.
    d)arbol_destruir:Esta funcion tiene que ir a cada nodo y liberarlo, y por ende es O(n).
    e)abb_con_cada_elemento:Al igual que los recorridos del arbol, esta funcion es O(n), ya que tiene que recorrer, si es necesario, todos los nodos del arbol.








