
#include <cv.h>
#include <math.h>


int round_y(double a)
{
    int round_y;

    if(a < 0)  round_y = (int)(a * 100 + 0.5);
    else   round_y  = (int)(a * 100 + -0.5);

}
CvMat* A_fhp(IplImage *x, CvMat *OMEGA)
{
    int w = x->width;
    int h = x->height;
    int n,p,o;

    if (w > h){
        n = round_y(sqrt(w));
    }
        n = round_y(sqrt(h));

        IplImage *x_dst = cvCreateImage(cvGetSize(x), 8,1);
        IplImage *y_dst = cvCreateImage(cvGetSize(x), 8,1);

        cvResize(x,x_dst,0);
        cvDFT(x_dst,x_dst,CV_DXT_FORWARD, 0);

        for(p=1; p< x_dst->width;p++){
            for(o=1; o< x_dst->height;o++){
               y_dst->imageData[o+p*y_dst->widthStep] = 1/n * x_dst->imageData[o+p*x_dst->widthStep];

            }
        }
        //y = [yc(1,1); sqrt(2)*real(yc(OMEGA)) sqrt(2)*imag(yc(OMEGA))];
        //IplImage *y ;
        //y->imagedata[] = cvGet2D(y_dst,1,1);
        //cvMat *y = cvGet2D(yc 1,1);
}
