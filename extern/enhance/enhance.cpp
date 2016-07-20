/*
 * enhance.cpp
 *
 * Code generation for function 'enhance'
 *
 * C source code generated on: Mon Jul 18 10:06:54 2016
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "enhance.h"
#include "enhance_emxutil.h"
#include "LineMask_limitedangleRange.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */

/* Function Definitions */
real_T enhance(const uint8_T I[65536], real_T n, real_T m_iter, real_T m_gamma,
               real_T m_beta, real_T m_tol, real_T m_aTV, real_T m_aL1)
{

  /*
        matlab code : constraint = 1;
                      x = reshape(I,n*n,1);

                      L             = 199;
                      [M,Mh,mi,mhi] = LineMask_limitedangleRange(L,n);
  */
  real_T U;
  emxArray_real_T *M;
  emxArray_real_T *Mh;
  emxArray_real_T *mi;
  emxArray_real_T *mhi;
  emxInit_real_T(&M, 2);
  emxInit_real_T(&Mh, 2);
  b_emxInit_real_T(&mi, 1);
  b_emxInit_real_T(&mhi, 1);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  LineMask_limitedangleRange(n, M, Mh, mi, mhi);

  /*  A             = @(z) A_fhp(z,OMEGA); */
  /*  At            = @(z) At_fhp(z,OMEGA,n); */
  /*  b             = A(x); */
  /*   wav = daubcqf(4); */
  /*  %  W = @(x) midwt(x,wav); */
  /*  %  WT = @(x) mdwt(x,wav); */
  /*   */
  /*   */
  /*     */
  /*      W = midwt(x,wav); */
  /*      WT = mdwt(x,wav); */
  /*  %%--------------------- */
  /*   */
  /*  opts = []; */
  /*  opts.maxItr     = m_iter;    % max # of iterations */
  /*  opts.gamma      = m_gamma;    */
  /*  opts.beta       = m_beta;        */
  /*  opts.relchg_tol = m_tol;     % stopping tolerance based on relative change */
  /*  opts.real_sol   = true;       */
  /*  opts.normalize  = true;       */
  /*                               */
  /*   */
  /*  pick=false(m,n); */
  /*  pick(picks)=true;  */
  /*   */
  /*  [U,Out_RecPF] = RecPF_constraint(m,n,aTV,aL1,pick,B,2,opts,WT,W,range(I(:)),I,constraint); */
  emxFree_real_T(&mhi);
  emxFree_real_T(&mi);
  emxFree_real_T(&Mh);
  emxFree_real_T(&M);
  return U;
}

/* End of code generation (enhance.cpp) */
