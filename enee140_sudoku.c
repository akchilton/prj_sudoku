/*
 * enee140_sudoku.c
 *
 *  Implementation of the Sudoku library.
 *
 */

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Check that the board is valid: each number between 1 and 9 must appear only
// once in each row, column and 3 x 3 box in the board. The board may include
// blank elements.
int
is_valid_board(int board[9][9])
{
    if(!is_valid_num(board)){
        return 0;
    }
    if(!is_valid_row(board)){
        return 0;
    }
    if(!is_valid_col(board)){
        return 0;
    }
    if(!is_valid_box(board)){
        return 0;
    }

    return 1;
}

int is_valid_num(int board[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] < 0 || board[i][j] > 9){
                return 0;
            }
        }
    }
    return 1;
}

int is_valid_row(int board[9][9]){
    for(int i = 0; i < 9; i++){
        int used[9] = {0}; //used array checks for the number of times a number appears, if it shows up it sets the value of index to 1
        for(int j = 0; j < 9; j++){
            int n = board[i][j];
            if (n != 0){
                if(used[n - 1] == 1){
                    return 0;
                }
                used[n - 1] = 1;
            }
        }
    }
    return 1;
}

int is_valid_col(int board[9][9]){
    for(int j = 0; j < 9; j++){
        int used[9] = {0};
        for(int i = 0; i < 9; i++){
            int n = board[i][j];
            if (n != 0){
                if(used[n - 1] == 1){
                    return 0;
                }
                used[n - 1] = 1;
            }
        }
    }
    return 1;
}

int is_valid_box(int box[9][9]){
    int count[9] = {0}; //counts number of boxes checked

    for(int i = 0; i < 9; i += 3){
        for(int j = 0; j < 9; j += 3){
            int used[10] = {0};
            for(int r = i; r < i + 3; r++){
                for(int c = j; c < j + 3; c++){
                    int n = box[r][c];
                    if(n != 0 && used[n] == 1){  //checks if n has already appeared beforehand
                        return 0;
                    }
                    used[n] = 1;
                }
            }
            count[i + j / 3] += 1; //determines which box the cell belongs to, then increments the counter for the box by 1
        }
    }

    for(int i = 0; i < 9; i++){
        if(count[i] != 1){
            return 0;
        }
    }

    return 1;
}

void new_sudoku_board(int board[9][9], int blanks){
    int canonical_board[9][9] = {
            {1, 4, 7, 2, 5, 8, 3, 6, 9},
            {2, 5, 8, 3, 6, 9, 4, 7, 1},
            {3, 6, 9, 4, 7, 1, 5, 8, 2},
            {4, 7, 1, 5, 8, 2, 6, 9, 3},
            {5, 8, 2, 6, 9, 3, 7, 1, 4},
            {6, 9, 3, 7, 1, 4, 8, 2, 5},
            {7, 1, 4, 8, 2, 5, 9, 3, 6},
            {8, 2, 5, 9, 3, 6, 1, 4, 7},
            {9, 3, 6, 1, 4, 7, 2, 5, 8}
    };

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            board[i][j] = canonical_board[i][j];
        }
    }

    srand(time(NULL));
    int n_blanks = 0;
    while (n_blanks < blanks){
        int r = rand() % 9;
        int c = rand() % 9;
        if(board[r][c] != 0){
            board[r][c]= 0;
            n_blanks++;
        }
    }

}

void generate_permutation(int p[], int n){
    for(int i = 0; i < n; i++){
        p[i] = i + 1;
    }

    //Shuffles numbers randomly
    for(int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
    }
}

void transform_permute_rows(int board[9][9]){
    int p1[3], p2[3], p3[3];
    int band1[3][9], band2[3][9], band3[3][9];

    generate_permutation(p1, 3);
    generate_permutation(p2, 3);
    generate_permutation(p3, 3);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 9; j++){
            band1[i][j] = board[i][j];
            band2[i][j] = board[i + 3][j];
            band3[i][j] = board[i + 6][j];
        }
    }

    for(int i = 0; i < 3; i++){
        int r1 = p1[i] - 1;
        int r2 = p2[i] - 1;
        int r3 = p3[i] - 1;

        for(int j = 0; j < 9; j++){
            board[i][j] = band1[r1][j];
            board[i + 3][j] = band2[r2][j];
            board[i + 6][j] = band3[r3][j];
        }
    }
}

