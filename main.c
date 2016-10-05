#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "SVGA.h"

void main()
{
	SetSVGAMode(0x114);
	ReadBmp(0,0,"enter.bmp");
	getch();
}