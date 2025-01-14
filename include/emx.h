#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>

#define TAB_SIZE  2

#ifndef EMX_USE_DOUBLE_DATA
typedef int emx_t;
#define EMX_PRINT_SPEC "%d"
#else 
typedef double emx_t;
#define EMX_PRINT_SPEC "%f"
#endif

typedef struct {
  int row;
  int column;
  int size;
  emx_t *addr;
} EMX;

emx_t *_EMX_GetVector(int size);
EMX *EMX_Generate(int r, int c, void *arr);  // Generate a matrix
void EMX_Free(EMX *mtx);  // Free a matrix which generated EMX_Generate(...)
void EMX_SetValue(EMX *mtx, int indexR, int indexC, emx_t val);  // Set a value at specific position
emx_t EMX_GetValue(EMX *mtx, int indexR, int indexC);  // Give a value at specific position
void EMX_Fill(EMX *mtx, void *arr);  // Fill into matrix from array
void EMX_Print(EMX *mtx);  // Print a matrix (You can change TAB_SIZE macro for proper display) 

EMX *EMX_Add_Pair(EMX *mtx1, EMX *mtx2);  // Add two matrix and return pointer of new matrix
EMX *EMX_Add(int n, ...);  // Add two or more number of matrix
EMX *EMX_Sub_Pair(EMX *mtx1, EMX *mtx2);  // Subtract two matrix and return pointer of new matrix
EMX *EMX_Sub(int n, ...);  // Subtract two or more number of matrix
EMX *EMX_Mul_Pair(EMX *mtx1, EMX *mtx2);  // Multiple two matrix and return pointer of new matrix
EMX *EMX_Mul(int n, ...);  // Multiple two or more number of matrix
EMX *EMX_Transpose(EMX *mtx);  // Give transpose of a matrix

emx_t *_EMX_GetVector(int size) {
  return (emx_t *)malloc(size * sizeof(emx_t));
}

/// @param r row size
/// @param c column size
/// @param arr array address
EMX *EMX_Generate(int r, int c, void *arr) {
  EMX *mtx = (EMX *)malloc(sizeof(EMX));
  mtx->row = r;
  mtx->column = c;
  mtx->size = r * c;
  mtx->addr = _EMX_GetVector(mtx->size);
  EMX_Fill(mtx, arr);
  return mtx;
}

/// @param mtx address of matrix
/// @param indexR index of row
/// @param indexC index of column
/// @param val value for set
void EMX_SetValue(EMX *mtx, int indexR, int indexC, emx_t val) {
  mtx->addr[indexC + indexR * mtx->column] = val;
}

/// @param mtx address of matrix
/// @param indexR index of row
/// @param indexC index of column
emx_t EMX_GetValue(EMX *mtx, int indexR, int indexC) {
  return mtx->addr[indexC + indexR * mtx->column];
}


/// @param mtx address of matrix
/// @param arr address of data
void EMX_Fill(EMX *mtx, void *arr) {
  if (arr) {
    for (int i = 0; i < mtx->size; i++) {
      mtx->addr[i] = ((emx_t *)arr)[i];
    }
  }
  else {
    for (int i = 0; i < mtx->size; i++) {
      mtx->addr[i] = 0;
    }
  }
}

void EMX_Print(EMX *mtx) {
  if (mtx) {
    for (int r = 0; r < mtx->row; r++) {
      for (int c = 0; c < mtx->column; c++) {
        printf(EMX_PRINT_SPEC, mtx->addr[c + r * mtx->column]);
        for (char i = 0; i < TAB_SIZE; i++) {
          printf("\t");
        }
      }
      printf("\n");
    }
    printf("\n");
  }
  else {
    printf("COULD NOT PRINT !\n");
  }
}

/* -----------------------------------------------------------------
                          OPERATIONS                              */

