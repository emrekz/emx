#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdbool.h>

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
EMX *EMX_Mul_Pair(EMX *mtx1, EMX *mtx2);  // Multiply two matrix and return pointer of new matrix
EMX *EMX_Mul(int n, ...);  // Multiply two or more number of matrix
EMX *EMX_Transpose(EMX *mtx);  // Give transpose of a matrix
bool EMX_CheckSquareMatrix(EMX *mtx);
EMX *EMX_GetMinorElement(EMX *mtx, int indexR, int indexC);  // Get minor of selected element
emx_t EMX_Determinant(EMX *mtx);  // Get determinant of a matrix
void _EMX_DeterminantHelper(EMX *mtx, emx_t *min, emx_t *det);  // Helper function for determinant
EMX *EMX_CofactorMatrix(EMX *mtx);  // Get cofactor of a matrix
emx_t EMX_CofactorElement(EMX *mtx, int indexR, int indexC);  // Get a cofactor of a selected element
EMX *EMX_AdjointMatrix(EMX *mtx);  // Get adjoint matrix
EMX *EMX_GenerateConstantMatrix(int indexR, int indexC, emx_t val);  // Generete constant(homogeneous) matrix
EMX *EMX_ScalerMul(EMX *mtx, emx_t val);  // Get scaler multiplication of matrix
EMX *EMX_Inverse(EMX *mtx);  // Get inverse of matrix

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
  if(arr) {
    for(int i = 0; i < mtx->size; i++) {
      mtx->addr[i] = ((emx_t *)arr)[i];
    }
  } else {
    for(int i = 0; i < mtx->size; i++) {
      mtx->addr[i] = 0;
    }
  }
}

void EMX_Print(EMX *mtx) {
  if(mtx) {
    for(int r = 0; r < mtx->row; r++) {
      for(int c = 0; c < mtx->column; c++) {
        printf(EMX_PRINT_SPEC, mtx->addr[c + r * mtx->column]);
        for(char i = 0; i < TAB_SIZE; i++) {
          printf("\t");
        }
      }
      printf("\n");
    }
    printf("\n");
  } else {
    printf("COULD NOT PRINT !\n");
  }
}

/* -----------------------------------------------------------------
                          OPERATIONS                              */

                          /// @param mtx1 address of first matrix
                          /// @param mtx2 address of second matrix
