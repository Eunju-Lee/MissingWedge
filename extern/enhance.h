/*
 * enhance.h
 *
 * Code generation for function 'enhance'
 *
 * C source code generated on: Mon Jul 18 10:06:54 2016
 *
 */
#include <stdio.h>
#include <cv.h>

typedef struct OPTS{

    double maxItr;
    double gamma;
    double beta;
    double relchg_tol;
    char real_sol;
    char normalize;

};

/* Function Declarations */
IplImage* enhance(IplImage *image, int n, double m_iter, double m_gamma, double m_beta, double m_tol, double m_aTV, double m_aL1);
