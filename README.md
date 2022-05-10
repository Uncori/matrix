# s21_matrix  

Implementation of the matrix.h library.   

# Chapter I  

![matrix](images/matrixx.png)

### Matrix structure in C language:

```c
typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;
```

The matrix_type field defines the matrix type, CORRECT_MATRIX - the correct matrix, INCORRECT_MATRIX - in case of errors in actions with matrices, IDENTITY_MATRIX - a identity matrix, ZERO_MATRIX - a null matrix.
The filling of the matrix in the case of the INCORRECT_MATRIX type is not defined.

## Matrix operations

### Creating matrices (create_matrix)

```c
matrix_t s21_create_matrix(int rows, int columns);
```

The matrix_type field must be initialized with the ZERO_MATRIX value.

### Cleaning of matrices (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

### Matrix comparison (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

The matrices A, B are equal |A = B| if they have the same dimensions and the corresponding elements are identical, thus for all i and j: A(i,j) = B(i,j)

The comparison must be up to and including 7 decimal places.

### Adding (sum_matrix) and subtracting matrices (sub_matrix)

```c
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);

### Matrix multiplication by scalar (mult_number). Multiplication of two matrices (mult_matrix)

```c
matrix_t s21_mult_number(matrix_t *A, double number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);
```

### Matrix transpose (transpose)

```c
matrix_t s21_transpose(matrix_t *A);
```

The transpose of matrix A is in switching its rows with its columns with their numbers retained

### Minor of matrix and matrix of algebraic complements (calc_complements)
```c
matrix_t s21_calc_complements(matrix_t *A);
```

Minor M(i,j) is a (n-1)-order determinant obtained by deleting out the i-th row and the j-th column from the matrix A.

### Matrix determinant

```c
double s21_determinant(matrix_t *A);
```

The determinant is a number that is associated to each square matrix and calculated from the elements using special formulas. \
Tip: The determinant can only be calculated for a square matrix.

The determinant of a matrix equals the sum of the products of elements of the row (column) and the corresponding algebraic complements.

### Inverse of the matrix (inverse_matrix)

```c
matrix_t s21_inverse_matrix(matrix_t *A);
```

A matrix A to the power of -1 is called the inverse of a square matrix A if the product of these matrices equals the identity matrix.

If the determinant of the matrix is zero, then it does not have an inverse.

The formula to calculate the inverse of matrix is $`A^{-1}=\frac{1} {|A|} × A_*^T`$
