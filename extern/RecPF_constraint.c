#include <stdio.h>
#include <cv.h>
#include <math.h>
#include "RecPF_constraint.h"
#include "enhance.h"

void RecPF_constraint(int m,int n,double aTV, double aL1,CvMat* picks,CvMat* B,
                      int a,/*struct OPTS* st*/double aa ,CvMat* WT,CvMat* W,int range,IplImage* I,int constraint, IplImage* U)
{

    int bPrint = 0;
    int bComplex = 1;

    cvSetZero(U);

    if(/*OPTS.normalize == 1*/1) //true
    {
        double fctr = 1/range;
        //B = fctr*B
        int j,i;
        for(j = 1; j<B->cols; j++){
            for(i = 1; i<B->rows; i++){
                B->data.db[i*B->step+j] = fctr * B->data.db[i*B->step+j];
            }
        }

        int count =0;
        for(j = 1; j<picks->cols; j++){
            for(i = 1; i<picks->rows; i++){
                int element = cvmGet(picks,i,j);
                if (element == 0){
                    count++;
                }

            }
        }
        aTV = count/sqrt(m*n)*aTV;
        aL1 = count/sqrt(m*n)*aL1;
    }

    CvMat *Numer1, *Denom1;
    cvZero(Numer1);

    int j, i;
    for(j = 1; j<B->cols; j++){
        for(i = 1; i<B->rows; i++){
            Numer1->data.db[i*Numer1->step+j] = sqrt(m*n) * Numer1->data.db[i*Numer1->step+j];
            Denom1->data.db[i*Denom1->step+j] = 1;
        }
    }

    double prd = sqrt(aTV * /*beta*/2.0);
    //denom2


}
