//Программа. пораждающая дочерний процесс (часть 1)
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
	printf("Начальное значение а: %d\n\n", a);
	b = fork();
	a = a+1;
	procid = getpid();
        pprocid = getppid();
	printf("После вызова fork()\n");
        printf("Ид. текущю процесса: %d\nИд.род.процесса: %d\n Новое значение а: %d\n\n", procid, pprocid, a);
	return 0;
}
