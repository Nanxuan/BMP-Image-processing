#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define FileHeaderLength 14
#define BMP 19778

    int width,height,OffSet,sizeHead,sizeall;
    short bits;
    unsigned char r[2000][2000],out_r[2000][2000];
    unsigned char g[2000][2000],out_g[2000][2000];
    unsigned char b[2000][2000],out_b[2000][2000];
    void help(){
        printf("\nUsage: bmpedit [OPTIONS...] [input.bmp]\n");
        printf("\nDESCRIPTION:\n");
        printf("      Reads header information from Windows BMP files and can apply simple image filters.\n");
        printf(" The resulting image is also stored using BMP format into an output file\n");
        printf("\nOPTIONS:\n");
        printf("-o FILE          Sets the output file for modified imagen(default address out.bmp)\n");
        printf("-t 0.0-1.0       Sets the threshold to filter the image through\n");
        printf("-br 0.0-2.0      Change the brightness of the image\n");
        printf("-c 0.0-4.0       Change the contrast of the image\n");
        printf("-bl 1+ INT       Blur the image(1.0 is the most clear )\n");
        printf("-r 90/180/etc    Rotate the image by degrees\n");
        printf("-g               Sets the image into a grayscale image\n");
        printf("-sr              Shield the Red Channel of the image\n");
        printf("-sg              Shield the Green Channel of the image\n");
        printf("-sb              Shield the Blue Channel of the image\n");
        printf("-h               Displays this usage message\n");
        printf("-s width heigth  Resize the image...\n");
        printf("....width/height with %%: resize by proportion; without %%:resize by pixel\n(eg.-s 20%% 30 MEANS new width is 20%% the old one, new height is 30px)\n");
    }
    int clamp (int value){
        if(value>255) return 255;
        if(value<0) return 0;
        return value;
    }
//create file and using get the data in the header
    void Create_File(FILE* file){
        int type=0;
        fseek(file,0,SEEK_SET);
        fread(&type,sizeof(char),2,file);
//test whether the file is a BMP file or not
        if(BMP!=type){
            printf("This File is not BMP file!!!\n");
            exit(0);
        }
//get the length of the header part
        fseek(file,10,SEEK_SET);
        fread(&OffSet,sizeof(char),4,file);
//get the width and the height of the file
        fseek(file,18,SEEK_SET);
        fread(&width,sizeof(char),4,file);
        fseek(file,22,SEEK_SET);
        fread(&height,sizeof(char),4,file);

        fseek(file,2,SEEK_SET);
        fread(&sizeall,sizeof(char),4,file);
        fseek(file,34,SEEK_SET);
        fread(&sizeHead,sizeof(char),4,file);

        fseek(file,28,SEEK_SET);
        fread(&bits,sizeof(char),2,file);
        printf("************BMP status***********************\n");
        printf("The width of this file is  %d\n",width);
        printf("The height of this file is %d\n",height);
        printf("The bpp for this file is   %d\n",bits);
        printf("The Header offset is       %d\n",OffSet);
        printf("The size of this file is   %d\n",sizeall);
        printf("The size of the data is    %d\n",sizeHead);
        printf("*********************************************\n\n");
    }

    void data(FILE* bmpbmp){
        int i, j=0;
        int stride;
        unsigned char* pix=NULL;
        fseek(bmpbmp, OffSet, SEEK_SET);
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pix=malloc(stride);
        for(i=0;i<height;i++){
            fread(pix, 1, stride, bmpbmp);
            for(j=0;j<width;j++){
                r[i][j]=pix[j*3+2];
                g[i][j]=pix[j*3+1];
                b[i][j]=pix[j*3];
                out_r[i][j]=pix[j*3+2];
                out_g[i][j]=pix[j*3+1];
                out_b[i][j]=pix[j*3];
            }
        }
    }
    void output(FILE* fileout){
        int stride,i=0,j=0;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        fseek(fileout,OffSet,SEEK_SET);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                pixout[j*3+2]=out_r[i][j];
                pixout[j*3+1]=out_g[i][j];
                pixout[j*3]=out_b[i][j];
            }
            fwrite(pixout,1,stride,fileout);
        }
	printf("Output file:done.\n");

    }
//doThreshold option
    void doThreshold_filter(float thr){
        int stride,i=0,j=0;
        float average;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                average=(r[(int)i][j]/255.0+g[i][j]/255.0+b[i][j]/255.0)/3;
                if(average>thr)
                    r[i][j]=g[i][j]=b[i][j]=out_r[i][j]=out_g[i][j]=out_b[i][j]=255;
                else
                    r[i][j]=g[i][j]=b[i][j]=out_r[i][j]=out_g[i][j]=out_b[i][j]=0;
            }
        }
        printf("Threshold Filter %0.2f :done.\n",thr);
   //     printf("%d\n",average);
    }
//convert the image into grayscale
    void doGrayscale(){
        int stride,i=0,j=0;
        int lumin;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                lumin=r[i][j]*0.3+g[i][j]*0.59+b[i][j]*0.11;
                r[i][j]=g[i][j]=b[i][j]=r[i][j]=out_r[i][j]=out_g[i][j]=out_b[i][j]=lumin;
            }
        }
        printf("Grayscale :done.\n");
    }
