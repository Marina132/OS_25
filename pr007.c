//Изменение пользовательского контекста во время выполнения программы
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
	printf("Программа начала работу...\n\n");
	pid_t pid, ppid;
	int result;
	pid = getpid();
	ppid = getppid();
	printf("Ид. процесса: %d\n", pid);
	printf("Ид. родительского процесса: %d\n\n", ppid);
	result = fork();
	if (result > 0) {
		printf("Родительский процесс...\n");
		printf("Ид. процесса: %d, Ид. процесса-ребенка %d\n", pid, result);
		printf("Ид. родительского процесса: %d\n", ppid);
		printf("Родитель завершил работу\n\n");
	}
	else if (result == 0) {
		printf("Дочерний процесс...\n\n");
		(void) execle("./pr003.out", "./pr003.out", 0, envp);
		printf("Ошибка при выполнении системного вызова exec\n");
		exit(-1);
	}
	else {
		printf("Произошла ошибка при выполнении вызова fork\n");
		exit(-1);
	}
	return 0;
}
