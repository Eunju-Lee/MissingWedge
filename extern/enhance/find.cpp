/*
 * find.cpp
 *
 * Code generation for function 'find'
 *
 * C source code generated on: Mon Jul 18 10:06:54 2016
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "enhance.h"
#include "find.h"
#include "enhance_emxutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
void find(const emxArray_real_T *x, emxArray_real_T *i)
{
  int32_T nx;
  int32_T idx;
  int32_T i1;
  uint32_T ii;
  boolean_T exitg1;
  boolean_T guard1 = FALSE;
  emxArray_real_T *b_i;
  nx = x->size[0] * x->size[1];
  idx = 0;
  i1 = i->size[0];
  i->size[0] = nx;
  emxEnsureCapacity((emxArray__common *)i, i1, (int32_T)sizeof(real_T));
  ii = 1U;
  exitg1 = 0U;
  while ((exitg1 == 0U) && (ii <= (uint32_T)nx)) {
    guard1 = FALSE;
    if (x->data[(int32_T)ii - 1] != 0.0) {
      idx++;
      i->data[idx - 1] = (real_T)ii;
      if (idx >= nx) {
        exitg1 = 1U;
      } else {
        guard1 = TRUE;
      }
    } else {
      guard1 = TRUE;
    }

    if (guard1 == TRUE) {
      ii++;
    }
  }

  if (nx == 1) {
    if (idx == 0) {
      i1 = i->size[0];
      i->size[0] = 0;
      emxEnsureCapacity((emxArray__common *)i, i1, (int32_T)sizeof(real_T));
    }
  } else {
    if (1 > idx) {
      idx = 0;
    }

    b_emxInit_real_T(&b_i, 1);
    i1 = b_i->size[0];
    b_i->size[0] = idx;
    emxEnsureCapacity((emxArray__common *)b_i, i1, (int32_T)sizeof(real_T));
    nx = idx - 1;
    for (i1 = 0; i1 <= nx; i1++) {
      b_i->data[i1] = i->data[i1];
    }

    i1 = i->size[0];
    i->size[0] = b_i->size[0];
    emxEnsureCapacity((emxArray__common *)i, i1, (int32_T)sizeof(real_T));
    nx = b_i->size[0] - 1;
    for (i1 = 0; i1 <= nx; i1++) {
      i->data[i1] = b_i->data[i1];
    }

    emxFree_real_T(&b_i);
  }
}

/* End of code generation (find.cpp) */