EMX *EMX_Add_Pair(EMX *mtx1, EMX *mtx2) {
  if(mtx1->row == mtx2->row && mtx1->column == mtx2->column) {
    EMX *mtx3 = EMX_Generate(mtx1->row, mtx1->column, NULL);
    for(int r = 0; r < mtx1->row; r++) {
      for(int c = 0; c < mtx1->column; c++) {
        EMX_SetValue(mtx3, r, c, (
          mtx1->addr[c + r * mtx1->column] + mtx2->addr[c + r * mtx2->column]
          ));
      }
    }
    return mtx3;
  } else {
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
  for(int i = 0; i < n - 1; i++) {
    tmp = va_arg(ptr, EMX *);
    if((total = EMX_Add_Pair(total, tmp))) {} else { return NULL; }
  }
  return total;
}


/// @param mtx1 address of first matrix
/// @param mtx2 address of second matrix
EMX *EMX_Sub_Pair(EMX *mtx1, EMX *mtx2) {
  if(mtx1->row == mtx2->row && mtx1->column == mtx2->column) {
    EMX *mtx3 = EMX_Generate(mtx1->row, mtx1->column, NULL);
    for(int r = 0; r < mtx1->row; r++) {
      for(int c = 0; c < mtx1->column; c++) {
        EMX_SetValue(mtx3, r, c, (
          mtx1->addr[c + r * mtx1->column] - mtx2->addr[c + r * mtx2->column]
          ));
      }
    }
    return mtx3;
  } else {
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
  for(int i = 0; i < n - 1; i++) {
    tmp = va_arg(ptr, EMX *);
    if((total = EMX_Sub_Pair(total, tmp))) {} else { return NULL; }
  }
  return total;
}

/// @param mtx1 address of first matrix
/// @param mtx2 address of second matrix
EMX *EMX_Mul_Pair(EMX *mtx1, EMX *mtx2) {
  if(mtx1->column == mtx2->row) {
    EMX *mtx3 = EMX_Generate(mtx1->row, mtx2->column, NULL);
    for(int r1 = 0; r1 < mtx1->row; r1++) {
      for(int c2 = 0; c2 < mtx2->column; c2++) {
        mtx3->addr[c2 + r1 * mtx2->column] = (emx_t)0;
        for(int c1 = 0; c1 < mtx1->column; c1++) {
          mtx3->addr[c2 + r1 * mtx2->column] += mtx1->addr[c1 + r1 * mtx1->column] * mtx2->addr[c2 + c1 * mtx2->column];
        }
      }
    }
    return mtx3;
  } else {
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
  for(int i = 0; i < n - 1; i++) {
    tmp = va_arg(mtx, EMX *);
    if((total = EMX_Mul_Pair(total, tmp))) {} else { return NULL; }
  }
  va_end(mtx);
  return total;
}

EMX *EMX_Transpose(EMX *mtx) {
  EMX *T = NULL;
  if(mtx) {
    T = EMX_Generate(mtx->column, mtx->row, NULL);
    T->row = mtx->row;
    T->column = mtx->column;
    T->size = T->row * T->column;
    for(int r = 0; r < mtx->row; r++) {
      for(int c = 0; c < mtx->column; c++) {
        T->addr[r + c * T->column] = mtx->addr[c + r * mtx->column];
      }
    }
  } else {
    printf("ERROR: Transpose of NULL Matrix !\n");
  }
  
  return T;
}

bool EMX_CheckSquareMatrix(EMX *mtx) {
  if(mtx->column == mtx->row) {
    return true;
  } else {
    return false;
  }
}

/// @param mtx address of matrix 
/// @param indexR row index of element
/// @param indexC column index of element
EMX *EMX_GetMinorElement(EMX *mtx, int indexR, int indexC) {
  EMX *M = EMX_Generate(mtx->row - 1, mtx->column - 1, NULL);
  int t = 0;
  for(int r = 0; r < mtx->row; r++) {
    if(r == indexR) continue;
    for(int c = 0; c < mtx->column; c++) {
      if(c == indexC) continue;
      M->addr[t] = mtx->addr[c + r * mtx->column];
      t++;
    }
  }
  return M;
}

emx_t EMX_Determinant(EMX *mtx) {
  emx_t _det = 0;
  emx_t _min = 1;
  emx_t *det = &_det;
  emx_t *min = &_min;
  _EMX_DeterminantHelper(mtx, min, det);
  return *det;
}

void _EMX_DeterminantHelper(EMX *mtx, emx_t *min, emx_t *det) {
  emx_t mtmp = 0;
  EMX *M;
  if(mtx->row == 2 && mtx->column == 2) {
    *det = (mtx->addr[0] * mtx->addr[3] - mtx->addr[1] * mtx->addr[2]);
  } else if(mtx->row == 1 && mtx->column == 1) {
    *det = mtx->addr[0];
  } else {
    for(int c = 0; c < mtx->column; c++) {
      M = EMX_GetMinorElement(mtx, 0, c);
      if(c % 2 == 1) *min *= -1;
      *min *= mtx->addr[c];
      if(M->row == 2 && M->column == 2) {
        mtmp = (M->addr[0] * M->addr[3] - M->addr[1] * M->addr[2]);
        *min *= mtmp;
        *det += *min;
        *min /= mtmp;
        *min /= mtx->addr[c];
        if(c % 2 == 1) *min *= -1;
      } else {
        _EMX_DeterminantHelper(M, min, det);
        EMX_Free(M);
        if(c % 2 == 1) *min *= -1;
        *min /= mtx->addr[c];
      }
    }
  }
}

EMX *EMX_CofactorMatrix(EMX *mtx) {
  EMX *tmp = NULL;
  if(EMX_CheckSquareMatrix(mtx)) {
    tmp = EMX_Generate(mtx->row, mtx->column, NULL);
    EMX *M;
    emx_t det;
    for(int r = 0; r < mtx->row; r++) {
      for(int c = 0; c < mtx->column; c++) {
        det = EMX_CofactorElement(mtx, r, c);
        EMX_SetValue(tmp, r, c, det);
      }
    }
  } else {
    printf("ERROR: MATRIX MUST BE SQUARE MATRIX !\n");
  }
  return tmp;
}

emx_t EMX_CofactorElement(EMX *mtx, int indexR, int indexC) {
  EMX *M;
  emx_t det;
  M = EMX_GetMinorElement(mtx, indexR, indexC);
  det = EMX_Determinant(M);
  EMX_Free(M);
  if((indexR + indexC) % 2 == 1) det *= -1;
  return det;
}

EMX *EMX_AdjointMatrix(EMX *mtx) {
  return EMX_Transpose(EMX_CofactorMatrix(mtx));
}

/// @param indexR row count of matrix
/// @param indexC column count of matrix
/// @param val value for fill in matrix
/// @return 
EMX *EMX_GenerateConstantMatrix(int indexR, int indexC, emx_t val) {
  EMX *mtx = (EMX *)malloc(sizeof(EMX));
  mtx->row = indexR;
  mtx->column = indexC;
  mtx->size = mtx->row * mtx->column;
  mtx->addr = _EMX_GetVector(mtx->size);
  for(int r = 0; r < indexR; r++) {
    for(int c = 0; c < indexC; c++) {
      EMX_SetValue(mtx, r, c, val);      
    }
  }
  return mtx;
}

/// @param mtx address of matrix
/// @param val scaler value
EMX *EMX_ScalerMul(EMX *mtx, emx_t val) {
  EMX *sca = EMX_Generate(mtx->row, mtx->column, NULL);
  for(int r = 0; r < mtx->row; r++) {
    for(int c = 0; c < mtx->column; c++) {
      sca->addr[c + r * sca->column] = mtx->addr[c + r * mtx->column] * val;  
    }
  }
  return sca;
}

EMX *EMX_Inverse(EMX *mtx) {
  EMX *adj = EMX_AdjointMatrix(mtx);
  emx_t det = EMX_Determinant(mtx);
  det = 1 / det;
  EMX *inv = EMX_ScalerMul(adj, det);
  EMX_Free(adj);
  return inv;
}

void EMX_Free(EMX *mtx) {
  if(mtx) {
    free(mtx->addr);
    free(mtx);
  }
}

#endif