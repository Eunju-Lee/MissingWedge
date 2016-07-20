/*
 * LineMask_limitedangleRange.cpp
 *
 * Code generation for function 'LineMask_limitedangleRange'
 *
 * C source code generated on: Mon Jul 18 10:06:54 2016
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "enhance.h"
#include "LineMask_limitedangleRange.h"
#include "enhance_emxutil.h"
#include "round.h"
#include "find.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void eml_ifftshift(emxArray_real_T *x, int32_T dim);

/* Function Definitions */
static void eml_ifftshift(emxArray_real_T *x, int32_T dim)
{
  int32_T i1;
  int32_T vlend2;
  int32_T n;
  int32_T vstride;
  int32_T k;
  int32_T i;
  int32_T npages;
  int32_T vspread;
  int32_T midoffset;
  int32_T j;
  int32_T ia;
  int32_T ib;
  real_T xtmp;
  int32_T ic;
  if (dim > 2) {
  } else {
    i1 = x->size[dim - 1];
    if (i1 <= 1) {
    } else {
      vlend2 = i1 / 2;
      if (vlend2 << 1 == i1) {
        i1 = x->size[dim - 1];
        if (i1 <= 1) {
        } else {
          vlend2 = i1 / 2;
          n = dim - 1;
          vstride = 1;
          for (k = 1; k <= n; k++) {
            i = x->size[k - 1];
            vstride *= i;
          }

          npages = 1;
          k = dim + 1;
          while (k < 3) {
            i = x->size[1];
            npages *= i;
            k = 3;
          }

          vspread = (i1 - 1) * vstride;
          midoffset = vlend2 * vstride;
          if (vlend2 << 1 == i1) {
            n = -1;
            for (i = 1; i <= npages; i++) {
              i1 = n;
              n += vspread;
              for (j = 1; j <= vstride; j++) {
                i1++;
                n++;
                ia = i1;
                ib = i1 + midoffset;
                for (k = 1; k <= vlend2; k++) {
                  xtmp = x->data[ia];
                  x->data[ia] = x->data[ib];
                  x->data[ib] = xtmp;
                  ia += vstride;
                  ib += vstride;
                }
              }
            }
          } else {
            n = -1;
            for (i = 1; i <= npages; i++) {
              i1 = n;
              n += vspread;
              for (j = 1; j <= vstride; j++) {
                i1++;
                n++;
                ia = i1;
                ib = i1 + midoffset;
                xtmp = x->data[ib];
                for (k = 1; k <= vlend2; k++) {
                  ic = ib + vstride;
                  x->data[ib] = x->data[ia];
                  x->data[ia] = x->data[ic];
                  ia += vstride;
                  ib = ic;
                }

                x->data[ib] = xtmp;
              }
            }
          }
        }
      } else {
        n = dim - 1;
        vstride = 1;
        for (k = 1; k <= n; k++) {
          i = x->size[k - 1];
          vstride *= i;
        }

        npages = 1;
        k = dim + 1;
        while (k < 3) {
          i = x->size[1];
          npages *= i;
          k = 3;
        }

        vspread = (i1 - 1) * vstride;
        midoffset = vlend2 * vstride;
        n = -1;
        for (i = 1; i <= npages; i++) {
          i1 = n;
          n += vspread;
          for (j = 1; j <= vstride; j++) {
            i1++;
            n++;
            ia = i1 + midoffset;
            ib = n;
            xtmp = x->data[n];
            for (k = 1; k <= vlend2; k++) {
              ia -= vstride;
              ic = ib;
              ib -= vstride;
              x->data[ic] = x->data[ia];
              x->data[ia] = x->data[ib];
            }

            x->data[ib] = xtmp;
          }
        }
      }
    }
  }
}

