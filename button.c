#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "button.h"
#include "SVGA.h"
#include "mouse.h"



/**********************************************************************
	功能说明：判断鼠标是否点击了指定区域
	参数说明：int x1, int y1, int x2, int y2 为矩形区域的左上和右下坐标
	返回值说明：若鼠标是否点击了指定区域，返回 1，否则返回 0
*********************************************************************/
int Button(int x1,int y1,int x2,int y2)
{
	int mouse_x,mouse_y;
	char mouse_butt;
	ReadMouse(&mouse_x,&mouse_y,&mouse_butt);
	if((mouse_x >= x1) &&(mouse_x <= x2) && (mouse_y > y1) &&(mouse_y < y2)&&(mouse_butt==1))
	{
		return 1;
	}else{
		return 0;
	}
}

