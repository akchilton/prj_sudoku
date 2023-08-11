/*
 * enee140_gen_sudoku.c
 *
 *  Generate Sudoku boards.
 *
 */

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*easy -> 31-45
 * medium -> 46-51
 * hard -> 52-61 */

//filename options difficulty

int
main(int argc, char *argv[])
{
    srand(time(NULL));
    int board[9][9];
    char *file = argv[1];
    char *difficulty = NULL;


    if(argc >= 4){
        difficulty = argv[3];
    }

    int option = atoi(argv[2]);
    int first9bits = option & 0x1FF;
    int bitval[9];

    for(int i = 0; i < 9; i++){
        bitval[i] = (first9bits >> i) & 1;
    }

    int blanks = 0;

    if(strcmp(difficulty, "easy") == 0){
        blanks = rand() % 15 + 31;
    }else if(strcmp(difficulty, "medium") == 0){
        blanks = rand() % 6 + 46;
    }else if(strcmp(difficulty, "hard") == 0){
        blanks = rand() % 10 + 52;
    }



    if(bitval[0] == 0){
        new_sudoku_board(board, blanks);
    }else{
        int r = read_sudoku_board(file, board);

        if(r == -1){
            printf("File I/O Error");
            exit(0);
        }else if(r == -2){
            printf("Error: Invalid character detected");
            exit(0);
        }else if(r == -3){
            printf("Error: Invalid file format");
            exit(0);
        }
        if(!is_valid_board(board)){
            printf("Error: Invalid sudoku board.");
            exit(0);
        }
    }

    if(bitval[1] == 1){
        transform_permute_rows(board);
    }

    if(bitval[2] == 1){
        transform_permute_bands(board);
    }

    if(bitval[3] == 1){
        transform_permute_columns(board);
    }

    if(bitval[4] == 1){
        transform_permute_stacks(board);
    }

    if(bitval[5] == 1){
        transform_flip_main_diagonal(board);
    }

    if(bitval[6] == 1){
        transform_flip_minor_diagonal(board);
    }

    if(bitval[7] == 1){
        print_sudoku_board(board);
    }

    if(bitval[8] == 1){
        write_sudoku_board(file, board);
    }

    /* Used for testing functions
    new_sudoku_board(board ,9);
    int v = is_valid_box(board);
    printf("%d ", v);
    print_sudoku_board(board);
    transform_permute_stacks(board);
    transform_permute_bands(board);
    print_sudoku_board(board);
     */



    return 0;
}
