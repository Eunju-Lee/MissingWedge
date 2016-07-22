
/* Include files */
#include "enhance.h"
#include "LineMask_limitedangleRange.h"
//#include <cv.h>
//#indlude <math.h>

#define pi 3.141592

int round_x(double a)
{
    int round_x;

    if(a < 0)  round_x = (int)(a * 100 + 0.5);
    else   round_x  = (int)(a * 100 + -0.5);

}
void find(IplImage *M)
{
    //Find indices and value nonzero elements

}
void LineMask_limitedandleTange(IplImage *image, int L, int N, IplImage* M, CvMat* Mh, CvMat* mi, CvMat* mhi)
{
    //CvMat* Mh, mi, mh, l;
//    IplImage *M = cvCreateImage(cvSize(N-1, L), 8, 1);

   // matlab : thc = linspace(0, pi-pi/L, L);
    int thc[L];

    int l;
    cvGet2D(image, 256, 256);
    for(l=0 ; l=L; l++)
    {
        thc[0] = 0;
        thc[l] = l * (pi-pi/L)/(L-1);
    }

    //matlab : M = zeros(N);
    cvZero(N);
    int xc, yr , nn;
    int ll=0;
    for(ll = 0; ll< L; ll++){
        if(thc[ll] >= pi/3 && thc[ll] <= pi/3 + pi/18
            || thc[ll] >= (2*pi/3-pi/18) && thc[ll] <= 2*pi/3) {
            xc = round_x(tan(thc[ll]) * (-N/3)) + N/2+1;  //round function


            for (nn = 0; nn< N-1; nn++){
                cvGet2D(M,nn+1, xc);
            }
        }

        else{
            if(thc[ll] >= pi/4 || thc[ll] > 3*pi/4) {
                yr = round_x(tan(thc[ll]) * (-N/3)) + N/2+1;  //round function

                for (nn = 0; nn< N-1; nn++){
                    cvGet2D(M,nn+1, yr);
                }
            }
            else{
                xc = round_x(tan(thc[ll]) * (-N/3)) + N/2+1;  //round function
                for (nn = 0; nn< N-1; nn++){
                    cvGet2D(M,nn+1, yr);
                }
            }
        }

    }
    //upper half plane mask
    cvZero(N);
    cvFFT(M,M,1,1); //0:fft, 1:ifft

}

