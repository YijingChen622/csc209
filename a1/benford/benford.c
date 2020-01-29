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
    	int num = 0;
    	if (argc == 3) {
    		FILE *file;
    		file = fopen(argv[2], "r");
    		if (file == NULL) {
    			return 1;
    		} 
    		while (fscanf(file, "%d", &num) == 1) {
    			add_to_tally(num, position, tally);
    		}
    		if (fclose(file) != 0) {
    			return 1;
    		}
    	} else {
    		while (scanf("%d", &num) == 1) {
    			add_to_tally(num, position, tally);
    		}
    	}
    	for (int i = 0; i < BASE; i++) {
    			printf("%ds: %d\n", i, tally[i]);
    		}
    	return 0;
    }
}
