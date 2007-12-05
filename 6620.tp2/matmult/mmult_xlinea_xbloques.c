
const char* matmult_desc = "Multiplicacion de matrices por linea por bloques.";

/* Se puede jugar con este valor */
#if !defined(TAM_BLOQUE)
#define TAM_BLOQUE ((int) 95)
#endif

void
matmult_basico (const int lda,
             const int M, const int N, const int K,
             const double *A, const double *B, double *C)
{
	int i,j,k;
	
	const double* Bi = B;
	double* Ci = C;

	for( i = 0; i < N; i++, Bi+=lda, Ci+=lda ) {
		const double* Aj = A;
		for( j = 0; j < K; j++, Aj+=lda ) {
			double Bij = Bi[j];
			for( k = 0; k < M; k++ ) {
				Ci[k] += Aj[k] * Bij;
			}
		}
	}	
}
#include <stdio.h>

void
procesar_bloque (const int lda,
          const double *A, const double *B, double *C,
          const int i, const int j, const int k)
{
     /*
       Recordar que hay que tener en cuenta los bloques incompletos de los bordes.
       Si la matriz es de 7x7 y los bloques de 3x3, hay bloques de 1x3, 3x1 y 1x1.


             xxxoooX
             xxxoooX
             xxxoooX
             oooxxxO
             oooxxxO
             oooxxxO
             XXXOOOX

     */
     const int M = (i+TAM_BLOQUE > lda? lda-i : TAM_BLOQUE);
     const int N = (j+TAM_BLOQUE > lda? lda-j : TAM_BLOQUE);
     const int K = (k+TAM_BLOQUE > lda? lda-k : TAM_BLOQUE);
     
     matmult_basico (lda, M, N, K,
                  A + i + k*lda, B + k + j*lda, C + i + j*lda);
}

void
matmult_cuadrado (const int M, 
              const double *A, const double *B, double *C)
{
     const int n_blocks = M / TAM_BLOQUE + (M%TAM_BLOQUE? 1 : 0);
     int bi, bj, bk;
      
     for (bi = 0; bi < n_blocks; ++bi) {
          const int i = bi * TAM_BLOQUE;
          
          for (bj = 0; bj < n_blocks; ++bj) {
               const int j = bj * TAM_BLOQUE;

               for (bk = 0; bk < n_blocks; ++bk) {
                    const int k = bk * TAM_BLOQUE;
                    
                    procesar_bloque (M, A, B, C, i, j, k);
               }
          }
     }
}
