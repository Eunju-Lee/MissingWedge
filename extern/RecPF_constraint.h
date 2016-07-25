#include <stdio.h>
//#include "enhance.h"

void RecPF_constraint(int m,int n,double aTV, double aL1,CvMat* pick,CvMat* B,
                      int a,/*struct OPTS* st*/ double aa,CvMat* WT,CvMat* W,int range,IplImage* I,int constraint, IplImage* U);
