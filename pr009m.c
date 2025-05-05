#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
	int fd[2], result;
	size_t size;
	char resstring[86];
	if(pipe(fd)<0) {
		printf("Не удвлось создать пайп\n");
		exit(-1);
	}
	result = fork();
	if (result < 0) {
		printf("Ошибка при выполнении fork()\n");
		exit(-1);
	}
	else if (result > 0) {
		if (close(fd[0]) < 0) {
			printf("Не удалось закрыть входной поток процесса-родителя\n");
			exit(-1);
		}
		size = write(fd[1], "Информация от дочернего процесса для родителя", 86);
		if(size != 86) {
			 printf("Родителю не удалось записать всю строку в пайп\n");
			 exit(-1);
		}
		if (close(fd[1] < 0)) {
			printf("Родителю не удалось закрыть выходной поток\n");
			exit(-1);
		}
		printf("Процесс родитель завершил работу\n");
	}
	else {
		if (close(fd[1])<0) {
		printf("Ребенку не удалось закрыть входной поток\n");
		exit(-1);
		}
		size = read(fd[0], resstring, 86);
		if(size < 0) {
			printf("Не удалось процессу ребенку проситать строку\n");
			exit(-1);
		}
		printf("Строка, прочитанная дочерним процессам: %s\n", resstring);
		if (close(fd[0]<0)) {
			printf("Не удалось закрыть входной поток процесса ребенка\n");
			exit(-1);
		}
	}
	return 0;
}

