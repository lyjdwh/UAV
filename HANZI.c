#include <stdio.h>
#include <process.h>

#include "HANZI.h"
#include "SVGA.h"

/********************************
	功能说明：12*12点阵字母的显示
	参数说明：
		char *s 要显示的字符地址
		int x        起始x坐標
		int y        起始y坐標
		int color    指定的颜色
		int gap		 間隔
		mode为0则横向输出，1则纵向输出
	返回值说明:无 
********************************/
void PrintASC(char *s,int x,int y,int dx,int dy,short color)//dx为字距，dy为字体粗细
{
	char *s1;
	unsigned long offset;
	FILE *fp;
	char buffer[16]; 										//buffer用来存储一个字符
	int m,n,i,j;
	if ((fp=fopen("asc16","rb"))==NULL)
	{
		printf("Can't open asc16,Please add it");
		exit(1);
	}
	s1=s;
	while(*s)
	{
		offset=(*s)*16+1; 									//计算该字符在字库中偏移量
		fseek(fp,offset,SEEK_SET);
		fread(buffer,16,1,fp); 								//取出字符16字节的点阵字模存入buffer中

		for(n=0;n<dx;n++) 									//将16位字节的点阵按位在屏幕上打印出来(1:打印,0:不打印),显示字符
		{
			for(i=0;i<16;i++)
			{
						for(j=0;j<8;j++)
						{
							for(m=0;m<dy;m++)
							{
								if(((buffer[i]>>(7-j))&0x1)!=NULL)
								{
									PutPixel(x+j+n,y+i+m,color);
								}
							}
						}

			}
		}
		s++; 												//一个字符内码占用一个字节
		x+=8*dx;											//字符间间隔
	}
	s=s1;
	fclose(fp);

}
/********************************
	功能说明：12*12点阵汉字的显示
	参数说明：
		int x        起始x坐標
		int y        起始y坐標
		int color    指定的颜色
		int gap		 間隔
		mode为0则横向输出，1则纵向输出
	返回值说明:无 
********************************/
void PrintHZ12(int x,int y,char *s,int color,int dx,int dy,int gap,int mode)  
{
	char *s1;
	unsigned long offset;
	FILE *fp;
	char buffer[24]; 											//buffer用来存储一个汉字
	int m,n,i,j,k;
	unsigned char qh,wh;

	if ((fp=fopen("hzk12.c","rb"))==NULL)
	{
		printf("Can't open hzk12.c,Please add it");
		exit(1);
	}
	s1=s;
	while(*s)
	{
		qh=*(s)-0xa0; 											//汉字区位码
		wh=*(s+1)-0xa0;
		offset=(94*(qh-1)+(wh-1))*24L; 							//计算该汉字在字库中偏移量
		fseek(fp,offset,SEEK_SET);
		fread(buffer,24,1,fp); 									//取出汉字32字节的点阵字模存入buffer中（一个汉字）

		for(i=0;i<12;i++) 										//将24位字节的点阵按位在屏幕上打印出来(1:打印,0:不打印),显示汉字
		{
			for(n=0;n<dx;n++)
			{
					for(j=0;j<2;j++)
					{
						for(k=0;k<8;k++)
						{
							for(m=0;m<dy;m++)
							{
								if(((buffer[i*2+j]>>(7-k))&0x1)!=NULL)
								{
									PutPixel(x+8*j*dy+k*dy+m,y+i*dx+n,color);
								}
							}
						}
					}
			}
		}
		s+=2; 													//一个汉字内码占用两个字节
		if(mode==0)
		{
			x+=gap;												//字间间隔
		}
		if(mode==1)
		{
			y+=gap;
		}
		
	}
	s=s1;
	fclose(fp);
}
/********************************
	功能说明：16*16点阵汉字的显示
	参数说明：
		int x        起始x坐標
		int y        起始y坐標
		int color    指定的颜色
		int dx,dy
		
	返回值说明:无 
********************************/

void PrintHZ16(int x,int y,char *s,int color,int dx,int dy)  
{
	char *s1;
	unsigned long offset;
 	FILE *fp;
 	char buffer[32]; 											//buffer用来存储一个汉字
 	int m,n,i,j,k;
 	unsigned char qh,wh;

	if ((fp=fopen("hzk16.c","rb"))==NULL)
	{
		printf("Can't open hzk16.c,Please add it");
		exit(1);
	}
	s1=s;
	while(*s)
	{
		qh=*(s)-0xa0; 											//汉字区位码
		wh=*(s+1)-0xa0;
		offset=(94*(qh-1)+(wh-1))*32L; 							//计算该汉字在字库中偏移量
		fseek(fp,offset,SEEK_SET);
		fread(buffer,32,1,fp); 									//取出汉字32字节的点阵字模存入buffer中（一个汉字）
		
		for(i=0;i<16;i++) 										//将32位字节的点阵按位在屏幕上打印出来(1:打印,0:不打印),显示汉字
		{
			for(n=0;n<dx;n++)
			{
					for(j=0;j<2;j++)
					{
						for(k=0;k<8;k++)
						{
							for(m=0;m<dy;m++)
							{
								if(((buffer[i*2+j]>>(7-k))&0x1)!=NULL)
								{
									PutPixel(x+8*j*dy+k*dy+m,y+i*dx+n,color);
								}
							}
						}
					}
			}
		}
		s+=2; 													//一个汉字内码占用两个字节
		x+=16;													//字间间隔

	}
	s=s1;
	fclose(fp);
}

