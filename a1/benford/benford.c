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
    	int position = (int)strtol(argv[1], NULL, 10);
    	int tally[BASE] = {0};
    	int j = 0;
    	if (argc == 3) {
    		FILE *file;
    		file = fopen(argv[2], "r");
    		// int position = (int)strtol(argv[1], NULL, 10);
    		if (file == NULL) {
    			return 1;
    		} 
    		// int tally[BASE] = {0};
    		// int j = 0;
    		while (fscanf(file, "%d", &j) == 1) {
    			add_to_tally(j, position, tally);
    		}
    		if (fclose(file) != 0) {
    			return 1;
    		}
    		// for (int i = 0; i < BASE; i++) {
    		// 	printf("%ds: %d\n", i, tally[i]);
    		// }
    	} else {
    		// int tally[BASE] = {0};
    		// int position = (int)strtol(argv[1], NULL, 10);
    		// int j = 0;
    		while (scanf("%d", &j) == 1) {
    			add_to_tally(j, position, tally);
    		}
    		// for (int i = 0; i < BASE; i++) {
    		// 	printf("%ds: %d\n", i, tally[i]);
    		// }
    	}
    	for (int i = 0; i < BASE; i++) {
    			printf("%ds: %d\n", i, tally[i]);
    		}
    	return 0;
    }
}
