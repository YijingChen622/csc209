#include <stdio.h>

#include "benford_helpers.h"

int count_digits(int num) {
	int result = 0;
	int remain = num;
    while (remain != 0) {
    	remain = remain / BASE;
    	result++;
    }
    return result;
}

int get_ith_from_right(int num, int i) {
	int index = 0;
	int remain = num;
	while (index < i) {
		remain = remain / BASE;
		index++;
	}
	return remain % BASE;
}

int get_ith_from_left(int num, int i) {
    return get_ith_from_right(num, count_digits(num) - i - 1);
}

void add_to_tally(int num, int i, int *tally) {
    int digit = get_ith_from_left(num, i);
	tally[digit] = tally[digit] + 1;
}
