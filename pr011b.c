//Программа №2 для иллюстрации работы с разделяемой памятью
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main() {
	//Указатель на адрес, по которому будет находиться наша разделяемая память
	int *array;
	//IPC-дескриптор для обращения к области разделяемой памяти
	int shmid;
	//Флаг, указывающий на необходимость создания нового масива в разделяемой памяти
	int new = 1;
	//Имя файла, предназначенное для генерации ipc-ключа
	char pathname[] = "pr011a.c";
	//Переменная для хранения ipc-ключа
	key_t key;

	//Генерация ipc-ключа
	if ((key = ftok(pathname, 0))<0) {
		printf("Не удалось сгенерировать ipc-ключ\n");
		exit(-1);
	}
	//Cоздание разделяемой памяти в эксклюзивном режиме 
	if ((shmid =  shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL))<0) {
		if(errno != EEXIST) {
			printf("Не удалось создать область разделяемой памяти\n");
			exit(-1);
		}
		else {
			if((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
				printf("Не удалось найти разделяемую память\n");
				exit(-1);
			}
			new = 0;
		}
	}	
	if((array = ( int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Не можем присоеденить область разделяемой памяти к адресному пространству текущего процесса\n");
		exit(-1);
	}
	if(new) {
		array[0] = 0;
		array[1] = 1;
		array[2] = 1;
	}
	else {
		array[1] += 1;
		array[2] += 1;
	}
	printf("Первая программа была запущено %d раз, вторая программа была запущена %d раз, общее количество запусков - %d\n", array[0], array[1], array[2]);
	if(shmdt(array) < 0) {
		printf("Не удалось отсоеденить область разделяемой памяти");
		exit(-1);
	}
	return 0;
}
