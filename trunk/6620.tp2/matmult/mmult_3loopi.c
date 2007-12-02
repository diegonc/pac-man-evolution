const char* matmult_desc = "Multiplicacion por 3 bucles invertido.";

void
matmult_cuadrado (const int M, 
              const double *A, const double *B, double *C)
{
  int i, j, k;

  for (j = 0; j < M; ++j) {
       for (i = 0; i < M; ++i) {
            const double *Ai_ = A + i;
            const double *B_j = B + j*M;

            double cij = *(C + j*M + i);

            for (k = 0; k < M; ++k) {
                 cij += *(Ai_ + k*M) * *(B_j + k);
            }

            *(C + j*M + i) = cij;
       }
  }
}
