#include <stdio.h>
#include <stdlib.h>

void matrix_vector_multiply(long long *y, long long *A, long long *x, long long size) {
   long long i, j;

   for (i = 0; i < size; ++i) {
      for (j = 0; j < size; ++j) {
         y[i] += A[i*size + j] * x[j];
      }
   }
}

int main(int argc, char **argv) {

   long long size = 100;
   if (argc >= 2) size = atoi(argv[1]);

   // y = Ax
   long long *A = (long long *)malloc(sizeof(long long) * size * size);
   long long *x = (long long *)malloc(sizeof(long long) * size);
   long long *y = (long long *)calloc(size, sizeof(long long));
   long long i, j;

   for (i = 0; i < size; ++i)
      for (j = 0; j < size; j++)
         A[i*size + j] = j;

   for (i = 0; i < size; ++i)
      x[i] = i;

   matrix_vector_multiply(y, A, x, size);

   for (i = 1; i < size; ++i)
      if (y[i] != y[i-1]) {
         printf("failed\n");
         return 1;
      }

   printf("passed(%ld)\n", y[0]);
   free(A);
   free(x);
   free(y);

   return 0;
}

