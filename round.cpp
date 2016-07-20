/*
 * round.cpp
 *
 * Code generation for function 'round'
 *
 * C source code generated on: Mon Jul 18 10:06:54 2016
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "enhance.h"
#include "round.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void b_round(emxArray_real_T *x)
{
  int32_T loop_ub;
  uint32_T k;
  real_T b_x;
  loop_ub = x->size[1];
  for (k = 1U; k <= (uint32_T)loop_ub; k++) {
    if (fabs(x->data[(int32_T)k - 1]) > 4.503599627370496E+15) {
      b_x = x->data[(int32_T)k - 1];
    } else if (x->data[(int32_T)k - 1] >= 0.5) {
      b_x = floor(x->data[(int32_T)k - 1] + 0.5);
    } else if (x->data[(int32_T)k - 1] > -0.5) {
      b_x = x->data[(int32_T)k - 1] * 0.0;
    } else {
      b_x = ceil(x->data[(int32_T)k - 1] - 0.5);
    }

    x->data[(int32_T)k - 1] = b_x;
  }
}

/* End of code generation (round.cpp) */
