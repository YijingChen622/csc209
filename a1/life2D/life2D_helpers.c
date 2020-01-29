#include <stdio.h>
#include <stdlib.h>


void print_state(int *board, int num_rows, int num_cols) {
    for (int i = 0; i < num_rows * num_cols; i++) {
        printf("%d", board[i]);
        if (((i + 1) % num_cols) == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void update_state(int *board, int num_rows, int num_cols) {
    int copy_arr[num_cols * num_rows];
    for (int i = 0; i < num_cols * num_rows; i ++) {
    	copy_arr[i] = board[i];
    }
    for (int i = 1; i < num_rows - 1; i++) {
    	for (int j = 1; j < num_cols - 1; j++) {
    		int count = 0;
    		count = copy_arr[(i - 1) * num_cols + j - 1] + copy_arr[(i - 1) * num_cols + j] \
    		+ copy_arr[(i - 1) * num_cols + j + 1] + copy_arr[i * num_cols + j - 1] + \
    		copy_arr[i * num_cols + j + 1] + copy_arr[(i + 1) * num_cols + j - 1] + \
    		copy_arr[(i + 1) * num_cols + j] + copy_arr[(i + 1) * num_cols + j + 1];
    		if ((copy_arr[i * num_cols + j] == 1) && (count < 2 || count >3)) {
    			board[i * num_cols + j] = 0;
    		}
    		if ((copy_arr[i * num_cols + j] == 0) && (count == 2 || count == 3)) {
    			board[i * num_cols + j] = 1;
    		}
    	}
    }  
}

