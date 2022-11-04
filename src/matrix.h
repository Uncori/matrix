#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define FAILURE 0
#define E 1e-7

typedef enum {
    CORRECT_MATRIX = 0, // корректная матрица
    INCORRECT_MATRIX = 1, // при ошибках в действиях с матрицами
    IDENTITY_MATRIX = 2, // единичная матрица
    ZERO_MATRIX = 3      // нулевая матрица
} matrix_type_t;
// Заполнение матрицы в случае типа INCORRECT_MATRIX не определено.

typedef struct matrix_struct {
    double **matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

matrix_t create_matrix(int rows, int columns);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
matrix_t sum_matrix(matrix_t *A, matrix_t *B);
matrix_t sub_matrix(matrix_t *A, matrix_t *B);
matrix_t mult_number(matrix_t *A, double number);
matrix_t mult_matrix(matrix_t *A, matrix_t *B);
matrix_t transpose(matrix_t *A);
matrix_t calc_complements(matrix_t *A);
double determinant(matrix_t *A);
matrix_t inverse_matrix(matrix_t *A);

// help func
int eq_size(matrix_t *A, matrix_t *B);
int eq_sqr(matrix_t *A);
matrix_t lil_matrix(matrix_t *A, int ip, int jp);
int identity_matrix(matrix_t *A);
int zero_matrix(matrix_t *A);
#endif // SRC_MATRIX_H_
