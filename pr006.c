//Программа, анализирующая аргументы командной строки
#include <stdio.h>

int main(int argc, char* argv[], char* envp[]) {
	//Количество аргументов, переднных программе - argc 
	printf("Программе передано %d агрументов\n\n", argc);

	//Cписок значений аргументов (массив argv)
	for (int i=0; i<argc; i++) 
		printf("Аргумент [%d]: %s\n", i, argv[i]);
	printf("\n");
}

