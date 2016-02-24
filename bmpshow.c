#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "display.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

/*

bmpshow - very simple bmp image viewer.

Eric McCreath 2013
 
To compile:
gcc display.c bmpshow.c -lglut -lGLU -o bmpshow
Run with cup.bmp in the same directory:
./bmpshow


*/

void error(char str[]) {
   printf ("Error : %s\n",str);
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
    int fd;
    unsigned char *data;

    fd = open("cup.bmp", O_RDONLY);  // open the cup.bmp for reading
    if (fd == -1) error("problem opening file");

    data = mmap(NULL,921654,PROT_READ, MAP_PRIVATE,fd,0);  // mmap the cup.bmp file.  Note the 921654 is the file size and obtained form ls -l
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
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    setupdisplay(XDIM,YDIM);
    loadimage();
    glutDisplayFunc(display);
    glutMainLoop();  // this never returns !!
    return 0;
}
