// #define EMX_USE_DOUBLE_DATA
#include "emx.h"

int main() {
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

  return 0;
}