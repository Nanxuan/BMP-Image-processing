=================================================================
                 Project1 README.TXT file         30-MAR-2013
  



******************************************************************

**               CONTACT ME :                                   **

                 MORE INFORMATION ABOUT THE PROGRAM             

                 Nanxuan Huang

		 hnx00001@gmail.com/u5306244@anu.edu.au            

******************************************************************



CONTENTS

1. Name & UniID
2. Copyright
3. A summary of the programs working
4. How to compile and run the program
5. The tests I did
6. Optional extensions I did and what makes them deserving or a high mark
7. Limitatinos of my program and what I would do next to improve the program


==================================================================

1. Name & UniID

Author: Nanxuan Huang, UniId is u5306244
E-mail: hnx00001@gmail.com, u5306244@anu.edu.au

==================================================================

2.Copyright

Copyright by Nanxuan Huang

==================================================================

3.A summary of the programs working

About 12 hours working

==================================================================

4. How to compile and run the program

Use this commond to compile:
gcc -wall -o bmpedit bmpedit.c

Run the program:
.\bmpedit [OPTIONS...] [input.bmp]

DESCRIPTION:
      Reads header information from Windows BMP files and can apply simple image filters.
 The resulting image is also stored using BMP format into an output file

OPTIONS:
 -o FILE          Sets the output file for modified imagen(default address out.bmp)
 -t 0.0-1.0       Sets the threshold to filter the image through
 -br 0.0-2.0      Change the brightness of the image
 -c 0.0-4.0       Change the contrast of the image
 -bl 1+ INT       Blur the image(1.0 is the clearest )
 -r 90/180/etc    Rotate the image by degrees
 -g               Sets the image into a grayscale image
 -sr              Shield the Red channel of the image
 -sg              Shield the Green channel of the image
 -sb              Shield the Blue channel of the image
 -h               Displays this usage message
 -s width heigth  Resize the impage...
    ....width/height with %: resize by proportion; without %:resize by pixel      (eg.-s 20% 30 MEANS new width is 20% the old one, new height is 30px)

==================================================================

5. The tests I did

A. General tests

1).\bmpedit cup.bmp
output:
------------------------------------------------------------------
cup.bmp has already been opened
out.bmp has already been created

************BMP status***********************
The width of this file is  640
The height of this file is 480
The bpp for this file is   24
The Header offset is       54
The size of this file is   921654
The size of the data is    921600
*********************************************

**********BMP Converting ********************
Output file:done
*********************************************
Thanks for using.  Good bye!!!
					Copyright:Nanxuan Huang
-----------------------------------------------------------------

2).\bmpedit -h cup.bmp
output:
-----------------------------------------------------------------
Usage: bmpedit [OPTIONS...] [input.bmp]

DESCRIPTION:
      Reads header information from Windows BMP files and can apply simple image filters.
 The resulting image is also stored using BMP format into an output file

OPTIONS:
-o FILE          Sets the output file for modified imagen(default address out.bmp)
-t 0.0-1.0       Sets the threshold to filter the image through
-br 0.0-2.0      Change the brightness of the image
-c 0.0-4.0       Change the contrast of the image
-bl 1+ INT       Blur the image(1.0 is the most clear )
-r 90/180/etc    Rotate the image by degrees
-g               Sets the image into a grayscale image
-sr              Shield the Red Channel of the image
-sg              Shield the Green Channel of the image
-sb              Shield the Blue Channel of the image
-h               Displays this usage message
-s width heigth  Resize the impage...
....width/height with %: resize by proportion; without %:resize by pixel
(eg.-s 20% 30 MEANS new width is 20% the old one, new height is 30px)
---------------------------------------------------------------------

3).\bmpedit -o out1.bmp cup.bmp
output:(and the result would be import into a bmpfile called out1.bmp)
---------------------------------------------------------------------
cup.bmp has already been opened
out1.bmp has already been created

************BMP status***********************
The width of this file is  640
The height of this file is 480
The bpp for this file is   24
The Header offset is       54
The size of this file is   921654
The size of the data is    921600
*********************************************

**********BMP Converting ********************
Output file:done
*********************************************
Thanks for using.  Good bye!!!
					Copyright:Nanxuan Huang

---------------------------------------------------------------------

3).\bmpedit           \*input without a file name*\
output:(a input error tips along with the help menu)
---------------------------------------------------------------------
You should Input the input file

Usage: bmpedit [OPTIONS...] [input.bmp]

DESCRIPTION:
      Reads header information from Windows BMP files and can apply simple image filters.
 The resulting image is also stored using BMP format into an output file

OPTIONS:
-o FILE          Sets the output file for modified imagen(default address out.bmp)
-t 0.0-1.0       Sets the threshold to filter the image through
-br 0.0-2.0      Change the brightness of the image
-c 0.0-4.0       Change the contrast of the image
-bl 1+ INT       Blur the image(1.0 is the most clear )
-r 90/180/etc    Rotate the image by degrees
-g               Sets the image into a grayscale image
-sr              Shield the Red Channel of the image
-sg              Shield the Green Channel of the image
-sb              Shield the Blue Channel of the image
-h               Displays this usage message
-s width heigth  Resize the impage...
....width/height with %: resize by proportion; without %:resize by pixel
(eg.-s 20% 30 MEANS new width is 20% the old one, new height is 30px)

