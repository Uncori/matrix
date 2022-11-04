#include "matrix.h"

matrix_t create_matrix(int rows, int columns)
{
    matrix_t neo;
    if (rows > 0 && columns > 0) {
        neo.rows = rows;
        neo.columns = columns;
        neo.matrix = (double **)malloc(rows * sizeof(double *));
        for (int i = 0; i < rows; i++) {
            neo.matrix[i] = (double *)calloc(columns, sizeof(double));
        }
        neo.matrix_type = ZERO_MATRIX;
    } else {
        neo.rows = 0;
        neo.columns = 0;
        neo.matrix_type = INCORRECT_MATRIX;
    }

    return neo;
}
void remove_matrix(matrix_t *A)
{
    if (A->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        free(A->matrix);
        A->rows = 0;
        A->columns = 0;
        A->matrix_type = INCORRECT_MATRIX;
    }
}

int eq_matrix(matrix_t *A, matrix_t *B)
{
    int error = SUCCESS;
    if (eq_size(A, B) == 1 && A->matrix_type != INCORRECT_MATRIX &&
        B->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < A->rows && error != 0; ++i) {
            for (int j = 0; j < A->columns && error != 0; ++j) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= E) {
                    error = FAILURE;
                }
            }
        }
    } else {
        error = FAILURE;
    }
    return error;
}

