#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "SVGA.h"
#include "HANZI.h"
#include "mouse.h"

void main()
{	char mouse_buffer[16*16];
	Coord mouse;
	char a;
	SetSVGAMode(0x114);
	SetScreenWidth(1600l);
	// SetShowBegin(1200,0);
	//SetScreenWidth() ;
	//PrintHZ16(400,0,"点击按键选择地图，点击地图进入预览模式",0x8972,1,1);     
	//delay(5000)      ;
	ReadBmp(0,0,"enter.bmp");
	ReadBmp(800,0,"jm3.bmp");
	SetShowBegin(400,0);
	PrintHZ16(400,0,"点击按键选择地图，点击地图进入预览模式",0x8972,1,1);
	delay(5000);
	//PrintHZ16(400,0,"点击按键选择地图，点击地图进入预览模式",0x8972,1,1); 
	
	// MouseInit();
	// SetMouseRange(0,0,600,800);
	// SetMousePositon(300,400);
	// MouseShow(&mouse);
	// while(1){
	// ReadMouse(&mouse.x,&mouse.y,&a);
	// MouseCopy(&mouse,mouse_buffer);
	// MouseShow(&mouse);
	// MouseReshow(&mouse,mouse_buffer);
	// //MouseReshow(CoordXY,mouse_buffer);
	// }
   	delay(5000);
}