(Aclaro que mi teclado no tiene tildes)

El readme se dividira en distintas secciones: 1) Introduccion
                                              2) Compilacion y ejecucion
                                              3) Breve explicacion del funcionamiento del programa
                                              4) Explicacion de los conceptos pedidos en el pdf

1) Introduccion: El trabajo presentado es un programa que, dado un arrecife de pokemones, que debe estar en formato txt, traslada a los pokemones deseados
a un acuario, para luego crear un archivo txt nuevo, con todos los pokemones que tiene el acuario.

2)Compilacion y ejecucion: El programa debe ser compilado con la linea ggc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca
Para ejecutarlo, la linea sera ./evento_pesca ruta_del_arrecife.txt ruta_del_acuario.txt. En caso de que falte algun parametro, o de que estos no sean txt, el programa
terminara su ejecucion.

3) Procedo a explicar como implemente las distintas funciones que venian en evento_pesca.h
   a)crear_arrecife: Crea un arrecife, que sera llenado con un loop while que lee de un archivo de texto.Seguira hasta que termine el archivo, una linea de este sea
    erronea, o hasta que al intentar hacer el realloc de error. Cuando pasa cualquiera de las tres cosas, devuelve el arrecife.
   b)crear_acuario: Crea un acuario e inicializa sus variables. Si hay algun error, devuelve NULL.
   c)trasladar_pokemon: Itero dos veces sobre el arrecife. La primera, cuento cada pokemon que cumple la condicion pedida por la funcion que viene por parametro.
    Si la cantidad de pokemones pedidos es mayor a la cantidad de pokemones que cumplen esta condicion, se devuelve error. Si hay suficientes pokemones para trasladar,
    itero de nuevo sobre el arrecife. Cuando se encuentra con un pokemon que satisface la condicion, intenta agregarlo al acuario. Si hay algun error, deja todo como
    estaba antes. Si logra agregar el pokemon al acuario, lo saca del arrecife.
   d)censar_arrecife:Itera sobre el arrecife, y en cada iteracion usa el procedimiento que llega por parametro para listar al pokemon.
   e)guardar_datos_acuario: Itera sobre el acuario, y en cada iteracion imprime en el archivo de texto el pokemon
   f)liberar_acuario y liberar_arrecife: Las dos funcionan igual, primero se libera al puntero al vector de pokemones, y despues al arrecife/acuario.

4) a)Punteros: Un puntero es una variable que "apunta" a la direccion de memoria de otra variable. Deben ser del mismo tipo, es decir un int* puntero debe apuntar a la
     direccion de memoria de un int. Mediante un puntero se puede modificar la variable a la que apunta.
   b)Aritmetica de punteros: Hace referencia a todas las operaciones que se realizan con punteros. Hay varios operadores para esto. Esta el *, que sirve para ver el
     valor al que apunta el puntero, esta & para ver la direccion de una variable, y tambien se le puede sumar enteros a un puntero. Por ejemplo, si tenemos un puntero
     que apunta a un vector de int, si usamos *(puntero+1) estariamos accediendo a la segunda celda del vector. Hay que tener cuidado con esto, ya que se puede acceder
     a memoria que no es nuestra.
   c)Punteros a funciones: Son punteros que apuntan a la direccion de memoria de una funcion. Esta direccion de memoria esta en el .code del programa. Con el puntero,
     se puede ejecutar la funcion cuando se desee.
   d) Malloc y Realloc: Malloc reserva una cantidad N de bytes en el heap (memoria dinamica) y devuelve un puntero a la primera posicion de estos bytes. A realloc hay
      que pasarle un puntero y una cantidad N de bytes. Si N es mas grande que la cantidad de bytes que tenia el primer puntero, lo agrando. Si es mas chico, 
      lo achica. Realloc buscara una cantidad N de bytes contiguos en memoria y los va a llenar hasta donde pueda con lo que habia en el primer puntero.