---------------------------------------------------------------------

4)./bmpedit sdlfjsdlk.bmp/*input a wrong filename*/
output:
---------------------------------------------------------------------
Open File failed(sdlfjsdlk.bmp)!!Please input your filename again!!
---------------------------------------------------------------------

B. -t tests

1) ./bmpedit -t 0.5 cup.bmp
output:(the output file is already applied the threshold)
---------------------------------------------------------------------
cup.bmp has already been opened
out.bmp has already been created

************BMP status***********************
The width of this file is  560
The height of this file is 340
The bpp for this file is   24
The Header offset is       54
The size of this file is   571254
The size of the data is    571200
*********************************************

**********BMP Converting ********************
Threshold Filter 0.50 :done.
Output file:done
*********************************************
Thanks for using.  Good bye!!!
					Copyright:Nanxuan Huang
--------------------------------------------------------------------

2)./bmpedit -t cup.bmp(input without the parameter of the -t)
output:(just ignore the -t)
--------------------------------------------------------------------
**********BMP Converting ********************
Threshold input ERROR!! Nothing to be done
Output file:done
*********************************************
--------------------------------------------------------------------

3)./bmpedit -t 100(illegal input)
--------------------------------------------------------------------
**********BMP Converting ********************
Threshold input ERROR!! Nothing to be done
Output file:done
*********************************************
--------------------------------------------------------------------

C. -br -c test

1)./bmpedit -br 2 -c 3 cup.bmp

output:(the output file is already applied the brightness and contract changing)
**********BMP Converting ********************
Convert: Brightness  2.00:done.
Convert: Contrast  3.00:done.
Output file:done.
*********************************************

2)./bmpedit -br 100 -c s(illegal input)
output:
**********BMP Converting ********************
Converting brightness: Input ERROR!!! Nothing to be done
Converting contrast: Input ERROR!!! Nothing to be done
Output file:done.
*********************************************

D.-bl test

1)./bmpedit -bl 2 cup.bmp
output:(the blur changing is already applied)
**********BMP Converting ********************
Bluring 2 :done.
Output file:done.
*********************************************

2)./bmpedit -bl sssss cup.bmp(illegal input)
output:
**********BMP Converting ********************
Converting blur: Input ERROR!!! Nothing to be done
Output file:done.
*********************************************

3)./bmpedit -bl 10000 cup.bmp(really large number)
output:
**********BMP Converting ********************
Blur should between 1 and min(height,width)!!Nothing to be done
Output file:done.
*********************************************

E.-r test
1)./bmpedit -r 90 cup.bmp
output:(the image was rotated by 90 degree)
**********BMP Converting ********************
Rotate 90 degree :done.
Output file:done.
*********************************************

2)./bmpedit -r slkdfj -r 89 cup.bmp
**********BMP Converting ********************
Converting rotate: Input ERROR!!! Nothing to be done
We can only rotate image by 90/180/270/360 degrees e.t.c
Output file:done.
*********************************************

F. -g -sr -sg -sb test
1)./bmpedit -g cup.bmp
output:
**********BMP Converting ********************
Grayscale :done.
Output file:done.
*********************************************

2)./bmpedit -sg cup.bmp
output:
**********BMP Converting ********************
Green channel shield :done.
Output file:done.
*********************************************

G.-s test
1)./bmpedit -s 20% 30% cup.bmp
output:(resize by proportion)
**********BMP Converting ********************
Resize: New size 96*192 :done.
Output file:done.
*********************************************

2)./bmpedit -s 20 30 cup.bmp
output:(resize by pixel)
**********BMP Converting ********************
Resize: New size 20*30 :done.
Output file:done.
*********************************************

3)./bmpedit -s 20 30% cup.bmp
output:
**********BMP Converting ********************
Resize: New size 20*192 :done.
Output file:done.
*********************************************
4)./bmpedit -s sdoif sdkfj cup.bmp /*illegal input*/
output:
**********BMP Converting ********************
Resize Input ERROR!! Nothint to be done
Output file:done.
*********************************************

==================================================================

6. Optional extensions I did and what makes them deserving a high mark

1) Add another image filter:

	a) Brightness filter: it can convert brightness from 0.0-2.0(0.0 is the darkest)
	b) Contrast filter: it can convert contrast form 0.0-4.0
	c) Blur filter: it can convert blur by steps (1 is the clearest)

2) Add an image rotate(by degrees) options

	Can only rotate the image by the integer times of 90 degrees(90/180/270/360 etc.)

3) Add an image resize option. 

	Can resize the BMP by proportion or by pixels.

4) Add a grayscale filter:

	Sets the image into a grayscale image

5) Shield the color channel of the image

	Shield Red/Green/Blue Channel of the image

Advantage:

	Multiple features:
		Providing multiple and useful filters. Can do different filters in one command whatever the sequence. 

	High robustness:
		Through the robustness test. Can do some reflects towards inputs errors. And once a filter is error, the system will just ignore this filter and do the next filter. 
	
	High reliability:
		Can do the filters exactly you want without any mistakes.

==================================================================
	

7. Limitations of my program and what I would do next to improve the program

The program can only do filters for BMP files. I can do something to make it work for other formats. 
The program cannot display the image and I can make it work by using <graphs.h>


==================================================================
copyright by Nanxuan Huang