void transform_permute_bands(int board[9][9]){
    int p[3];
    int temp[9][9];
    generate_permutation(p, 3);
    //printf("\n");
    //moves values in board based on og order from temp
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            temp[i][j] = board[i][j];
        }
    }

    for(int k = 0; k < 3; k++){
        int step = (k + 1 - p[k]) * 3; //Gives us how many columns I need to move said column
        for(int j = 0; j < 9; j++){
            for(int i = (p[k] - 1) * 3; i < (p[k] * 3); i++) {
                board[i + step][j] = temp[i][j];
            }
        }
    }
}

void transform_permute_columns(int board [9][9]){
    int p1[3], p2[3], p3[3];
    int stack1[9][3], stack2[9][3], stack3[9][3];

    generate_permutation(p1, 3);
    generate_permutation(p2, 3);
    generate_permutation(p3, 3);

    for(int j = 0; j < 3; j++){
        for(int i = 0; i < 9; i++){
            stack1[i][j] = board[i][j];
            stack2[i][j] = board[i][j + 3];
            stack3[i][j] = board[i][j + 6];
        }
    }

    for(int j = 0; j < 3; j++){
        int c1 = p1[j] - 1;
        int c2 = p2[j] - 1;
        int c3 = p3[j] - 1;

        for(int i = 0; i < 9; i++){
            board[i][j] = stack1[i][c1];
            board[i][j + 3] = stack2[i][c2];
            board[i][j + 6] = stack3[i][c3];
        }
    }
}

void transform_permute_stacks(int board[9][9]){
    int p[3];
    int temp[9][9];
    generate_permutation(p, 3);
    //printf("\n");
    //moves values in board based on og order from temp
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            temp[i][j] = board[i][j];
        }
    }

    for(int k = 0; k < 3; k++){
        int step = (k + 1 - p[k]) * 3; //Gives us how many columns I need to move said column
        for(int i = 0; i < 9; i++){
            for(int j = (p[k] - 1) * 3; j < (p[k] * 3); j++) {
                board[i][j + step] = temp[i][j];
            }
        }
    }
}

void transform_flip_main_diagonal(int board[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = i + 1; j < 9; j++){
            int temp = board[i][j];
            board[i][j] = board[j][i];
            board[j][i] = temp;
        }
    }
}

void transform_flip_minor_diagonal(int board[9][9]){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < (9 - i); j++){
            int temp = board[i][j];
            board[i][j] = board[8 - j][8 - i]; //flips top right half values with bottom left half values
            board[8 - j][8 - i] = temp;
        }
    }
}

int print_sudoku_board(int board[9][9]){
    //checks to see if any values on board are invalid
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] < 0 || board[i][j] > 9){
                return -1;
            }
        }
    }

    printf("+-------+-------+-------+\n");
    for(int i = 0; i < 9; i++){
        printf("| ");  //first | in each row

        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                printf("- ");
            } else{
                printf("%d ", board[i][j]);
            }

            if(j % 3 == 2){  //vertical separation of each 3x3 box
                printf("| ");
            }
        }

        printf("\n");
        if(i % 3 == 2){
            printf("+-------+-------+-------+\n");
        }
    }
    return 0;
}

int read_sudoku_board(const char file_name[], int board[9][9]){
    FILE *file = fopen(file_name, "r");
    if(!file){
        return -1; //file I/O error
    }

    char line[11];
    for(int i = 0; i < 9; i++){
        if(!fgets(line, sizeof(line), file)){ //file too short
            fclose(file);
            return -3;
        }
        if(line[9] != '\n' && line[9] != '\0'){ //file too long
            return -3;
        }
        //printf("line %d: %s\n", i, line);
        for(int j = 0; j < 9; j++){
            char c = line[j];
            if(c == '-'){
                board[i][j] = 0;
            }
            else if( c >= '1' && c <= '9'){
                board[i][j] = c - '0';
            }
            else{
                fclose(file);
                return -2;
            }
        }
    }

    fclose(file);
    return 0;
}

int write_sudoku_board(const char file_name[], int board[9][9]){
    char c;

    FILE *file = fopen(file_name, "w");
    if(!file){
        return -1; //I/O error
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            int n = board[i][j];
            if(n == 0){
                c = '-';
                fprintf(file, "%c", c);
            }
            else{
                c = n + '0';
                fprintf(file, "%c", c);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}



