// sudo apt install libopenblas-dev libopenblass-base
// gcc -O3 matrices.c -o matrices -lgomp -lopenblas && ./matrices
// cc -o sgemm sgemm.c -lopenblas -lgomp
// cat /proc/cpuinfo
// OMP_NUM_THREADS=1 ./sgemm
// 
/*
cs.../~bc/cp2018
*/

// los #pragma sirven para ignorar gcc warnings de docopt.c (https://stackoverflow.com/questions/6321839/how-to-disable-warnings-for-particular-include-files/29994938#29994938)
#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "docopt.c" // <- Este es un archivo automaticamente generado usando $ make docopt
#pragma GCC diagnostic pop


#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <stdbool.h>

#define N 700
#define STEPS 10

void init(float * m) {
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            m[y * N + x] = 1.0f;
        }
    }
}


// register
int main(int argc, char ** argv) {

    DocoptArgs args = docopt(argc, argv, /* help */ true, /* version */ "0.0.1"); //ignorable :)

    size_t matsize = N * N * sizeof(float);

    /* alojar matrices */
    // float a[N][N]  <<- utilizaria el stack que tiene memoria limitada --> stack overflow!!
    float *a = malloc(matsize);  // <<--- utiliza el heap
    float *b = malloc(matsize);
    float *c = malloc(matsize);

    /* inicializar valores */
    init(a);
    init(b);
    init(c);

    /* TODO: cronometrar */
    double start_time = omp_get_wtime();
    // usar omp_get_wtime # include <omp.h> -lgom
    //do stuff

    printf("Number of threads (this can be changed using envir variable OMP_NUM_THREADS=1): %d\n",  
        omp_get_num_threads());
    if (args.conblas)
        for (int i = 0; i < STEPS; ++i)
            /* TODO: C += A * B */
            /* Discussion
                This function multiplies A * B and multiplies the resulting matrix by alpha. It then multiplies matrix C by beta. It stores the sum of these two products in matrix C.
                Thus, it calculates either
                    C←αAB + βC
                        or
                    C←αBA + βC
                 with optional use of transposed forms of A, B, or both.
            */
            cblas_sgemm(
                CblasRowMajor,  /* Specifies row-major (C) or column-major (Fortran) data ordering. */
                CblasNoTrans,   /* Specifies whether to transpose matrix A. */
                CblasNoTrans,   /* Specifies whether to transpose matrix B. */
                N,              /* Number of rows in matrices A and C. */
                N,              /* Number of columns in matrices B and C. */
                N,              /* Number of columns in matrix A;  */
                1.0,            /* Scaling factor for the product of matrices A and B. */
                a,              /* Matrix A. */
                N,              /* The size of the first dimention of matrix A; if you are passing a matrix A[m][n], the value should be m. */
                b,              /* Matrix B. */
                N,              /* The size of the first dimention of matrix B; if you are passing a matrix B[m][n], the value should be m. */
                1.0,            /* Scaling factor for matrix C. */
                c,              /* Matrix C. */
                N               /* The size of the first dimention of matrix C; if you are passing a matrix C[m][n], the value should be m. */
                );
    else
        for (int i = 0; i < STEPS; ++i)
            for (int y = 0; y < N; y++)
               for (int x = 0; x < N; x++)
                  for (int z = 0; z < N; z++)
                      c[x * N + y] += a[x * N + z] * b[z * N + y];

    if (args.c0)
        printf("finalmente: c[0] = %f\n", c[0]);

    /* TODO: tiempo transcurrido */
    double elapsed = omp_get_wtime() - start_time;
    printf("took %lf s\n", elapsed);
    double operations = 2.0 * STEPS * N * N * (N + 1.0);
    double gflops = operations / (1000.0 * 1000.0 * 1000.0 * elapsed);
    // charlie .442733 GFLOPS
    printf("%f GFLOPS\n", gflops);

    /* devolver algun resultado para que el compilador no descarte codigo */
    return (int) c[0];
}