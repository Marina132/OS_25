#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
	int user_id, group_id;
	user_id = getuid();
	group_id = getgid();
	printf("Идентефикатор пользователя: %d\n", user_id);
	printf("Идентефикатор группы: %d\n", group_id);
	return 0;
}