void LineMask_limitedangleRange(real_T N, emxArray_real_T *M, emxArray_real_T
  *Mh, emxArray_real_T *mi, emxArray_real_T *mhi)
{
  int32_T i0;
  int32_T loop_ub;
  emxArray_real_T *xc;
  int32_T ll;
  static const real_T dv0[199] = { 0.0, 0.015786897756732629,
    0.031573795513465258, 0.047360693270197887, 0.063147591026930516,
    0.078934488783663145, 0.094721386540395774, 0.1105082842971284,
    0.12629518205386103, 0.14208207981059368, 0.15786897756732629,
    0.17365587532405891, 0.18944277308079155, 0.20522967083752419,
    0.22101656859425681, 0.23680346635098942, 0.25259036410772207,
    0.26837726186445471, 0.28416415962118735, 0.29995105737791994,
    0.31573795513465258, 0.33152485289138522, 0.34731175064811781,
    0.36309864840485045, 0.3788855461615831, 0.39467244391831574,
    0.41045934167504838, 0.42624623943178097, 0.44203313718851361,
    0.45782003494524626, 0.47360693270197884, 0.48939383045871149,
    0.50518072821544413, 0.52096762597217672, 0.53675452372890942,
    0.552541421485642, 0.5683283192423747, 0.58411521699910729,
    0.59990211475583988, 0.61568901251257258, 0.63147591026930516,
    0.64726280802603775, 0.66304970578277045, 0.678836603539503,
    0.69462350129623562, 0.71041039905296832, 0.72619729680970091,
    0.74198419456643361, 0.7577710923231662, 0.77355799007989878,
    0.78934488783663148, 0.80513178559336407, 0.82091868335009677,
    0.83670558110682935, 0.85249247886356194, 0.86827937662029464,
    0.88406627437702723, 0.89985317213375982, 0.91564006989049251,
    0.9314269676472251, 0.94721386540395769, 0.96300076316069039,
    0.978787660917423, 0.99457455867415567, 1.0103614564308883,
    1.0261483541876208, 1.0419352519443534, 1.0577221497010862,
    1.0735090474578188, 1.0892959452145514, 1.105082842971284,
    1.1208697407280166, 1.1366566384847494, 1.152443536241482,
    1.1682304339982146, 1.1840173317549472, 1.1998042295116798,
    1.2155911272684123, 1.2313780250251452, 1.2471649227818777,
    1.2629518205386103, 1.2787387182953429, 1.2945256160520755,
    1.3103125138088083, 1.3260994115655409, 1.3418863093222735,
    1.3576732070790061, 1.3734601048357387, 1.3892470025924712,
    1.4050339003492041, 1.4208207981059366, 1.4366076958626692,
    1.4523945936194018, 1.4681814913761344, 1.4839683891328672,
    1.4997552868895998, 1.5155421846463324, 1.531329082403065,
    1.5471159801597976, 1.5629028779165304, 1.578689775673263,
    1.5944766734299956, 1.6102635711867281, 1.6260504689434607,
    1.6418373667001935, 1.6576242644569261, 1.6734111622136587,
    1.6891980599703913, 1.7049849577271239, 1.7207718554838565,
    1.7365587532405893, 1.7523456509973219, 1.7681325487540545,
    1.783919446510787, 1.7997063442675196, 1.8154932420242524, 1.831280139780985,
    1.8470670375377176, 1.8628539352944502, 1.8786408330511828,
    1.8944277308079154, 1.9102146285646482, 1.9260015263213808,
    1.9417884240781134, 1.9575753218348459, 1.9733622195915785,
    1.9891491173483113, 2.0049360151050437, 2.0207229128617765,
    2.0365098106185093, 2.0522967083752417, 2.0680836061319745,
    2.0838705038887069, 2.0996574016454397, 2.1154442994021725,
    2.1312311971589049, 2.1470180949156377, 2.16280499267237, 2.1785918904291028,
    2.1943787881858356, 2.210165685942568, 2.2259525836993008,
    2.2417394814560332, 2.257526379212766, 2.2733132769694988,
    2.2891001747262312, 2.304887072482964, 2.3206739702396963,
    2.3364608679964292, 2.3522477657531615, 2.3680346635098943,
    2.3838215612666271, 2.3996084590233595, 2.4153953567800923,
    2.4311822545368247, 2.4469691522935575, 2.4627560500502903,
    2.4785429478070227, 2.4943298455637555, 2.5101167433204878,
    2.5259036410772207, 2.5416905388339535, 2.5574774365906858,
    2.5732643343474186, 2.589051232104151, 2.6048381298608838,
    2.6206250276176166, 2.636411925374349, 2.6521988231310818,
    2.6679857208878142, 2.683772618644547, 2.69955951640128, 2.7153464141580121,
    2.731133311914745, 2.7469202096714773, 2.76270710742821, 2.7784940051849425,
    2.7942809029416753, 2.8100678006984081, 2.8258546984551405,
    2.8416415962118733, 2.8574284939686057, 2.8732153917253385,
    2.8890022894820713, 2.9047891872388036, 2.9205760849955364,
    2.9363629827522688, 2.9521498805090016, 2.9679367782657344,
    2.9837236760224668, 2.9995105737791996, 3.015297471535932,
    3.0310843692926648, 3.0468712670493976, 3.06265816480613, 3.0784450625628628,
    3.0942319603195951, 3.1100188580763279, 3.1258057558330603 };

  real_T x;
  real_T a;
  real_T d;
  int32_T n;
  real_T apnd;
  real_T ndbl;
  real_T cdiff;
  real_T absa;
  real_T absb;
  int32_T nm1;
  int32_T nm1d2;
  int32_T k;
  emxArray_int32_T *r0;
  emxArray_int32_T *r1;
  emxArray_int32_T *r2;
  i0 = M->size[0] * M->size[1];
  M->size[0] = (int32_T)N;
  M->size[1] = (int32_T)N;
  emxEnsureCapacity((emxArray__common *)M, i0, (int32_T)sizeof(real_T));
  loop_ub = (int32_T)N * (int32_T)N - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    M->data[i0] = 0.0;
  }

  emxInit_real_T(&xc, 2);
  for (ll = 0; ll < 199; ll++) {
    if (((dv0[ll] >= 1.0471975511965976) && (dv0[ll] <= 1.2217304763960306)) ||
        ((dv0[ll] >= 1.9198621771937623) && (dv0[ll] <= 2.0943951023931953))) {
      x = 1.0 / tan(dv0[ll]);
      a = -N / 2.0 + 1.0;
      d = N / 2.0 - 1.0;
      if (d < a) {
        n = 0;
        apnd = d;
      } else if (rtIsInf(a) || rtIsInf(d)) {
        n = 1;
        a = rtNaN;
        apnd = d;
      } else {
        ndbl = floor((d - a) + 0.5);
        apnd = a + ndbl;
        cdiff = apnd - d;
        absa = fabs(a);
        absb = fabs(d);
        if (absa > absb) {
          absb = absa;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = d;
        } else if (cdiff > 0.0) {
          apnd = a + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int32_T)ndbl;
        } else {
          n = 0;
        }
      }

      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      xc->size[1] = n;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      if (n > 0) {
        xc->data[0] = a;
        if (n > 1) {
          xc->data[n - 1] = apnd;
          nm1 = n - 1;
          nm1d2 = nm1 / 2;
          loop_ub = nm1d2 - 1;
          for (k = 1; k <= loop_ub; k++) {
            xc->data[k] = a + (real_T)k;
            xc->data[(n - k) - 1] = apnd - (real_T)k;
          }

          if (nm1d2 << 1 == nm1) {
            xc->data[nm1d2] = (a + apnd) / 2.0;
          } else {
            xc->data[nm1d2] = a + (real_T)nm1d2;
            xc->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
          }
        }
      }

      a = N / 2.0;
      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      nm1 = xc->size[0];
      nm1d2 = xc->size[1];
      loop_ub = nm1 * nm1d2 - 1;
      for (i0 = 0; i0 <= loop_ub; i0++) {
        xc->data[i0] *= x;
      }

      b_round(xc);
      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      nm1 = xc->size[0];
      nm1d2 = xc->size[1];
      loop_ub = nm1 * nm1d2 - 1;
      for (i0 = 0; i0 <= loop_ub; i0++) {
        xc->data[i0] = (xc->data[i0] + a) + 1.0;
      }

      a = N - 1.0;
      for (d = 1.0; d <= a; d++) {
        M->data[((int32_T)(d + 1.0) + M->size[0] * ((int32_T)xc->data[(int32_T)d
                  - 1] - 1)) - 1] = 0.0;
      }
    } else if ((dv0[ll] <= 0.78539816339744828) || (dv0[ll] > 2.3561944901923448))
    {
      x = tan(dv0[ll]);
      a = -N / 2.0 + 1.0;
      d = N / 2.0 - 1.0;
      if (d < a) {
        n = 0;
        apnd = d;
      } else if (rtIsInf(a) || rtIsInf(d)) {
        n = 1;
        a = rtNaN;
        apnd = d;
      } else {
        ndbl = floor((d - a) + 0.5);
        apnd = a + ndbl;
        cdiff = apnd - d;
        absa = fabs(a);
        absb = fabs(d);
        if (absa > absb) {
          absb = absa;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = d;
        } else if (cdiff > 0.0) {
          apnd = a + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int32_T)ndbl;
        } else {
          n = 0;
        }
      }

      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      xc->size[1] = n;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      if (n > 0) {
        xc->data[0] = a;
        if (n > 1) {
          xc->data[n - 1] = apnd;
          nm1 = n - 1;
          nm1d2 = nm1 / 2;
          loop_ub = nm1d2 - 1;
          for (k = 1; k <= loop_ub; k++) {
            xc->data[k] = a + (real_T)k;
            xc->data[(n - k) - 1] = apnd - (real_T)k;
          }

          if (nm1d2 << 1 == nm1) {
            xc->data[nm1d2] = (a + apnd) / 2.0;
          } else {
            xc->data[nm1d2] = a + (real_T)nm1d2;
            xc->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
          }
        }
      }

      a = N / 2.0;
      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      nm1 = xc->size[0];
      nm1d2 = xc->size[1];
      loop_ub = nm1 * nm1d2 - 1;
      for (i0 = 0; i0 <= loop_ub; i0++) {
        xc->data[i0] *= x;
      }

      b_round(xc);
      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      nm1 = xc->size[0];
      nm1d2 = xc->size[1];
      loop_ub = nm1 * nm1d2 - 1;
      for (i0 = 0; i0 <= loop_ub; i0++) {
        xc->data[i0] = (xc->data[i0] + a) + 1.0;
      }

      a = N - 1.0;
      for (d = 1.0; d <= a; d++) {
        M->data[((int32_T)xc->data[(int32_T)d - 1] + M->size[0] * ((int32_T)(d +
                   1.0) - 1)) - 1] = 1.0;
      }
    } else {
      x = 1.0 / tan(dv0[ll]);
      a = -N / 2.0 + 1.0;
      d = N / 2.0 - 1.0;
      if (d < a) {
        n = 0;
        apnd = d;
      } else if (rtIsInf(a) || rtIsInf(d)) {
        n = 1;
        a = rtNaN;
        apnd = d;
      } else {
        ndbl = floor((d - a) + 0.5);
        apnd = a + ndbl;
        cdiff = apnd - d;
        absa = fabs(a);
        absb = fabs(d);
        if (absa > absb) {
          absb = absa;
        }

        if (fabs(cdiff) < 4.4408920985006262E-16 * absb) {
          ndbl++;
          apnd = d;
        } else if (cdiff > 0.0) {
          apnd = a + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        if (ndbl >= 0.0) {
          n = (int32_T)ndbl;
        } else {
          n = 0;
        }
      }

      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      xc->size[1] = n;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      if (n > 0) {
        xc->data[0] = a;
        if (n > 1) {
          xc->data[n - 1] = apnd;
          nm1 = n - 1;
          nm1d2 = nm1 / 2;
          loop_ub = nm1d2 - 1;
          for (k = 1; k <= loop_ub; k++) {
            xc->data[k] = a + (real_T)k;
            xc->data[(n - k) - 1] = apnd - (real_T)k;
          }

          if (nm1d2 << 1 == nm1) {
            xc->data[nm1d2] = (a + apnd) / 2.0;
          } else {
            xc->data[nm1d2] = a + (real_T)nm1d2;
            xc->data[nm1d2 + 1] = apnd - (real_T)nm1d2;
          }
        }
      }

      a = N / 2.0;
      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      nm1 = xc->size[0];
      nm1d2 = xc->size[1];
      loop_ub = nm1 * nm1d2 - 1;
      for (i0 = 0; i0 <= loop_ub; i0++) {
        xc->data[i0] *= x;
      }

      b_round(xc);
      i0 = xc->size[0] * xc->size[1];
      xc->size[0] = 1;
      emxEnsureCapacity((emxArray__common *)xc, i0, (int32_T)sizeof(real_T));
      nm1 = xc->size[0];
      nm1d2 = xc->size[1];
      loop_ub = nm1 * nm1d2 - 1;
      for (i0 = 0; i0 <= loop_ub; i0++) {
        xc->data[i0] = (xc->data[i0] + a) + 1.0;
      }

      a = N - 1.0;
      for (d = 1.0; d <= a; d++) {
        M->data[((int32_T)(d + 1.0) + M->size[0] * ((int32_T)xc->data[(int32_T)d
                  - 1] - 1)) - 1] = 1.0;
      }
    }
  }

  emxFree_real_T(&xc);

  /*  upper half plane mask (not including origin) */
  i0 = Mh->size[0] * Mh->size[1];
  Mh->size[0] = M->size[0];
  Mh->size[1] = M->size[1];
  emxEnsureCapacity((emxArray__common *)Mh, i0, (int32_T)sizeof(real_T));
  loop_ub = M->size[0] * M->size[1] - 1;
  for (i0 = 0; i0 <= loop_ub; i0++) {
    Mh->data[i0] = M->data[i0];
  }

  a = N / 2.0 + 2.0;
  if (a > N) {
    i0 = 1;
    k = 0;
  } else {
    i0 = (int32_T)a;
    k = (int32_T)N;
  }

  emxInit_int32_T(&r0, 1);
  n = r0->size[0];
  r0->size[0] = (k - i0) + 1;
  emxEnsureCapacity((emxArray__common *)r0, n, (int32_T)sizeof(int32_T));
  loop_ub = k - i0;
  for (k = 0; k <= loop_ub; k++) {
    r0->data[k] = i0 + k;
  }

  emxInit_int32_T(&r1, 1);
  k = r1->size[0];
  r1->size[0] = M->size[1];
  emxEnsureCapacity((emxArray__common *)r1, k, (int32_T)sizeof(int32_T));
  loop_ub = M->size[1] - 1;
  for (k = 0; k <= loop_ub; k++) {
    r1->data[k] = 1 + k;
  }

  nm1d2 = r0->size[0];
  nm1 = r1->size[0];
  emxFree_int32_T(&r1);
  emxFree_int32_T(&r0);
  loop_ub = nm1 - 1;
  for (k = 0; k <= loop_ub; k++) {
    nm1 = nm1d2 - 1;
    for (n = 0; n <= nm1; n++) {
      Mh->data[((i0 + n) + Mh->size[0] * k) - 1] = 0.0;
    }
  }

  a = N / 2.0 + 1.0;
  if (a > N) {
    i0 = 1;
    k = 0;
  } else {
    i0 = (int32_T)a;
    k = (int32_T)N;
  }

  emxInit_int32_T(&r2, 1);
  nm1d2 = (int32_T)(N / 2.0 + 1.0);
  n = r2->size[0];
  r2->size[0] = (k - i0) + 1;
  emxEnsureCapacity((emxArray__common *)r2, n, (int32_T)sizeof(int32_T));
  loop_ub = k - i0;
  for (k = 0; k <= loop_ub; k++) {
    r2->data[k] = i0 + k;
  }

  nm1 = r2->size[0];
  emxFree_int32_T(&r2);
  loop_ub = nm1 - 1;
  for (k = 0; k <= loop_ub; k++) {
    Mh->data[(nm1d2 + Mh->size[0] * ((i0 + k) - 1)) - 1] = 0.0;
  }

  for (nm1 = 0; nm1 < 2; nm1++) {
    eml_ifftshift(M, nm1 + 1);
  }

  find(M, mi);
  for (nm1 = 0; nm1 < 2; nm1++) {
    eml_ifftshift(Mh, nm1 + 1);
  }

  find(Mh, mhi);
}

/* End of code generation (LineMask_limitedangleRange.cpp) */
