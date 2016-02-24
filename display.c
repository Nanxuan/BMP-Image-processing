/*
 
Copyright Eric C. McCreath 2012  <ericm@cs.anu.edu.au>

This file is part of the clapper-webcam-recorder project.

clapper-webcam-recorder is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

clapper-webcam-recorder is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with clapper-webcam-recorder.  If not, see <http://www.gnu.org/licenses/>.

 */



       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fcntl.h>             
#include <unistd.h>

#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>          

#include <sys/time.h>


#include <GL/glut.h>
#include <GL/glu.h>

#include <math.h>

#include <time.h>


#include "display.h"


unsigned char *texturebuf;
GLuint texturename;
int xdim, ydim;

// set a color in the texture
void setcolorRGB(int x, int y, unsigned char r, unsigned char g,unsigned char b) {
    texturebuf[3*(y*xdim + x) + 0] = r;  
    texturebuf[3*(y*xdim + x) + 1] = g;  
    texturebuf[3*(y*xdim + x) + 2] = b;  
}



// set up the display - this uses glut and opengl
void setupdisplay (int x, int y) {
    xdim = x;
    ydim = y; 
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(xdim,ydim);
    glutCreateWindow("ClapperWebCam - Recorder");
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (0.0,xdim,0.0,ydim);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    texturebuf = (unsigned char *) malloc(xdim * ydim * 3);
    glGenTextures(1, &texturename);
    glBindTexture( GL_TEXTURE_2D, texturename ); 
}



// draw a rectangle with the image as the texture on it
void drawtexture(void) {          
    glBindTexture( GL_TEXTURE_2D, texturename );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, xdim, ydim, 0, GL_RGB, GL_UNSIGNED_BYTE, texturebuf);

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    
    glTexCoord2d(0.0,1.0);
    glVertex2f(0.0f,0.0f);
    
    glTexCoord2d(1.0,1.0);
    glVertex2f(xdim,0.0f);
    
    glTexCoord2d(1.0,0.0);
    glVertex2f(xdim,ydim);
    
    glTexCoord2d(0.0,0.0);
    glVertex2f(0.0f,ydim);
  
    glEnd();      
}


