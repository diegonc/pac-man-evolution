#include <stdlib.h>

const char* matmult_desc = "Multiplicacion basica de tres bucles luego de trasponer.";

double* trasp_init( const int N, const double* M )
{
	int i,j;
	double* buf = malloc( sizeof(double)*N*N );
	for( i = 0; i < N; i++ )
		for( j = 0; j < N;  j++ )
			buf[i*N + j] = M[j*N + i];
	return buf;
}

void trasp_free( double* M )
{
	free( M );
}

void
matmult_cuadrado (const int M, 
              const double *A, const double *B, double *C)
{
  int i, j, k;

  double* T = trasp_init( M, A );
  for (i = 0; i < M; ++i) {
       for (j = 0; j < M; ++j) {
            const double *Ai_ = T + i*M;
            const double *B_j = B + j*M;

            double cij = *(C + j*M + i);

            for (k = 0; k < M; ++k) {
                 cij += *(Ai_ + k) * *(B_j + k);
            }

            *(C + j*M + i) = cij;
       }
  }
  trasp_free( T );
}
