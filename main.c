#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <cv.h>
#include "extern/enhance.h"

int main()
{

    int m = 256, n = 256;
    //Read the .png image
    IplImage *image = cvLoadImage("sample.png");

    //Converts the matrix A to the intensity image I   matlab code : org = mat2gray(I);
    //IplImage *image_gray = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    //cvCvtColor(image, image_gray, CV_BGR2GRAY);

    //FBP matlab code : theta=1:180; sino =radon(org,theta);

    //matlab code   recon= iradon(sino,theta);  F    = recon(2:n+1,2:n+1);  F    = mat2gray(F);

    // matlab code   [U] = enhance(org, n, m_iter, m_gamma, m_beta, m_tol, m_aTV, m_aL1);
    double m_aTV = 1e-4, m_aL1 = 1e-6, m_iter = 500, m_gamma = 1.0, m_beta = 10, m_tol = 1e-10;

    //IplImage to CvMat
    CvMat matHader, *pSrcMat;
    pSrcMat = cvGetMat(image,&matHader,0,0);

    //CvMat to IplImage
    //IplImage *conv_img ,tmpImage;
    //conv_img = cvGetImage(psrcMat, &tmpImage);

    //CvMat *dstImageU = cvCreateMat(m,n,CV_32FC1);
    IplImage *dstImageU = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    dstImageU = enhance(image, n, m_iter, m_gamma, m_beta, m_tol, m_aTV, m_aL1);



    cvShowImage("image", image);
    cvWaitKey(0);

    cvReleaseImage(&image);
    cvReleaseImage(&pSrcMat);
    cvReleaseImage(&dstImageU);
    cvDestroyWindow("image");

    return 0;
}
