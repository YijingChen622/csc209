#include <stdio.h>
#include <stdlib.h>

/*
 * $ gcc -Wall -std=gnu99 -g -o phone phone.c
 * $ ./phone
 */

int main() {
	char phone[11];
	int integer;
	scanf("%s%d\n", phone, &integer);
	if (integer == -1) {
		printf("%s", phone);
		return 0;
	} else if (integer >= 0 & integer <= 9) {
		printf("%c", phone[integer]);
		return 0;
	} else {
		printf("ERROR");
		return 1;
	}
}