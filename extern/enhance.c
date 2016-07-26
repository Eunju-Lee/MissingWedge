/* Include files */
#include "enhance.h"
#include "LineMask_limitedangleRange.h"
#include "A_fhp.h"



IplImage* enhance(IplImage *image, int n, double m_iter, double m_gamma, double m_beta, double m_tol, double m_aTV, double m_aL1)
{
    struct OPTS opts;
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
    b = A_fhp(x, &OMEGA);

    //OMEGA = [1;OMEGA]
    b->data.fl[1] = 1;
    //b->data.fl[2] = OMEGA;
    //pick = OMEGA


    int cM, cN, p, o;
    cM = image->width;
    cN = image->height;
    IplImage * FB;

    cvFFT(image,image, 0,0);
    for(p = 0; p<image->width; p++){
        for(o=0; o<image->height; o++){

            FB->imageData[o+p*image->widthStep] = image->imageData[o+p*image->widthStep] * sqrt(cM*cN);
        }
    }

    //B=FB(Picks);

    double aTV = m_aTV;
    double aL1 = m_aL1;

    CvMat *wav, *W;
    daubcqf(4, &wav);

    midwt(x,wav,&W);
//  mdwt(x,wav, &w);

    opts.maxItr = m_iter;
    opts.gamma = m_gamma;
    opts.beta = m_beta;
    opts.relchg_tol = 1;
    opts.normalize = 1;

    CvMat * pick ,*B, *WT;
    cvSetZero(pick);        //pick = false(m,n);

    //pick(picks)=true;
    int range = cM;
    int m = 256;
    CvMat * U = cvCreateMat(m,n,CV_32FC1);
 //   int m=256;


    RecPF_constraint(m,n,aTV, aL1,pick,B,2, opts.maxItr, WT, W,range,image,constraint, &U);


  }

