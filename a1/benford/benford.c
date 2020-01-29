#include <stdio.h>
#include <stdlib.h>

#include "benford_helpers.h"

/*
 * The only print statement that you may use in your main function is the following:
 * - printf("%ds: %d\n")
 *
 */
int main(int argc, char **argv) {

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "benford position [datafile]\n");
        return 1;
    } else {
    	if (argc == 3) {
    		FILE *file;
    		file = fopen(argv[2], "r");
    		int position = (int)strtol(argv[1], NULL, 10);
    		if (file == NULL) {
    			return 1;
    		} 
    		int tally[BASE];
    		for (int i = 0; i < BASE; i++) {
    			tally[i] = 0;
    		}
    		int j = 0;
    		while (fscanf(file, "%d", &j) != EOF) {
    			add_to_tally(j, position, tally);
    		}
    		for (int i = 0; i < BASE; i++) {
    			printf("%ds: %d\n", i, tally[i]);
    		}
    	} else {
    		int tally[BASE];
    		int position = (int)strtol(argv[1], NULL, 10);
    		for (int i = 0; i < BASE; i++) {
    			tally[i] = 0;
    		}
    		int j = 0;
    		while (scanf("%d", &j) != EOF) {
    			add_to_tally(j, position, tally);
    		}
    		for (int i = 0; i < BASE; i++) {
    			printf("%ds: %d\n", i, tally[i]);
    		}
    	}
    }
    return 0;
}