//do brightness and contrast change
    void doBrightnessContrast(float brightness,float contrast){
        int stride,i,j,rmean=0,gmean=0,bmean=0,rt,gt,bt;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                rmean+=r[i][j];
                gmean+=g[i][j];
                bmean+=b[i][j];
            }
        }
        rmean=rmean/(width*height);
        gmean=gmean/(width*height);
        bmean=bmean/(width*height);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                rt=out_r[i][j];
                gt=out_g[i][j];
                bt=out_b[i][j];
                rt=(int)((rt-rmean)*contrast)+(int)(rmean*brightness);
                gt=(int)((gt-gmean)*contrast)+(int)(gmean*brightness);
                bt=(int)((bt-bmean)*contrast)+(int)(bmean*brightness);
                r[i][j]=out_r[i][j]=clamp(rt);
                g[i][j]=out_g[i][j]=clamp(gt);
                b[i][j]=out_b[i][j]=clamp(bt);
            }
        }
        printf(":done.\n");

    }
//add mosaic
    void doBluring(int step){
        int stride,i=0,j=0,k,l;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i+=step){
            for(j=0;j<width;j+=step)
                for(k=i;k<i+step;k++)
                    for(l=j;l<j+step;l++){
                        r[k][l]=out_r[k][l]=r[i][j];
                        g[k][l]=out_g[k][l]=g[i][j];
                        b[k][l]=out_b[k][l]=b[i][j];
                    }
        }
        printf("Bluring %d :done.\n",step);
    }
//rotate the image
    void doRotate(int degree,FILE*fileout){
        int stride,i=0,j=0,temp;
        unsigned char* pixout=NULL;
        if(degree==1||degree==3){
            fseek(fileout,18,SEEK_SET);
            fwrite(&height,sizeof(char),4,fileout);
            fseek(fileout,22,SEEK_SET);
            fwrite(&width,sizeof(char),4,fileout);
            temp=height;height=width;width=temp;
        }
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        if(degree==2)
            for(i=0;i<height;i++)
                for(j=0;j<width;j++){
                    out_r[height-1-i][j]=r[i][j];
                    out_g[height-1-i][j]=g[i][j];
                    out_b[height-1-i][j]=b[i][j];
                }
        if(degree==1)
            for(i=0;i<height;i++)
                for(j=0;j<width;j++){
                    out_r[i][j]=r[j][i];
                    out_g[i][j]=g[j][i];
                    out_b[i][j]=b[j][i];
                }
        if(degree==3)
            for(i=0;i<height;i++)
                for(j=0;j<width;j++){
                    out_r[i][j]=r[width-1-j][i];
                    out_g[i][j]=g[width-1-j][i];
                    out_b[i][j]=b[width-1-j][i];
                }
        for(i=0;i<height;i++)
                for(j=0;j<width;j++){
                    r[i][j]=out_r[i][j];
                    b[i][j]=out_b[i][j];
                    g[i][j]=out_g[i][j];
                }
    }
//change the size using proportion or size
    void doResize(int re_height,int re_width,FILE*fileout){
        int stride,i=0,j=0;
        float coe_h=(float)height/re_height,coe_w=(float)width/re_width;
        unsigned char* pixout=NULL;
        fseek(fileout,18,SEEK_SET);
        fwrite(&re_width,sizeof(char),4,fileout);
        fseek(fileout,22,SEEK_SET);
        fwrite(&re_height,sizeof(char),4,fileout);
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        height=re_height;
        width=re_width;
        for(i=0;i<height;i++)
            for(j=0;j<width;j++){
                out_r[i][j]=r[(int)(i*coe_h)][(int)(j*coe_w)];
                out_g[i][j]=g[(int)(i*coe_h)][(int)(j*coe_w)];
                out_b[i][j]=b[(int)(i*coe_h)][(int)(j*coe_w)];
            }
         for(i=0;i<height;i++)
            for(j=0;j<width;j++){
                r[i][j]=out_r[i][j];
                g[i][j]=out_g[i][j];
                b[i][j]=out_b[i][j];
            }
        printf("Resize: New size %d*%d :done.\n",width,height);

    }
//convert image into single channel image
    void Shield_r(){
        int stride,i=0,j=0;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                r[i][j]=out_r[i][j]=0;
            }
        }
        printf("Red channel shield :done.\n");
    }
    void Shield_g(){
        int stride,i=0,j=0;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                g[i][j]=out_g[i][j]=0;
            }
        }
        printf("Green channel shield :done.\n");
    }
    void Shield_b(){
        int stride,i=0,j=0;
        unsigned char* pixout=NULL;
        stride=(bits*width+31)/8;
        stride=stride/4*4;
        pixout=malloc(stride);
        for(i=0;i<height;i++){
            for(j=0;j<width;j++){
                b[i][j]=out_b[i][j]=0;
            }
        }
        printf("Blue channel shield :done.\n");
    }




#endif // BMP_H_INCLUDED
