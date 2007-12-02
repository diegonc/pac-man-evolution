const char* matmult_desc = "Multiplicacion por columnas de A.";

void
matmult_cuadrado (const int M, 
              const double *A, const double *B, double *C)
{
	int i,j,k;
	
	const double* Bi = B;
	double* Ci = C;

	for( i = 0; i < M; i++, Bi+=M, Ci+=M ) {
		const double* Aj = A;
		for( j = 0; j < M; j++, Aj+=M ) {
			double Bij = Bi[j];
			for( k = 0; k < M; k++ ) {
				Ci[k] += Aj[k] * Bij;
			}
		}
	}	
}
