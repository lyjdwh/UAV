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
	����˵�����ж�����Ƿ�����ָ������
	����˵����int x1, int y1, int x2, int y2 Ϊ������������Ϻ���������
	����ֵ˵����������Ƿ�����ָ�����򣬷��� 1�����򷵻� 0
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

