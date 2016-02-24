#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "display.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
 #include <string.h>
/*

bmpgray - very simple program to make bmp files gray.

Eric McCreath 2013
 
To compile:
gcc display.c bmpgray.c -lglut -lGLU -o bmpgray
Run with cup.bmp in the same directory:
./bmpgray -b 1.2 outfile


*/

#define CUPSIZE 921654

double bright = 1.0;
char *outfile;


void error(char str[]) {
   printf ("Error : %s\n",str);
   exit(1);
}

void usage() {
   printf ("Usage : bmpgray [-b brightvalue] [outfile]\n");
 printf ("   default brightvalue is 1.0, default outfile is cupout.bmp\n");


   exit(1);
}

void display(void) {
    drawtexture();
    glFlush(); 
    glutSwapBuffers();
}

#define XDIM 640
#define YDIM 480

void loadimage() {
    int i,j;
    int fd, fdo;
    unsigned char *data, *datao;

    fd = open("cup.bmp", O_RDONLY);  // open the cup.bmp for reading
    if (fd == -1) error("problem opening file");

    data = mmap(NULL,CUPSIZE,PROT_READ, MAP_PRIVATE,fd,0);  // mmap the cup.bmp file.  Note the 921654 is the file size and obtained form ls -l
    if (data == MAP_FAILED) error("mmap problem");    

    printf ("%c%c\n",data[0],data[1]);

    int pos = data[10] | data[11] << 8 | data[12] << 16 | data[13] << 24;  // the offset in the header starts at offset 10
    printf ("pixeloffset : %d\n", pos);

    for (i=0;i<XDIM;i++) {  // set every pixel in the image based on bytes from the bmp file.
       for (j=0;j<YDIM;j++) {
           setcolorRGB(i, YDIM - j, data[pos + i*3 + j*XDIM*3 + 2], 
                                    data[pos + i*3 + j*XDIM*3 + 1], 
                                    data[pos + i*3 + j*XDIM*3 ]);   // note this striding will not work if the width is not a multiple of 4.
       }
    }

    fdo = open(outfile, O_RDWR|O_TRUNC|O_CREAT,00666);  // open and create the file
    if (fdo == -1) error("problem opening output file");
    if (ftruncate(fdo,CUPSIZE) != 0) error("problem truncating file");

    datao = mmap(NULL,CUPSIZE,PROT_READ|PROT_WRITE, MAP_SHARED,fdo,0); 

    memcpy(datao,data,CUPSIZE);

    double avg;
    int capped;

    for (i=0;i<XDIM;i++) {  // work out the average of every pixel
       for (j=0;j<YDIM;j++) {
           avg = bright * (data[pos + i*3 + j*XDIM*3 + 2] +  
                           data[pos + i*3 + j*XDIM*3 + 1] + 
                           data[pos + i*3 + j*XDIM*3 ])/3.0;
           
           capped = (int) (avg<255.0 ? avg : 255);
         
   
           datao[pos + i*3 + j*XDIM*3 + 2] = capped;
           datao[pos + i*3 + j*XDIM*3 + 0] = capped;
           datao[pos + i*3 + j*XDIM*3 + 1] = capped;
       }
    }

    for (i=0;i<XDIM;i++) {  // set every pixel in the image based on bytes from the bmp file.
       for (j=0;j<YDIM;j++) {
           setcolorRGB(i, YDIM - j, datao[pos + i*3 + j*XDIM*3 + 2], 
                                    datao[pos + i*3 + j*XDIM*3 + 1], 
                                    datao[pos + i*3 + j*XDIM*3 ]);   // note this striding will not work if the width is not a multiple of 4.
       }
    }
    munmap(datao,CUPSIZE);
    munmap(data,CUPSIZE);
    close(fd);
    close(fdo);

}


int main(int argc, char **argv) {
    outfile = "cupout.bmp";
           // parse the arguments
    int pos = 1;  
    while (pos < argc) {
        if (strcmp(argv[pos],"-b") == 0) {
            pos++;
            if (pos > argc) usage();
            if (sscanf(argv[pos], "%lf", &bright) != 1) usage();
            pos++;
        } else if (pos == (argc-1)) {
            outfile = argv[pos];
            pos++;
        } else {
            usage();
        }
    }

    glutInit(&argc, argv);
    setupdisplay(XDIM,YDIM);
    loadimage();
    glutDisplayFunc(display);
    glutMainLoop();  // this never returns !!
    return 0;
}
