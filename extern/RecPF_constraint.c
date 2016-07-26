#include <stdio.h>
#include <cv.h>
#include <math.h>
#include "RecPF_constraint.h"
#include "enhance.h"

void RecPF_constraint(int m,int n,double aTV, double aL1,CvMat* picks,CvMat* B,
                      int TVtype,/*struct OPTS* st*/double aa ,CvMat* WT,CvMat* W,int range,IplImage* I,int constraint, IplImage* U)
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

    CvMat *Numer1, *Denom1, *Denom2, *Denom;
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


    if(aL1 == 0){
        cvmAdd(Denom1, Denom2, Denom);
    }
    else{
        cvmAdd(Denom1, Denom2, Denom);
        for(j = 1; j<Denom->cols; j++){
            for(i = 1; i<Denom->rows; i++){
                double element = cvmGet(Denom, i, j) + aL1*/*beta*/2.0;
                cvmSet(Denom,i, j, element);
            }
        }
    }

    CvMat* Ux, *Uy, *bx, *by, *d, *d_penalty, *PsiTU;
    cvSetZero(Ux);
    cvSetZero(Uy);
    cvSetZero(bx);
    cvSetZero(by);
    cvSetZero(d);
    cvSetZero(d_penalty);

    if(aL1 > 0){
        cvSetZero(PsiTU);
        cvSetZero(d);
    }


    double MaxItr;
    double beta = 2.0;
    int ii;
    CvMat* Wx,Wy;

        for(ii =0; ii<MaxItr; ii++){

            switch(TVtype){
                case 1 :
                    cvmAdd(Ux, bx, Ux);
                    cvmAdd(Uy, by, Uy);
                break;

                case 2 :
                    Compute_Wx_Wy(Ux, Uy, bx, by, 1/beta, &Wx, &Wy);
                break;
                default :
                    printf("TVtype must be 1 or 2\n");
                break;

            }
            if(aL1 > 0){

                cvmAdd(PsiTU,d,PsiTU);
                int i,j;
                for(j = 1; j<PsiTU->cols; j++){
                    for(i = 1; i<PsiTU->rows; i++){

                        double element_sin = sin(cvmGet(PsiTU, i, j));
                        double element_abs = abs(cvmGet(PsiTU, i, j));

                        if(element_abs-1/beta > 0){
                            cvmSet(PsiTU,i,j,element_abs*element_sin);
                        }
                        else{
                            cvmSet(PsiTU,i,j,0.);
                        }

                    }
                }

            }



    }//for


    cvReleaseMat(&PsiTU);
    cvReleaseMat(&Numer1);
    cvReleaseMat(&Denom1);
    cvReleaseMat(&Denom2);
    cvReleaseMat(&Denom);
    cvReleaseMat(&Ux);
    cvReleaseMat(&Uy);
    cvReleaseMat(&bx);
    cvReleaseMat(&by);
    cvReleaseMat(&d);
    cvReleaseMat(&d_penalty);
}