/// @param mtx1 address of first matrix
/// @param mtx2 address of second matrix
EMX *EMX_Add_Pair(EMX *mtx1, EMX *mtx2) {
  if (mtx1->row == mtx2->row && mtx1->column == mtx2->column) {
    EMX *mtx3 = EMX_Generate(mtx1->row, mtx1->column, NULL);
    for (int r = 0; r < mtx1->row; r++) {
      for (int c = 0; c < mtx1->column; c++) {
        EMX_SetValue(mtx3, r, c, (
          mtx1->addr[c + r * mtx1->column] + mtx2->addr[c + r * mtx2->column]
          ));
      }
    }
    return mtx3;
  }
  else {
    printf("ERROR: WRONG DIMENSION WHILE ADDITION !\n");
    return NULL;
  }
}

/// @param n number of matrix
/// @param ... address of matrices
EMX *EMX_Add(int n, ...) {
  EMX *tmp;
  va_list ptr;
  va_start(ptr, n);
  EMX *total = va_arg(ptr, EMX *);
  for (int i = 0; i < n - 1; i++) {
    tmp = va_arg(ptr, EMX *);
    if ((total = EMX_Add_Pair(total, tmp))) {}
    else { return NULL; }
  }
  return total;
}


/// @param mtx1 address of first matrix
/// @param mtx2 address of second matrix
EMX *EMX_Sub_Pair(EMX *mtx1, EMX *mtx2) {
  if (mtx1->row == mtx2->row && mtx1->column == mtx2->column) {
    EMX *mtx3 = EMX_Generate(mtx1->row, mtx1->column, NULL);
    for (int r = 0; r < mtx1->row; r++) {
      for (int c = 0; c < mtx1->column; c++) {
        EMX_SetValue(mtx3, r, c, (
          mtx1->addr[c + r * mtx1->column] - mtx2->addr[c + r * mtx2->column]
          ));
      }
    }
    return mtx3;
  }
  else {
    printf("ERROR: WRONG DIMENSION WHILE SUBTRACTION !\n");
    return NULL;
  }
}

/// @param n number of matrix
/// @param ... address of matrices
EMX *EMX_Sub(int n, ...) {
  EMX *tmp;
  va_list ptr;
  va_start(ptr, n);
  EMX *total = va_arg(ptr, EMX *);
  for (int i = 0; i < n - 1; i++) {
    tmp = va_arg(ptr, EMX *);
    if ((total = EMX_Sub_Pair(total, tmp))) {}
    else { return NULL; }
  }
  return total;
}

/// @param mtx1 address of first matrix
/// @param mtx2 address of second matrix
EMX *EMX_Mul_Pair(EMX *mtx1, EMX *mtx2) {
  if (mtx1->column == mtx2->row) {
    EMX *mtx3 = EMX_Generate(mtx1->row, mtx2->column, NULL);
    for (int r1 = 0; r1 < mtx1->row; r1++) {
      for (int c2 = 0; c2 < mtx2->column; c2++) {
        mtx3->addr[c2 + r1 * mtx2->column] = (emx_t)0;
        for (int c1 = 0; c1 < mtx1->column; c1++) {
          mtx3->addr[c2 + r1 * mtx2->column] += mtx1->addr[c1 + r1 * mtx1->column] * mtx2->addr[c2 + c1 * mtx2->column];
        }
      }
    }
    return mtx3;
  }
  else {
    printf("ERROR: WRONG DIMENSION WHILE MULTIPLICATION !\n");
    return NULL;
  }
}

/// @param n number of matrix
/// @param ... address of matrices
EMX *EMX_Mul(int n, ...) {
  EMX *tmp;
  va_list mtx;
  va_start(mtx, n);
  EMX *total = va_arg(mtx, EMX *);
  for (int i = 0; i < n - 1; i++) {
    tmp = va_arg(mtx, EMX *);
    if ((total = EMX_Mul_Pair(total, tmp))) {}
    else { return NULL; }
  }
  va_end(mtx);
  return total;
}

EMX *EMX_Transpose(EMX *mtx) {
  EMX *T = EMX_Generate(mtx->column, mtx->row, NULL);
  for (int r = 0; r < mtx->row; r++) {
    for (int c = 0; c < mtx->column; c++) {
      T->addr[r + c * T->column] = mtx->addr[c + r * mtx->column];
    }
  }
  return T;
}

void EMX_Free(EMX *mtx) {
  if (mtx) {
    free(mtx->addr);
    free(mtx);
  }
}

#endif