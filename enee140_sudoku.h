/*
 * enee14_sudoku.h
 *
 *  Function prototypes for the Sudoku library.
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

int is_valid_board(int board[9][9]);
int is_valid_num(int box[9][9]);
int is_valid_row(int box[9][9]);
int is_valid_col(int box[9][9]);
int is_valid_box(int box[9][9]);
void new_sudoku_board(int board[9][9], int blanks);
void transform_permute_rows(int board[9][9]);
void generate_permutation(int p[], int n);
void transform_permute_bands(int board[9][9]);
void transform_permute_columns(int board[9][9]);
void transform_permute_stacks(int board[9][9]);
void transform_flip_main_diagonal(int board[9][9]);
void transform_flip_minor_diagonal(int board[9][9]);
int print_sudoku_board(int board[9][9]);
int read_sudoku_board(const char file_name[], int board[9][9]);
int write_sudoku_board(const char file_name[], int board[9][9]);

#endif /* SUDOKU_H_ */
