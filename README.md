# emx - C Library for Basic Matrix Operation
It is a small header-only C library which can perform basic operations for matrix
## Functions
*Definitions for function parameters are in doxgyen comments*
```c
EMX *EMX_Generate(int r, int c, void *arr);  // Generate a matrix
void EMX_Free(EMX *mtx);  // Free a matrix which generated in EMX_Generate(...)
void EMX_SetValue(EMX *mtx, int posr, int posc, emx_t val);  // Set a value at specific position
emx_t EMX_GetValue(EMX *mtx, int posr, int posc);  // Give a value at specific position
void EMX_Fill(EMX *mtx, void *arr);  // Fill into matrix from array
void EMX_Print(EMX *mtx);  // Print a matrix (You can change TAB_SIZE macro for proper display) 

EMX *EMX_Add_Pair(EMX *mtx1, EMX *mtx2);  // Add two matrix and return pointer of new matrix
EMX *EMX_Add(int n, ...);  // Add two or more number of matrix
EMX *EMX_Sub_Pair(EMX *mtx1, EMX *mtx2);  // Subtract two matrix and return pointer of new matrix
EMX *EMX_Sub(int n, ...);  // Subtract two or more number of matrix
EMX *EMX_Mul_Pair(EMX *mtx1, EMX *mtx2);  // Multiple two matrix and return pointer of new matrix
EMX *EMX_Mul(int n, ...);  // Multiple two or more number of matrix
EMX *EMX_Transpose(EMX *mtx);  // Give transpose of a matrix
```
## Usage
Default data type for members of matrix is `int` type. If you want to use `double` type then use `#define EMX_USE_DOUBLE_DATA` before `#include "emx.h"`
```c
// #define EMX_USE_DOUBLE_DATA
#include "emx.h"

emx_t dataA[2][2] = {
  { 2,  2 },
  { 1,  3 }
};
emx_t dataB[2][2] = {
  { 3,  1 },
  { 4,  0 }
};
emx_t dataC[2][4] = {
  { 1,  2,  1,  3 },
  { 2,  3,  1,  7 }
};

EMX *matrixA = EMX_Generate(2, 2, dataA);
EMX *matrixB = EMX_Generate(2, 2, dataB);
EMX *matrixC = EMX_Generate(2, 4, dataC);

EMX *sum = EMX_Add(3, matrixA, matrixB, matrixA);
EMX_Print(sum);
EMX_Free(sum);

EMX *sub = EMX_Sub(2, matrixA, matrixB);
EMX_Print(sub);
EMX_Free(sub);

EMX *mul = EMX_Mul(2, matrixA, matrixC);
EMX_Print(mul);
EMX_Free(mul);

EMX_Free(matrixA);
EMX_Free(matrixB);
EMX_Free(matrixC);
```
