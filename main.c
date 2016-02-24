#include"BMP.h"

int main(int argc,char* argv[]){
    unsigned char * fp_temp;
    int i,blur,rotate,re_h,re_w;
    double thr;
    char* temp1,* temp2;
    char temp[100],fileadd[100],fileadd2[100]="out.bmp";
    float brightness=1.0,contrast=1.0;
    FILE * filein;
    FILE * fileout;
    fileadd[0]='\0';
    for(i=0;i<argc;i++){
        if(!strcmp(argv[i],"-h")){//jump to help menu
            help();
            return 0;
        }
        //get output filename
        if(!strcmp(argv[i],"-o")) strcpy(fileadd2,argv[i+1]);
        //get input filename
    }
    temp1=argv[argc-1]+(strlen(argv[argc-1])-3);
    if (!strcasecmp(temp1,"bmp")){
        strcpy(fileadd,argv[argc-1]);
    }
    else{
        printf("You should Input the input file\n");
        help();
        return 1;
    }
    if(fileadd[0]=='\0'){
        printf("Cannot find the input file\n");
        return 1;
    }
    //input file start
    filein=fopen(fileadd,"rb");
    if(filein==NULL)
    {
        printf("Open File failed(%s)!!Please input your filename again!!\n",fileadd);
        return 1;
    }
    printf("\n%s has already been opened\n",fileadd);
//input file over
//output file start
    fileout=fopen(fileadd2,"wb+");
    if(fileout==NULL)
    {
        printf("Open out.bmp failed!!\n");
        return 1;
    }
    printf("%s has already been created\n\n",fileadd2);
//output file over
//read file
    Create_File(filein);

//save header
    fseek(filein,0,SEEK_SET);
    fseek(fileout,0,SEEK_SET);
    fp_temp=malloc(OffSet);
    fread(fp_temp,1,OffSet,filein);
    fwrite(fp_temp,1,OffSet,fileout);
//save data
    data(filein);

    printf("**********BMP Converting ********************\n");

    for(i=0;i<argc;i++){
//do Threshold filter
        if(!strcmp(argv[i],"-t")){
            if (bits!=24){

                printf("Sorry!! This commond can only work for 24 bits per pixel\n");
                continue;
            }
            strcpy(temp,argv[i+1]);
            thr=atof(temp);
            if(thr==0||thr>1||thr<0){
                printf("Threshold input ERROR!! Nothing to be done\n");
                continue;
            }
            doThreshold_filter(thr);
        }
        if(!strcmp(argv[i],"-g"))
            doGrayscale();
        if(!strcmp(argv[i],"-sr"))
            Shield_r();
        if(!strcmp(argv[i],"-sb"))
            Shield_b();
        if(!strcmp(argv[i],"-sg"))
            Shield_g();

//do filter brightness&contrast
        if(!strcmp(argv[i],"-br")){
            strcpy(temp,argv[i+1]);
            brightness=atof(temp);
            if(brightness==0||brightness>2||brightness<0){
                printf("Converting brightness: Input ERROR!!! Nothing to be done\n");
                continue;
            }
            brightness=(brightness<0)?1.0:brightness;//got brightness
            printf("Convert: Brightness  %0.2f",brightness);
            doBrightnessContrast(brightness,1.0);
        }

        if(!strcmp(argv[i],"-c")){
            strcpy(temp,argv[i+1]);
            contrast=atof(temp);
            if(contrast==0||contrast>4||contrast<0){
                printf("Converting contrast: Input ERROR!!! Nothing to be done\n");
                continue;
            }
            contrast=(contrast<0)?1.0:contrast;//got contrast
            printf("Convert: Contrast  %0.2f",contrast);
            doBrightnessContrast(1.0,contrast);
        }
//convering brightness&contrast over
//do bluring
        if(!strcmp(argv[i],"-bl")){
            strcpy(temp,argv[i+1]);
            blur=atoi(temp);
            if(blur==0){
                printf("Converting blur: Input ERROR!!! Nothing to be done\n");
                continue;
            }
            if(blur>height||blur>width||blur<=0){
                printf("Blur should between 1 and min(height,width)!!Nothing to be done\n");
                continue;
            }
            doBluring(blur);
        }
// bluring done
//doRotate
        if(!strcmp(argv[i],"-r")){
            strcpy(temp,argv[i+1]);
            rotate=atoi(temp);
            if(rotate==0){
                printf("Converting rotate: Input ERROR!!! Nothing to be done\n");
                continue;
            }
            if(rotate%90!=0){
                printf("We can only rotate image by 90/180/270/360 degrees e.t.c\n");
                continue;
            }
            rotate=(rotate/90)%4;
            doRotate(rotate,fileout);
            printf("Rotate %d degree :done.\n",atoi(temp));
        }
//reSize
        if(!strcmp(argv[i],"-s")){
            temp2=argv[i+2];
            temp1=argv[i+1];
            if (temp1[strlen(temp1)-1]=='%'){
                temp1[strlen(temp1)-1]='\0';
                re_h=(int)(atof(temp1)*height/100);
            }
            else re_h=atoi(temp1);
            if (temp2[strlen(temp2)-1]=='%'){
                temp2[strlen(temp2)-1]='\0';
                re_w=(int)(atof(temp2)*width/100);
            }
            else re_w=atoi(temp2);
            if(re_h==0||re_w==0){
                printf("Resize Input ERROR!! Nothint to be done\n");
                continue;
            }
            doResize(re_w,re_h,fileout);
        }

    }

//output file
        output(fileout);
//        break;

    printf("*********************************************\n");
    printf("Thanks for using.  Good bye!!!\n");
    printf("\t\t\t\t\tCopyright:Nanxuan Huang\n");
    fclose(filein);
    fclose(fileout);
    return 0;
}
