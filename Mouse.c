#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

#include "SVGA.h"
#include "mouse.h"

int mouse_save[16][16] ;  	/*用于保存鼠标即将覆盖的区域*/
int mouse_dot[16][16]=   	//设计鼠标的形状,其中1:表示鼠标的区域,2:表示鼠标边界所包围的区域的边界,0:表示鼠标以外的区域  
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,//0x00,0x00,
		0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,//0x30,0x00,
		0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,//0x48,0x00,
		0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,//0x48,0x00,
		0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,//0x78,0x00,
		0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,//0x78,0x00,
		0,2,1,1,2,0,0,0,0,0,0,0,0,0,0,0,//0x78,0x00,
		0,2,1,1,2,0,2,2,0,2,2,0,2,2,0,0,//0x7B,0x6C,
		0,2,1,1,2,2,2,2,2,2,1,2,2,2,0,0,//0x7F,0xFE,
		0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,//0x7F,0xFE,
		0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,//0x7F,0xFE,
		0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,//0x7F,0xFE,
		0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,//0x7F,0xFE,
		0,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,//0x7F,0xFE,
		0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,//0x3F,0xFE,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 //0x00,0x00
	};


/*************************************8
	功能说明：初始化鼠标，并设置鼠标移动范围
	函数说明：wu
	返回值说明：无返回值
****************************/
void MouseInit(void)
{
	union REGS regs;
	int retcode;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		ReturnMode();
		printf("mouse driver is not installed \n");
		getch();
		exit(1);

	}
}

/**********************************************************************
	功能说明：设置鼠标移动范围；
	参数说明：int left,int top,int right,int bottom分别为左上右下坐标
	返回值说明：无
*********************************************************************/
void SetMouseRange(int left,int top,int right,int bottom)
{
	union REGS regs;
    regs.x.ax=7;
    regs.x.cx=left;
    regs.x.dx=right-16;
    int86(51,&regs,&regs);
    regs.x.ax=8;
    regs.x.cx=top;
    regs.x.dx=bottom-16;
    int86(51,&regs,&regs);
}

/**********************************************************************
	功能说明：设置鼠标位置；
	参数说明：x，y分别为鼠标横纵坐标
	返回值说明：无
*********************************************************************/

void SetMousePositon(int x,int y)
{
	union REGS regs;
	regs.x.ax=4;
	regs.x.cx=x;
	regs.x.dx=y;
	int86(51,&regs,&regs);

}

/********************************
	功能说明：设置鼠标计数与像素比,值越大鼠标移动速度越慢 
	参数说明：int   vx,	鼠标横向的；
			 int   vy	鼠标纵向的

********************************/
void  MouseSetSpeed(int vx,int vy)
{
	union REGS regs;
	regs.x.ax=0x0f;
	regs.x.cx=vx;
    regs.x.dx=vy;
	int86(51,&regs,&regs);
} 

/******************************************************
	功能说明：读鼠标的位置和按钮状态函数
	参数说明：mouse_x，mouse_y为鼠标坐标，mouse_butt为鼠标案件状态，1，2,4分别表示按下左中右键
	返回值说明：无返回值
***************************************************************/
void ReadMouse(int *mouse_x,int *mouse_y,char *mouse_butt )
{
	union REGS regs;
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*mouse_x=regs.x.cx;
	*mouse_y=regs.x.dx;
	*mouse_butt=regs.x.bx&0x07;
}


/********************************
	功能说明：获取鼠标状态,利用不活动不刷新消除闪烁
	参数说明：
		int * mouseX		鼠标纵坐标地址
		int * mouseY		鼠标横坐标地址
		int * mButton		鼠标按键状态地址
	返回值说明：

********************************/
void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt)
{
	int 	Xx0 = *mouse_x;
	int 	Yy0 = *mouse_y;
	int 	but0 =*mouse_butt;
	union REGS regs;
	/*获取鼠标位置*/
		regs.x.ax=3;
		int86(0x33,&regs,&regs);
		do
		{
			*mouse_x =regs.x.cx;
		    *mouse_y=regs.x.dx;
		    *mouse_butt =regs.x.bx&1;
		}while((*mouse_x == Xx0)&&(*mouse_y == Yy0)&&	(*mouse_butt == but0));
	}

/*********************************************************************
	功能说明：鼠标的显示操作，鼠标区域背景扣取
	参数说明：结构体说明见SVGA.H，
	返回值说明：无返回值
**************************************************************************/
void MouseCopy(Coord *CoordXY,char *mouse_buffer)    
{
	int i,j;
	unsigned long pos;
	short far * video_buffer=(short far *)0xA0000000L;
	int old_page,new_page;
	old_page=((CoordXY->y)*1600L+CoordXY->x)>>15;
	new_page=old_page;
	SelectPage(new_page);
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			pos=((CoordXY->y+i)*1600L+CoordXY->x+j);
			new_page=pos>>15;
			if(old_page!=new_page)
			{
				SelectPage(new_page);
				old_page=new_page;
			}
			mouse_buffer[i*16+j]=video_buffer[pos&0x0000ffffL];
		}
	}

}

/*****************************************************************************
	功能说明：鼠标区域背景扣取后重新显示
	参数说明：结构体说明见SVGA.H，
	返回值说明：无返回值
*****************************************************************************/
void MouseReshow(Coord *CoordXY,char *mouse_buffer)
{
	 int i,j;
    char old_page,new_page;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
	old_page=((CoordXY->y)*1600L+(CoordXY->x))/32768;
    new_page=old_page;
	SelectPage(old_page);
	for(i=0;i<16;i++)
	{
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600L+j+(CoordXY->x);
            new_page=pos>>15;
            if(old_page!=new_page)
            {
				SelectPage(new_page);
                old_page=new_page;
            }
			video_buffer[pos&0x0000ffffl]=mouse_buffer[i*16+j];
        }
    }
}

/**************************************************************************************
	功能说明：鼠标显示
	参数说明：见SVGA。h
	返回值说明：无返回值
**************************************************************************/
void MouseShow(Coord *CoordXY)
{
	int i,j;
	short far *video_buffer=(short far *)0xA0000000L;
	char new_page,old_page;
	unsigned long pos;
	old_page=((CoordXY->y)*1600L+(CoordXY->x))>>15;
    new_page=old_page;
	SelectPage(old_page);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*1600L+j+(CoordXY->x);
            new_page=pos>>15;
            if(old_page!=new_page)
            {
                SelectPage(new_page);
                old_page=new_page;
            }
             if(mouse_dot[i][j]==1)    /* 画鼠标*/
				video_buffer[pos&0x0000ffffl]=0xffff;
			 else if(mouse_dot[i][j]==2)
				video_buffer[pos&0x0000ffffl]=0;
        }
    }
    delay(15);
}