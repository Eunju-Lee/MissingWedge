/*
 * enhance.h
 *
 * Code generation for function 'enhance'
 *
 * C source code generated on: Mon Jul 18 10:06:54 2016
 *
 */

#ifndef __ENHANCE_H__
#define __ENHANCE_H__
/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "rt_nonfinite.h"

//#include "rtwtypes.h"
//#include "enhance_types.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern IplImage* enhance(IplImage *image, char n, double m_iter, double m_gamma, double m_beta, double m_tol, double m_aTV, double m_aL1);
#endif
/* End of code generation (enhance.h) */
