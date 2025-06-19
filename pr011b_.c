//Программа №1 для иллюстрации работы с разделяемой памятью

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main() {
	int *array;	//азатель на адрес, по которому будет находиться наша разделяемая память
	int  shmid;	//PC-дескриптор для обращения к области разделяемой памяти
	int new = 1;	//Флаг, указывающий на необходимость создания нового массива в разделяемой памяти
	char pathname[] = "pr011a_.c";	//Имя файла, предназначенное для генерации IPC-ключа
	long i;
	key_t key;	//Переменная для хранения IPC-ключа
	
	if ((key = ftok(pathname, 0))<0) {	//Генерация IPC-ключа
		printf("Не удалось сгенерировать IPC-ключ\n");
		exit(-1);
	}

	if ((shmid = shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL))<0) {		//Создание разделения памяти в эксклюзивном режиме

		if(errno != EEXIST) {
			printf("Не удалось создать область разделяемой памяти\n");
			exit(-1);
		}

		else {
			if((shmid = shmget(key, 3*sizeof(int), 0))<0) {
				printf("Не удалось найти разделяемую память\n");
				exit(-1);
			}
			new = 0;
		}
	}

	if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("Не удалось присоединить область разделяемой памяти к адресному пространству текущего процесса\n");
		exit(-1);
	}

	if(new) {
		array[0] = 0;
		array[1] = 1;
		array[2] = 1;
	}

	else {
		array[1] += 1;
	for(i=0; i<1000000000L; i++);
		array[2] += 1;
	}

	printf("Кол-во запусков первой программы:%d, кол-во запуской второй программы:%d, общее кол-во запусков:%d\n", array[0], array[1], array[2]);

	if(shmdt(array) < 0) {
		printf("Не удалось отсоединить область разделяемой памяти");
		exit(-1);
	}
	
	return 0;

}
