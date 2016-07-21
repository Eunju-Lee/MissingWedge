#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <cv.h>
#include "extern/enhance.h"

int main()
{
    /*
    *********************************************************************
      Read the .png image
      matlab code : iFile = './input/sample02.png';
                    fprintf('\nreading file: %s', iFile);
                    I = imread(iFile);

      reference : http://www.libpng.org/pub/png/book/chapter13.html
     ********************************************************************
    */
    IplImage *image = cvLoadImage("sample.png");
    /*
    ***********************************************************

        Converts the matrix A to the intensity image I

        matlab code : org = mat2gray(I);

    ***********************************************************
    */

    double min, max;
    IplImage *org = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);
    cvMinMaxLoc(image, &min, &max, NULL, NULL, NULL);
    cvConvertScale(image, org, 1/(max-min), -min/(max-min));

   /*
    ****************************************************************

        %% FBP
        matlab code : theta=1:180;
                      sino =radon(org,theta);

    *****************************************************************
    */

   #if 0
    int x,y;
    int org_x, org_y, pixel;

    double xcenter = (double)width/2.0, ycenter = (double)height/2.0; //rotation center
    int **orignalImage;
    int **sinogramImage;

    for(int theta = 0; theta <180; theta++ )
    {
        double radian = theta*3.141592/180.0;
        double cc = cos(radian), ss=sin(-radian);

        for(int h = 0; h < height; h++ )
        {
            for(int w =0; w < weight; w++)
            {
                org_x = (int)(xcenter + ((double)h -ycenter)*ss + ((double)w-xconter)*cc );
                org_y = (int)(ycenter + ((double)h -ycenter)*cc + ((double)w-xconter)*ss );

                if((org_y > 0 &&orgy <height) && (org_x >=0 && org_x <width))
                    pixel = orignalImage[h][w];

                int **rotationImage[h][w] = pixel;

                sinogram[??][theta] = sum(rotationImage);
            }
        }
    }
    #endif // 0
    /*
    *********************************************************

        matlab code   recon= iradon(sino,theta);
                      F    = recon(2:n+1,2:n+1);
                      F    = mat2gray(F);

    *********************************************************
    */

    #if 0


    #endif // 0
    /*
    *********************************************************

        matlab code   m_aTV    = 1e-4;
                      m_aL1    = 1e-6;
                      m_iter   = 500;       % max # of iterations
                      m_gamma  = 1.0;       % \BA\AF\BC\F61
                      m_beta   = 10;        % \BA\AF\BC\F62
                      m_tol    = 1e-10;     % stopping tolerance based on relative change
                      [U]      = enhance(org, n, m_iter, m_gamma, m_beta, m_tol, m_aTV, m_aL1);

    *********************************************************
    */

    double m_aTV = 1e-4;
    double m_aL1 = 1e-6;
    double m_iter = 500;
    double m_gamma = 1.0;
    double m_beta = 10;
    double m_tol=1e-10;

    IplImage *dstIMageU = cvCreateImage(cvGetSize(org), IPL_DEPTH_8U, 1);
    dstIMageU = enhance(org, 256, m_iter, m_gamma, m_beta, m_tol, m_aTV, m_aL1);

    /*
    *********************************************************
        write .png image

        matlab code   fprintf('\nwriting result to ./output \n');
                      imwrite(org,   ['./output/INPUT_'  'a' num2str(m_gamma) '_b' num2str(m_beta) '_i' num2str(m_iter) '.png']);
                      imwrite(F,     ['./output/FBP_'  'a' num2str(m_gamma) '_b' num2str(m_beta) '_i' num2str(m_iter) '.png']);
                      imwrite(U,     ['./output/ENHANCED_'  'a' num2str(m_gamma) '_b' num2str(m_beta) '_i' num2str(m_iter) '.png']);


    *********************************************************
    */
    #if 0


    #endif // 0

    cvShowImage("image", dstIMageU);

    cvWaitKey(0);

    cvReleaseImage(&image);
    cvReleaseImage(&org);
    cvReleaseImage(&dstIMageU);
    cvDestroyWindow("image");


    return 0;
}
