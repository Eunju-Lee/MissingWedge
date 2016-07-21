/* Include files */
#include "enhance.h"
#include "LineMask_limitedangleRange.h"


IplImage* enhance(IplImage *image, char n, double m_iter, double m_gamma,
               double m_beta, double m_tol, double m_aTV, double m_aL1)
{

  /*
        matlab code : constraint = 1;
                      x = reshape(I,n*n,1);

                      L             = 199;
                      [M,Mh,mi,mhi] = LineMask_limitedangleRange(L,n);
  */
    char constraint = 1;
    CvMat *CvMat_Img;
    CvMat_Img = cvCreateMat(80, 60, 1);
    cvGetMat(image, &CvMat_Img);
    cvReshape(image, CvMat &header, 0,1);

    char L = 199;

    LineMask_limitedandleRange(L, n);


  }

