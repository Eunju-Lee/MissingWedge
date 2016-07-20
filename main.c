
// IDE code::block
// Compiler : GCC 3.4.5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include    <time.h>
#include    <unistd.h>

#include "include/png.h"     //png library
#include "include/pngconf.h"

#include "opencv/cv.h"
#include "opencv/highgui.h"
//#include "zlib128/include/zlib.h"

//#include "extern/enhance/enhance.h" //enhance library

#define     ERROR    -1

typedef unsigned char   uch;
typedef unsigned short  ush;
typedef unsigned int    uln;
typedef unsigned long   ulg;



int main()
{
    printf("Hello world!\n");


    int n = 256;
    int m = 256;
    int N = n*m;

    /*
    *********************************************************************
      Read the .png image
      matlab code : iFile = './input/sample02.png';
                    fprintf('\nreading file: %s', iFile);
                    I = imread(iFile);

      reference : http://www.libpng.org/pub/png/book/chapter13.html
     ********************************************************************
    */

    #if 0
    FILE *infile;
    uch sig[8];
    png_structp    png_ptr = NULL;
    png_infop      info_ptr = NULL;

    png_uint_32    ihdr_width, ihdr_height;
    int            width, height;
    int            bit_depth, color_type;
    png_color_16p  pBackground;

    uch            bg_red =0, bg_green=0, bg_blue=0;
    uch           *image_data = NULL;
    int            image_channels, image_rowbytes;
    double         display_exponent  = 1.0 * 2.2;

    double         gamma;
    png_uint_32    rowbytes;
    png_bytepp     row_pointers = NULL;
    int            i;

    infile = fopen("sample.png", "rb");
    fread(sig, 1, 8, infile);

    if( !png_check_sig(sig,8)) printf("bed\n");
    else
    {
      png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
      if ( !png_ptr)    printf( "out of memory\n");
      else
      {
          info_ptr = png_create_info_struct( png_ptr);
         if (!png_ptr)     printf( "out of memory\n");
         else
         {
            if ( setjmp( png_jmpbuf(png_ptr)))
            {
               png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
               printf( "for bad IHDR");
            }
            else
            {
               png_init_io( png_ptr, infile);
               png_set_sig_bytes( png_ptr, 8);                                   // we already read the 8 signature bytes
               png_read_info( png_ptr, info_ptr);                                // read all PNG info up to image data

               /* alternatively, could make separate calls to png_get_image_width(),
                * etc., but want bit_depth and color_type for later [don't care about
                * compression_type and filter_type => NULLs] */

               png_get_IHDR(png_ptr, info_ptr, &ihdr_width, &ihdr_height, &bit_depth, &color_type, NULL, NULL, NULL);
               width    = ihdr_width;
               height   = ihdr_height;
               printf( "width     = %u\n", width      );
               printf( "height    = %u\n", height     );
               printf( "bit depth = %d\n", bit_depth  );
               printf( "color type= %d\n", color_type );

               if ( setjmp(png_jmpbuf( png_ptr))) {
                   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
                   printf( "libpng error\n");
               }
               else
               {

                  {
                    png_get_bKGD(png_ptr, info_ptr, &pBackground);

                      /* however, it always returns the raw bKGD data, regardless of any
                       * bit-depth transformations, so check depth and adjust if necessary */

                      if ( bit_depth == 16)
                      {
                          bg_red   = pBackground->red   >> 8;
                          bg_green = pBackground->green >> 8;
                          bg_blue  = pBackground->blue  >> 8;
                      }
                      else if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                      {
                          if (bit_depth == 1)
                              bg_red = bg_green = bg_blue = pBackground->gray? 255 : 0;
                          else if (bit_depth == 2)
                              bg_red = bg_green = bg_blue = (255/3) * pBackground->gray;
                          else /* bit_depth == 4 */
                              bg_red = bg_green = bg_blue = (255/15) * pBackground->gray;
                      }
                      else
                      {
                          bg_red   = (uch)pBackground->red;
                          bg_green = (uch)pBackground->green;
                          bg_blue  = (uch)pBackground->blue;
                      }

                     //  Read the image data

                     /* setjmp() must be called in every function that calls a PNG-reading
                      * libpng function */

                     if (setjmp(png_jmpbuf(png_ptr)))
                     {
                         png_destroy_read_struct( &png_ptr, &info_ptr, NULL);
                         printf( "ERROR: setjmp(png_jmpbuf(png_ptr)\n");
                     }
                     else
                     {
                        /* expand palette images to RGB, low-bit-depth grayscale images to 8 bits,
                         * transparency chunks to full alpha channel; strip 16-bit-per-sample
                         * images to 8 bits per sample; and convert grayscale to RGB[A] */

                        if (color_type == PNG_COLOR_TYPE_PALETTE)
                            png_set_expand(png_ptr);
                        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
                            png_set_expand(png_ptr);
                        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
                            png_set_expand(png_ptr);
                        if (bit_depth == 16)
                            png_set_strip_16(png_ptr);
                        if (color_type == PNG_COLOR_TYPE_GRAY ||
                            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                            png_set_gray_to_rgb(png_ptr);


                        /* unlike the example in the libpng documentation, we have *no* idea where
                         * this file may have come from--so if it doesn't have a file gamma, don't
                         * do any correction ("do no harm") */

                        if (png_get_gAMA(png_ptr, info_ptr, &gamma))
                            png_set_gamma(png_ptr, display_exponent, gamma);


                        /* all transformations have been registered; now update info_ptr data,
                         * get rowbytes and channels, and allocate image memory */

                        png_read_update_info(png_ptr, info_ptr);

                        image_rowbytes = rowbytes = png_get_rowbytes(png_ptr, info_ptr);
                        image_channels = (int)png_get_channels(png_ptr, info_ptr);

                        if ( (image_data = (uch *)malloc(rowbytes*height)) == NULL)
                        {
                            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
                            printf( "error: image_data = malloc(rowbytes*height)\n");
                        }
                        else
                        {
                           if ( (row_pointers = (png_bytepp)malloc(height*sizeof( png_bytep))) == NULL)
                           {
                               png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
                               free(image_data);
                               printf( "error: row_pointer = malloc(height*sizeof(png_bytep)\n");
                           }
                           else
                           {
                              printf( "readpng_get_image:\n");
                              printf( "  channels = %d\n" , image_channels);
                              printf( "  rowbytes = %ld\n", rowbytes);
                              printf( "  height   = %d\n" , height  );

                              /* set the individual row_pointers to point at the correct offsets */

                              for (i = 0;  i < height; i++)
                                  row_pointers[i] = image_data + i*rowbytes;

                              /* now we can go ahead and just read the whole image */

                              png_read_image( png_ptr, row_pointers);

                              /* and we're done!  (png_read_end() can be omitted if no processing of
                               * post-IDAT text/time/etc. is desired) */

                              free( row_pointers);
                              row_pointers = NULL;

                              png_read_end( png_ptr, NULL);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
    }
    #endif // 1


    /*
    ***********************************************************

        Converts the matrix A to the intensity image I

        matlab code : org = mat2gray(I);

    ***********************************************************
    */

    #if 0

    uch minValue = 2;
    uch maxValue = 200;
    uch *I = (image_data - minValue) * 255 / (maxValue - minValue);

    #endif // 1


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
                      m_gamma  = 1.0;       % 변수1
                      m_beta   = 10;        % 변수2
                      m_tol    = 1e-10;     % stopping tolerance based on relative change
                      [U]      = enhance(org, n, m_iter, m_gamma, m_beta, m_tol, m_aTV, m_aL1);

    *********************************************************
    */

    #if 0
    double m_aTV = 1e-4;
    double m_aL1 = 1e-6;
    double m_iter = 500;
    double m_gamma = 1.0;
    double m_beta = 10;
    double m_tol=1e-10;

    uint8_T **enhanceImage;

    /*test image_data*/
    uint8_T *image_data;

    int i;
    for(i=0; i<65536; i++)
    {
            image_data[i] = 0;
    }


    //enhanceImage = enhance(image_data, 256, m_iter, m_gamma, m_beta, m_tol, m_aTV, m_aL1);


    #endif // 1

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

        write_png_file();

    #endif // 0


   // fclose(infile);
    return 0;

}



# if 0

void read_png_file(char *filename) {

  int width, height;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep *row_pointers;

  FILE *fp = fopen(filename, "rb");

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png) abort();

  png_infop info = png_create_info_struct(png);
  if(!info) abort();

  if(setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  png_read_info(png, info);

  width      = png_get_image_width(png, info);
  height     = png_get_image_height(png, info);
  color_type = png_get_color_type(png, info);
  bit_depth  = png_get_bit_depth(png, info);

  // Read any color_type into 8bit depth, RGBA format.
  // See http://www.libpng.org/pub/png/libpng-manual.txt

  if(bit_depth == 16)
    png_set_strip_16(png);

  if(color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);

  // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
  if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);

  if(png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // These color_type don't have an alpha channel then fill it with 0xff.
  if(color_type == PNG_COLOR_TYPE_RGB ||
     color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_PALETTE)
    png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

  if(color_type == PNG_COLOR_TYPE_GRAY ||
     color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    png_set_gray_to_rgb(png);

  png_read_update_info(png, info);

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

  int y;
  for(y = 0; y < height; y++) {
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
  }

  png_read_image(png, row_pointers);

  fclose(fp);
}

void write_png_file(char *filename) {
  int y;

  FILE *fp = fopen(filename, "wb");
  if(!fp) abort();

  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) abort();

  png_infop info = png_create_info_struct(png);
  if (!info) abort();

  if (setjmp(png_jmpbuf(png))) abort();

  png_init_io(png, fp);

  // Output is 8bit depth, RGBA format.
  png_set_IHDR(
    png,
    info,
    width, height,
    8,
    PNG_COLOR_TYPE_RGBA,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT,
    PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
  // Use png_set_filler().
  //png_set_filler(png, 0, PNG_FILLER_AFTER);

  png_write_image(png, row_pointers);
  png_write_end(png, NULL);

  for(int y = 0; y < height; y++) {
    free(row_pointers[y]);
  }
  free(row_pointers);

  fclose(fp);
}

void process_png_file() {
  for(int y = 0; y < height; y++) {
    png_bytep row = row_pointers[y];
    for(int x = 0; x < width; x++) {
      png_bytep px = &(row[x * 4]);
      // Do something awesome for each pixel here...
      //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
    }
  }
}
#endif
