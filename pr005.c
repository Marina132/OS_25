//Программа. пораждающая дочерний процесс (часть 2).
//Процесс-родитель и процесс-ребенок должны выполнять разные действия
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	pid_t procid, pprocid;
        int a=0, b;
        procid = getpid();
        pprocid = getppid();
        printf("Перед вызовом fork()\n");
        printf("Ид. текущю процесса: %d\nИд.род.процесса: %d\n", procid, pprocid);
	printf("Начальное значение а: %d\n", a);
        b = fork();
	if (b<0) {
		//Во время выполнения fork() произошла ошибка.Выходим из программы с возвратом кода -1
		printf("Ошибка при выполнении fork()\n");
		exit(-1);//выход из программы
	}
	else if (b==0) {
		printf("\n\nПоявился дочерний,поцесс получил значение %d\n", b); 
        	a = a+1; //Проверяем извенение значения переменной а
        	procid = getpid();
        	pprocid = getppid();
        	printf("После вызова fork() в процессе-ребенке\n");
		printf("Ид. текущю процесса: %d\nИд.род.процесса: %d\nНовое значение а: %d\n", procid, pprocid, a);
	}
	else {
		printf("\n\nРодительский процесс после вызова fork() получил индефекатор ребенка %d\n", b);
		a = a+1111; //Проверяем извенение значения переменной а
		procid = getpid();
		pprocid = getppid();
                printf("Индефекаторы процесса-родителя:\n");
		printf("Ид. текущю процесса: %d\nИд.род.процесса: %d\nНовое значение а: %d\n", procid, pprocid, a);
	}
	return 0;
}
