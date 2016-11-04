#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

#include "SVGA.h"
#include "mouse.h"

int mouse_save[16][16] ;  	/*���ڱ�����꼴�����ǵ�����*/
int mouse_dot[16][16]=   	//���������״,����1:��ʾ��������,2:��ʾ���߽�����Χ������ı߽�,0:��ʾ������������  
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
	����˵������ʼ����꣬����������ƶ���Χ
	����˵����wu
	����ֵ˵�����޷���ֵ
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
		printf("mouse or mouse driver is absent,please install ");
		getch();
		exit(1);
    }
    return;
}

/**********************************************************************
	����˵������������ƶ���Χ��
	����˵����int left,int top,int right,int bottom�ֱ�Ϊ������������
	����ֵ˵������
*********************************************************************/
void SetMouseRange(const int left,const int top,const int right,const int bottom)
{
	 union REGS regs;
	 int retcode,xmin=left,ymin=top,xmax=right-16,ymax=bottom-16;
	 /*�趨����ƶ��ı߽�*/
    regs.x.ax=7;
    regs.x.cx=xmin;
    regs.x.dx=xmax;
    int86(51,&regs,&regs);
    regs.x.ax=8;
    regs.x.cx=ymin;
    regs.x.dx=ymax;
    int86(51,&regs,&regs);
}

/**********************************************************************
	����˵�����������λ�ã�
	����˵����x��y�ֱ�Ϊ����������
	����ֵ˵������
*********************************************************************/

void SetMousePosition(int x,int y)
{
	union REGS regs;
    regs.x.ax=4;
	regs.x.cx=x;
    regs.x.dx=y;
	int86(51,&regs,&regs);//������굱ǰ����			 
	return ;

}

/********************************
	����˵�������������������ر�,ֵԽ������ƶ��ٶ�Խ�� 
	����˵����int   vx,	������ģ�
			 int   vy	��������

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
	����˵����������λ�úͰ�ť״̬����
	����˵����mouse_x��mouse_yΪ������꣬mouse_buttΪ��갸��״̬��1��2,4�ֱ��ʾ���������Ҽ�
	����ֵ˵�����޷���ֵ
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
	����˵������ȡ���״̬,���ò����ˢ��������˸
	����˵����
		int * mouseX		����������ַ
		int * mouseY		���������ַ
		int * mButton		��갴��״̬��ַ
	����ֵ˵����

********************************/
void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt)
{
	int 	Xx0 = *mouse_x;
	int 	Yy0 = *mouse_y;
	int 	but0 =*mouse_butt;
	union REGS regs;
	/*��ȡ���λ��*/
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
	����˵����������ʾ������������򱳾���ȡ
	����˵�����ṹ��˵����SVGA.H��
	����ֵ˵�����޷���ֵ
**************************************************************************/
void MouseCopy(Coord *CoordXY,short  *mouse_buffer)    
{
	int i,j;
	unsigned long pos;
	short far * video_buffer=(short far *)0xA0000000L;
	int old_page,new_page;
	old_page=((CoordXY->y)*800L+CoordXY->x)>>15;
	new_page=old_page;
	SelectPage(new_page);
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			pos=(((CoordXY->y)+i)*800L+(CoordXY->x)+j);
			new_page=pos>>15;
			if(old_page!=new_page)
			{
				SelectPage(new_page);
				old_page=new_page;
			}
			mouse_buffer[i*16+j]=video_buffer[pos%32768];
		}
	}

}

/*****************************************************************************
	����˵����������򱳾���ȡ��������ʾ
	����˵�����ṹ��˵����SVGA.H��
	����ֵ˵�����޷���ֵ
*****************************************************************************/
void MouseReshow(Coord *CoordXY,short *mouse_buffer)
{
	int i,j;
    char old_page,new_page;
    unsigned long pos;
    short far *video_buffer=(short far *)0xA0000000L;
	old_page=((CoordXY->y)*800L+(CoordXY->x))/32768;
    new_page=old_page;
	SelectPage(old_page);
	for(i=0;i<16;i++)
	{
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*800L+j+(CoordXY->x);
            new_page=pos>>15;
            if(old_page!=new_page)
            {
				SelectPage(new_page);
                old_page=new_page;
            }
			video_buffer[pos%65536]=mouse_buffer[i*16+j];
        }
    }
}

/**************************************************************************************
	����˵���������ʾ
	����˵������SVGA��h
	����ֵ˵�����޷���ֵ
**************************************************************************/
void MouseShow(Coord *CoordXY)
{
	int i,j;
	short far *video_buffer=(short far *)0xA0000000L;
	char new_page,old_page;
	unsigned long pos;
	old_page=((CoordXY->y)*800L+(CoordXY->x))>>15;
    new_page=old_page;
	SelectPage(old_page);
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
			pos=(i+(CoordXY->y))*800L+j+(CoordXY->x);
            new_page=pos>>15;
            if(old_page!=new_page)
            {
                SelectPage(new_page);
                old_page=new_page;
            }
             if(mouse_dot[i][j]==1)    /* �����*/
				video_buffer[pos&0x0000ffffl]=0xffff;
			 else if(mouse_dot[i][j]==2)
				video_buffer[pos&0x0000ffffl]=0;
        }
    }
    delay(15);
}