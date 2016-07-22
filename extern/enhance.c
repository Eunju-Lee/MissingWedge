/* Include files */
#include "enhance.h"
#include "LineMask_limitedangleRange.h"
#include "A_fhp.h"

IplImage* enhance(IplImage *image, int n, double m_iter, double m_gamma, double m_beta, double m_tol, double m_aTV, double m_aL1)
{

  // matlab code : constraint = 1;  x = reshape(I,n*n,1); L   = 199;
  //[M,Mh,mi,mhi] = LineMask_limitedangleRange(L,n);
  IplImage *x = cvCreateImage(cvSize(n,n), 8, 1);
  cvResize(image,x, 0);

   int constraint = 1;
   int L = 199;

   CvMat * M, Mh, mi, mhi;

   LineMask_limitedandleTange(image, L,n, &M, &Mh, &mi, &mhi);

    CvMat OMEGA = mhi;
    int k = mhi.cols * mhi.rows;    //length(mhi)

    CvMat *b;
    //b = A_fhp(x, OMEGA);

  }

