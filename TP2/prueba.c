#include <stdio.h>

int main(){
	char c;
	printf("Ingrese un caracter: ");
	char buffer[100];
	char* aux = fgets(buffer, 100, stdin);
	printf("\n HOla!%c", aux[0]);
	scanf(" %c", &c);
	printf("\n%c", c);



	return 0;
}