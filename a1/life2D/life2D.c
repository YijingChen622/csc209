#include <stdio.h>
#include <stdlib.h>

#include "life2D_helpers.h"


int main(int argc, char **argv) {

    if (argc != 4) {
        fprintf(stderr, "Usage: life2D rows cols states\n");
        return 1;
    } else {
    	int height = (int)strtol(argv[1], NULL, 10);
    	int width = (int)strtol(argv[2], NULL, 10);
    	int states = (int)strtol(argv[3], NULL, 10);
    	int board[height * width];
    	int count = 0;
    	while(scanf("%d", &board[count]) != EOF) {
    		count++;
    	}
    	for (int i = 0; i < states; i++) {
    		print_state(board, height, width);
    		update_state(board, height, width);
    	}
    	return 0;
    }
}
