#include <stdio.h>
#include <stdlib.h>

/*
 * $ gcc -Wall -std=gnu99 -g -o phone_loop phone_loop.c
 * $ ./phone_loop
 */

int main(void) {
	char phone_loop[11];
	int integer;
	int error_flag = 0;
	scanf("%s", phone_loop);
	while (scanf("%d", &integer) != EOF) {
		if (integer == -1) {
			printf("%s\n", phone_loop);
			error_flag = 0;
		} else if (integer >= 0 && integer <= 9) {
			printf("%c\n", phone_loop[integer]);
			error_flag = 0;
		} else {
			printf("ERROR\n");
			error_flag = 1;
		}
	}
	return error_flag;
}