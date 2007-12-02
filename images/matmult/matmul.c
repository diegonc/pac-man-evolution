/*
  Idealmente, no haría falta hacer cambios en este archivo. Puede querer 
  hacer algunos cambios para depurar el programa, pero recuerde revertirlos
  para las corridas finales. 

  El formato de salida: "Tam: %u\tmflop/s: %g\n"

El archivo ha pasado por estas manos:
    Jason Riedy
    David Bindel
    David Garmire
    Juan Heguiabehere
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <float.h>
#include <math.h>

#include <sys/types.h>
#include <sys/resource.h>

#include <unistd.h>
#include <time.h>

#include "timing.h"

#if !defined(COMPILER)
#  define COMPILER "desconocido"
#endif
#if !defined(FLAGS)
#  define FLAGS "desconocido"
#endif
#if !defined(PLATFORM)
#  define PLATFORM "desconocido"
#endif

/*
  La firma de su función DEBE ser la siguiente:
*/
extern const char* matmult_desc;
extern void matmult_cuadrado ();

/*
  Tratamos de hacer suficiente cantidad de iteraciones para conseguir 
  mediciones razonables. Las matrices se multiplican al menos MIN_TIMES veces.
  Si eso no tarda al menos MIN_SECS segundos, duplicamos el número de iteraciones 
  y probamos de nuevo.

  Puede jugar con estos parámetros para apurar el debugging...
*/
#define MIN_RUNS 4
#define MIN_SECS 1.0

/*
  La lista de tamaños de matriz es un poco exótica... hay efectos interesantes
  cerca de algunas potencias de 2.
*/
const int test_sizes[] = {
  31, 32, 96, 97, 127, 128, 129, 191, 192, 229,
#if defined(DEBUG_RUN)
# define MAX_SIZE 229u
#else
  255, 256, 257, 319, 320, 321, 417, 479, 480, 511, 512, 639, 640,
  767, 768, 769,
# define MAX_SIZE 769u
#endif
};

#define N_SIZES (sizeof (test_sizes) / sizeof (int))

static double A[MAX_SIZE * MAX_SIZE], B[MAX_SIZE * MAX_SIZE],
  C[MAX_SIZE * MAX_SIZE];

static void matriz_init (double* A);
static void matriz_clear (double* C);

/* Compara C con la version de multiplicar A*B con los tres bucles*/
static void validar_matmult (const int M,
			    const double *A, const double *B, double *C);
/* Contar los mflop/s */
static double cronometrar_matmult (const int M,
			  const double *A, const double *B, double *C);

int
main (void)
{
  int i;
  double mflop_s;

  matriz_init (A);
  matriz_init (B);

  printf ("Compilador:\t%s\nOpciones:\t%s\nPlataforma:\t%s\nDescripcion:\t%s\n\n",
	  COMPILER, FLAGS, PLATFORM, matmult_desc);

  /* printf ("Resolucion: %Lg\n", timer_resolution() ); */

  for (i = 0; i < N_SIZES; ++i) {

    const int M = test_sizes[i];

#ifndef NO_VALIDATE
    validar_matmult (M, A, B, C);
#endif
    mflop_s = cronometrar_matmult(M, A, B, C);    

    printf ("Tam: %u\tmflop/s: %lg\n", M, mflop_s);
  }

  return 0;
}

void 
matriz_init (double *A)
{
  int i;

  for (i = 0; i < MAX_SIZE*MAX_SIZE; ++i) {
    A[i] = ((unsigned char)lrand48()) / 20 ; /* drand48 (); */
  }
}

void 
matriz_clear (double *C) 
{
  memset (C, 0, MAX_SIZE * MAX_SIZE * sizeof (double));
}

/*
  Los productos de matrices satisfacen la siguiente cota de error:
  float(sum a_i * b_i) = sum a_i * b_i * (1 + delta_i)
  donde delta_i <= n * epsilon. Para validar su producto de matrices,
  computamos cada elemento y verificamos que su producto esté dentro 
  de un rango de error de tres veces este valor. Lo hacemos tres veces
  porque hay tres fuentes de error:

  - El error de redondeo en su producto
  - El error de redondeo en nuestro producto
  - El error de redondeo al computar la cota de error (esta última no es tan significativa)
*/
void
validar_matmult (const int M,
                const double *A, const double *B, double *C)
{
  int i, j, k;

  matriz_clear (C);
  matmult_cuadrado (M, A, B, C);

  for (i = 0; i < M; ++i) {
    for (j = 0; j < M; ++j) {

      double dotprod = 0;
      double errorbound = 0;
      double err;

      for (k = 0; k < M; ++k) {
	double prod = A[k*M + i] * B[j*M + k];
	dotprod += prod;
	errorbound += fabs(prod);
      }
      errorbound *= (M * DBL_EPSILON);

      err = fabs(C[j*M + i] - dotprod);
      if (err > 3*errorbound) {
	printf("Error en el producto de matrices.\n");
	printf("C(%d,%d) deberia ser %lg, y fue %lg\n", i, j,
	       dotprod, C[j*M + i]);
	printf("Error de %lg, limite aceptable %lg\n",
	       err, 3*errorbound);
	exit(-1);
      }
    }
  }
}

double
cronometrar_matmult (const int M,
            const double *A, const double *B, double *C)
{
  struct timespec start, finish;
  double mflops, mflop_s;
  double secs = -1.0;

  int num_iterations = MIN_RUNS;
  int i;

  while (secs < MIN_SECS) {

    matriz_clear (C);
    get_time (&start);
    for (i = 0; i < num_iterations; ++i) {
      matmult_cuadrado (M, A, B, C);
    }
    get_time (&finish);
    secs = timespec_diff (start, finish);

    mflops  = 2.0 * num_iterations * M * M * M / 1.0e6;
    mflop_s = mflops/secs;

    num_iterations *= 2;
  }

  return mflop_s;
}

