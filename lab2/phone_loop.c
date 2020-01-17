#include <stdio.h>
#include <stdlib.h>

/*
 * $ gcc -Wall -std=gnu99 -g -o phone_loop phone_loop.c
 * $ ./phone_loop
 */

int main() {
	char phone_loop[11];
	int integer;
	scanf("%s%d", phone_loop, &integer);
	while (1) {
		if (integer == -1) {
			printf("%s\n", phone_loop);
			return 0;
		} else if (integer >= 0 && integer <= 9) {
			printf("%c\n", phone_loop[integer]);
			return 0;
		} else {
			printf("ERROR\n");
			return 1;
		}
	}
}