matrix_t sum_matrix(matrix_t *A, matrix_t *B)
{
    matrix_t neo;
    if (eq_size(A, B) == 1 && A->matrix_type != INCORRECT_MATRIX &&
        B->matrix_type != INCORRECT_MATRIX) {
        neo = create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < A->columns; ++j) {
                neo.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
        if (identity_matrix(&neo) == 1) {
            neo.matrix_type = IDENTITY_MATRIX;
        } else if (zero_matrix(&neo) == 1) {
            neo.matrix_type = ZERO_MATRIX;
        } else {
            neo.matrix_type = CORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }

    return neo;
}

matrix_t sub_matrix(matrix_t *A, matrix_t *B)
{
    matrix_t neo;
    if (eq_size(A, B) == 1 && A->matrix_type != INCORRECT_MATRIX &&
        B->matrix_type != INCORRECT_MATRIX) {
        neo = create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < A->columns; ++j) {
                neo.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
        if (identity_matrix(&neo) == 1) {
            neo.matrix_type = IDENTITY_MATRIX;
        } else if (zero_matrix(&neo) == 1) {
            neo.matrix_type = ZERO_MATRIX;
        } else {
            neo.matrix_type = CORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }
    return neo;
}

matrix_t mult_number(matrix_t *A, double number)
{
    matrix_t neo;
    if (A->matrix_type != INCORRECT_MATRIX && number == number) {
        neo = create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; ++i) {
            for (int j = 0; j < A->columns; ++j) {
                neo.matrix[i][j] = number * A->matrix[i][j];
            }
        }
        if (identity_matrix(&neo) == 1) {
            neo.matrix_type = IDENTITY_MATRIX;
        } else if (number == 0) {
            neo.matrix_type = ZERO_MATRIX;
        } else {
            neo.matrix_type = CORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }
    return neo;
}

matrix_t mult_matrix(matrix_t *A, matrix_t *B)
{
    matrix_t neo;
    if (A->columns == B->rows && A->matrix_type != INCORRECT_MATRIX &&
        B->matrix_type != INCORRECT_MATRIX) {
        double sum = 0;
        neo = create_matrix(A->rows, B->columns);
        for (int i = 0; i < neo.rows; ++i) {
            for (int j = 0; j < neo.columns; ++j) {
                for (int k = 0; k < neo.rows; ++k) {
                    sum += A->matrix[i][k] * B->matrix[k][j];
                    neo.matrix[i][j] = sum;
                }
                sum = 0;
            }
        }
        if (identity_matrix(&neo) == 1) {
            neo.matrix_type = IDENTITY_MATRIX;
        } else if (zero_matrix(&neo) == 1) {
            neo.matrix_type = ZERO_MATRIX;
        } else {
            neo.matrix_type = CORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }

    return neo;
}

matrix_t transpose(matrix_t *A)
{
    matrix_t neo;
    if (A->matrix_type != INCORRECT_MATRIX) {
        neo = create_matrix(A->columns, A->rows);
        for (int i = 0; i < neo.rows; ++i) {
            for (int j = 0; j < neo.columns; ++j) {
                neo.matrix[i][j] = A->matrix[j][i];
            }
        }
        if (identity_matrix(&neo) == 1) {
            neo.matrix_type = IDENTITY_MATRIX;
        } else if (zero_matrix(&neo) == 1) {
            neo.matrix_type = ZERO_MATRIX;
        } else {
            neo.matrix_type = CORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }
    return neo;
}

matrix_t calc_complements(matrix_t *A)
{
    matrix_t neo;
    if (eq_sqr(A) == 1 && A->matrix_type != INCORRECT_MATRIX) {
        if (A->rows == 1 && A->columns == 1) {
            neo = create_matrix(1, 1);
            neo.matrix[0][0] = 1;
        } else {
            neo = create_matrix(A->rows, A->columns);
            matrix_t temp;
            for (int i = 0; i < neo.rows; ++i) {
                for (int j = 0; j < neo.columns; ++j) {
                    temp = lil_matrix(A, i, j);
                    neo.matrix[i][j] =
                        determinant(&temp) * pow(-1, (i + 1) + (j + 1));
                    remove_matrix(&temp);
                }
            }
        }
        if (identity_matrix(&neo) == 1) {
            neo.matrix_type = IDENTITY_MATRIX;
        } else if (zero_matrix(&neo) == 1) {
            neo.matrix_type = ZERO_MATRIX;
        } else {
            neo.matrix_type = CORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }
    return neo;
}

double determinant(matrix_t *A)
{
    double deter = 0;
    if (eq_sqr(A) == 1 && A->matrix_type != INCORRECT_MATRIX) {
        if (A->rows == 1 && A->columns == 1) {
            deter = A->matrix[0][0];
        } else if (A->rows == 2 && A->columns == 2) {
            deter = (A->matrix[0][0] * A->matrix[1][1]) -
                    (A->matrix[1][0] * A->matrix[0][1]);
        } else if (A->rows >= 3 && A->columns >= 3) {
            for (int i = 1; i <= A->columns; ++i) {
                matrix_t neo = lil_matrix(A, 0, i - 1);
                deter += pow(-1, 1 + (double)i) * A->matrix[0][i - 1] *
                         determinant(&neo);
                remove_matrix(&neo);
            }
        }
    } else {
        deter = NAN;
    }
    return deter;
}

matrix_t inverse_matrix(matrix_t *A)
{
    matrix_t neo;
    if (eq_sqr(A) == 1 && A->matrix_type != INCORRECT_MATRIX) {
        double det = determinant(A);
        if (det != 0) {
            neo = create_matrix(A->rows, A->columns);
            remove_matrix(&neo);
            matrix_t temp = calc_complements(A);
            matrix_t second_temp = transpose(&temp);
            neo = mult_number(&second_temp, 1 / det);
            remove_matrix(&temp);
            remove_matrix(&second_temp);
            if (identity_matrix(&neo) == 1) {
                neo.matrix_type = IDENTITY_MATRIX;
            } else if (zero_matrix(&neo) == 1) {
                neo.matrix_type = ZERO_MATRIX;
            } else {
                neo.matrix_type = CORRECT_MATRIX;
            }
        } else {
            neo = create_matrix(0, 0);
            neo.matrix_type = INCORRECT_MATRIX;
        }
    } else {
        neo = create_matrix(0, 0);
        neo.matrix_type = INCORRECT_MATRIX;
    }
    return neo;
}

int eq_size(matrix_t *A, matrix_t *B)
{
    int suck = FAILURE;
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
        suck = SUCCESS;
    }
    return suck;
}

int eq_sqr(matrix_t *A)
{
    int suck = FAILURE;
    if (A->rows == A->columns) {
        suck = SUCCESS;
    }
    return suck;
}

matrix_t lil_matrix(matrix_t *A, int ip, int jp)
{
    matrix_t neo = create_matrix(A->rows - 1, A->columns - 1);
    for (int i = 0; i < A->rows; ++i) {
        for (int j = 0; j < A->columns; ++j) {
            if (i != ip && j != jp) {
                if (i > ip && j < jp) {
                    neo.matrix[i - 1][j] = A->matrix[i][j];
                } else if (i > ip && j > jp) {
                    neo.matrix[i - 1][j - 1] = A->matrix[i][j];
                } else if (i < ip && j > jp) {
                    neo.matrix[i][j - 1] = A->matrix[i][j];
                } else {
                    neo.matrix[i][j] = A->matrix[i][j];
                }
            }
        }
    }
    return neo;
}

int identity_matrix(matrix_t *A)
{
    int error = FAILURE;
    if (A->rows == A->columns) {
        matrix_t neo = create_matrix(A->rows, A->columns);
        for (int i = 0, j = 0; i < neo.rows && j < neo.columns; ++j, ++i) {
            neo.matrix[i][j] = 1;
        }
        if (eq_matrix(A, &neo) == 1) {
            A->matrix_type = IDENTITY_MATRIX;
            error = SUCCESS;
        }
        remove_matrix(&neo);
    }
    return error;
}

int zero_matrix(matrix_t *A)
{
    int error = FAILURE;
    matrix_t neo = create_matrix(A->rows, A->columns);
    if (eq_matrix(A, &neo) == 1) {
        A->matrix_type = ZERO_MATRIX;
        error = SUCCESS;
    }
    remove_matrix(&neo);
    return error;
}
