/************************************
该文件为一些图形显示的函数
********************************/

#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "SVGA.h"

/********************************
	功能说明：本函数在(x,y)点画指定颜色的点
	参数说明：
		int x        目标位置横坐标
		int y        目标位置纵坐标
		int color    指定的颜色
	返回值说明:无 
********************************/
void  PutPixel(int  x,int  y,short color)
{
	long pos;
	short far *video_buffer=(short far *)0xA0000000L;
	register new_page=0;
	pos = y* 800L + x;
	new_page = pos >>15;
	pos = pos& 0x0000ffffL;
	SelectPage(new_page);
	video_buffer[pos]= color;
}

/********************************
	功能说明：本函数在(x,y)点获取指定颜色的点
	参数说明：
		int x        目标位置横坐标
		int y        目标位置纵坐标
		int color    指定的颜色
	返回值说明:wu 
********************************/
short int GetPixel(int x, int y)
{
	long pos;
	short color;
	short far *video_buffer= (short far *)0xA0000000L;
	register int new_page =  0;
	pos = y*8001 +x;
	new_page = pos >> 15;
	pos = pos & 0x0000ffffL;
	SelectPage(new_page);
	color = video_buffer[pos];
	return color;
}

/********************************
	功能说明：从(x,y)开始从左向右画指定长度水平线
	参数说明：int x        所需画线的左端点横坐标
		int y        所需画线的左端点纵坐标
		int lenth    画线的长度(像素)
		int color    画线的颜色
	返回值说明：无
********************************/
void XLine(int x,int y,int length, int color)
{
	int i;
	long pos;
	int new_page =0 ,old_page=0;
	short far * video_buffer = (short far *)0xA0000000L;
	pos = y *8001 +x;
	old_page = pos >> 15;
	SelectPage(old_page);
	for(i=0 ;i<length ;i++)
	{
		pos= y*8001 +x+i;
		new_page = pos >>15;
		if( new_page !=old_page)
		{
			SelectPage(new_page);
			old_page = new_page;
		}
		video_buffer[pos &0x0000ffffL] =color;
	}
}

/********************************
	功能说明：从(x,y)开始从上到下垂直线
	参数说明：int x        所需画线的左端点横坐标
			int y        所需画线的左端点纵坐标
			int lenth    画线的长度(像素)
			int color    画线的颜色
	返回值说明：无
********************************/

void YLine(int x,int y,int length, int color)
{
	int i;
	long pos;
	int new_page =0 ,old_page=0;
	short far * video_buffer = (short far *)0xA0000000L;
	pos = y *8001 +x;
	old_page = pos >> 15;
	SelectPage(old_page);
	for(i=0 ;i<length ;i++)
	{
		pos= (y+i)*8001 +x;
		new_page = pos >>15;
		if( new_page !=old_page)
		{
			SelectPage(new_page);
			old_page = new_page;
		}
		video_buffer[pos &0x0000ffffL] =color;
	}
}




/******************************************************************
	功能说明：设置SVGA的模式
	参数说明：Mode序号
	返回值说明：int10中断中的_AH
   种类 编号 说明
   图形 100h 640*400*256
   图形 101h 640*480*256
   图形 102h 800*600*16
   图形 103h 800*600*256
   图形 104h 1024*768*16
   图形 105h 1024*768*256
   图形 106h 1280*1024*16
   图形 107h 1280*1024*256
   文本 108h 80*60*16
   文本 109h 132*25*16
   文本 10Ah 132*43*16
   文本 10Bh 132*50*16
   文本 10Ch 132*60*16
   图形 10Dh 320*200*32K
   图形 10Eh 320*200*64K
   图形 10Fh 320*200*16M
   图形 110h 640*480*32K
   图形 111h 640*488*64K
   图形 112h 640*480*16M
   图形 113h 800*600*32K
   图形 114h 800*600*64K
   图形 115h 800*600*16M
   图形 116h 1024*768*32K
   图形 117h 1024*768*64K
   图形 118h 1024*768*16M
   图形 119h 1280*1024*32K
   图形 11Ah 1280*1024*64K
   图形 10Bh 1280*1024*16M
   　ax  说 明
   0x4f00  读SVGA卡信息
   0x4f01  读显示模式信息
   0x4f02  设置显示模式
   0x4f03  读当前显示模式
   0x4f04  存储或恢复SVGA的视频状态
   0x54f05  控制内存页区域切换
   0x4f06  设置或读取逻辑扫描线宽度
   0x4f07  设置或读取视频内存与屏幕的初始对应位置
   0x4f08  设置或读取DAC各原色有效位数
*************************************************************************/
unsigned char SetSVGAMode(unsigned int mode) 
{
	union REGS in,out;
    in.x.ax=0x4f02;
    in.x.bx=mode;
    int86(0x10,&in,&out);
    if(out.h.ah==0x01)
    {
		//ReturnMode();
        printf("Set SVGA error!"); /*中断*/
        getch();
        exit(1);
    }
    return(out.h.ah);
}

/************************************************
	功能说明: 返回SVGA模式
	参数说明 : 无
	返回值说明: SVGA mode

**************************************************/
		
unsigned char GetSVGAMode()
{
	union REGS in,out;
	in.x.ax=0x4f03;
	int86(0x10,&in,&out);
	return out.h.ah;
}


/************************************************
	功能说明：SVGA显存换页面
	参数说明：index，页面号
	返回值说明：0
*******************************************************/
unsigned int SelectPage(unsigned char index)
{
	union REGS in,out;
	in.x.ax=0x4f05;
	in.x.bx=0;
	in.x.dx=index;
	int86(0x10,&in,&out);
	return 1;
}

/*******************************************
	功能说明：退出SVGA模式，返回原模式
	参数说明：无参数
	返回值说明：无返回值
**********************************************/

void ReturnMode()        
{
    union REGS in;
    in.h.ah=0;
    in.h.al=(char)0x03;
    int86(0x10,&in,&in);  /*中断*/
    return;
}
/*******************************************************
	功能说明：从硬盘读取BMP直接到显存,支持不同
	参数说明：x，y：图片左上角坐标，FileName：文件路径
	返回值说明：无返回值
***********************************************************/

char ReadBmp(int x,int y,char *FileName)
{
    int i,j,k=0;
    FILE *fp;
	char old_page=0,new_page=0;
	unsigned int data_offset;
    long width,height;
    unsigned long pos;
    short *buffer;

	BITMAPFILEHEADER		FileHeader;
	BITMAPINFOHEADER		 bmiHeader;

	short far *VedioBuffer=(short far *)0xA0000000L;
    if((fp=fopen(FileName,"rb"))==NULL)
    {
		ReturnMode();
		printf("Cannot read the picture\n\t\t%s",FileName);
		getch();
		exit(1);
	}
	 																/*  读文件头 */
	if (fread((char *)&FileHeader, sizeof(FileHeader), 1, fp) != 1)
	{
		printf("Can't read file header !\n");
		return 0;
	}
	if (FileHeader.bfType != 0X4D42)
	{	
		fprintf(stderr, "Not a BMP file !\n");
		return 0;
	}
	 																/*  读信息头 */
	if (fread((char *)&bmiHeader, sizeof(bmiHeader), 1, fp) != 1)
	{
		fprintf(stderr, "Can't read bmiHeader !\n");  
		return 0;
	}
																	/*  不能显示真彩色图像 */
	if (bmiHeader.biBitCount <16)
	{	
		fprintf(stderr, "Not non-compressed image !\n");
		return 0;
	}


	width = (unsigned int)bmiHeader.biWidth;
	height = (unsigned int)bmiHeader.biHeight;
	buffer=(short *)malloc(width*sizeof(short));
    if(buffer==NULL)
    {
		ReturnMode();
        printf("SVAGA.c_Malloc error! in function ReadBMP!");
        getch();
        return 1;
	}

    data_offset=(unsigned int)FileHeader.bfOffBits;					
	fseek(fp,data_offset,SEEK_SET);									/*Put BITS to VRAM*/

   
	k=(width*2%4)?(4-width*2%4):0;									/*计算偏移量，windos只能读取4的整数倍字节*/
	old_page=((height-1+y)*8001+x)>>15;							/*计算显示页*/
	new_page=old_page;
    SelectPage(old_page);   
	for(i=height-1;i>=0;i--)
    {
		fread(buffer,width*2+k,1,fp); 								//读取一行像素点的信息
        for(j=0;j<width;j++)     									//把读取的一行像素点显示出来
        {
			pos=((i+y)*800l+j+x);									/*计算要显示点的显示位置POSITION*/
            new_page=pos>>15;										/*计算显示页*/
			pos=pos&0x0000ffffl;									/*计算在一个页面上的偏移位置，整除65536的快速方案*/
            if(new_page!=old_page)//换页
            {
				SelectPage(new_page);
                old_page=new_page;
            }
			VedioBuffer[pos]=buffer[j];
        }
    }
    /*Close file*/
    fclose(fp);
    free(buffer);
    return 1;
}

/*******************************************************
	功能说明：从硬盘读取BMP直接到显存
	参数说明：x，y：图片左上角坐标，FileName：文件路径
	          x0,y0截取图片部分的左上角坐标，H,W截取图片部分的高与宽
	返回值说明：成功返回1，否则返回0
***********************************************************/
char ReadPartBMP(int x,int y,int x0,int y0,int w,int h,char *FileName)
{
    int i,j,k=0;
    FILE *fp;
	char old_page=0,new_page=0;
	unsigned int data_offset;
	long width,height;
    long linebytes;
	
																			/*宽高限制*/
	int      ResX; 
    int      ResY;
    
	unsigned long pos;
    short *buffer;


	BITMAPFILEHEADER		FileHeader;
	BITMAPINFOHEADER		 bmiHeader;

	short far *vedio_buffer=(short far *)0xA0000000L;
    if((fp=fopen(FileName,"rb"))==NULL)
    {
		ReturnMode();
		printf("Cannot read the picture\n\t\t%s",FileName);
        getch();
        exit(1);
    }


	if (fread((char *)&FileHeader, sizeof(FileHeader), 1, fp) != 1)
	{
		printf("Can't read file header !\n"); 								/*  读文件头 */
		return 0;
	}
	if (FileHeader.bfType != 0X4D42)
	{																		/* BM */
		fprintf(stderr, "Not a BMP file !\n");
		return 0;
	}

	if (fread((char *)&bmiHeader, sizeof(bmiHeader), 1, fp) != 1)
	{
		fprintf(stderr, "Can't read bmiHeader !\n");   						/*  读信息头 */
		return 0;
	}
	if (bmiHeader.biBitCount <16)
	{
		fprintf(stderr, "Not non-compressed image !\n");
		return 0;
	}


	width = (unsigned int)bmiHeader.biWidth;
	height = (unsigned int)bmiHeader.biHeight;
    data_offset = (unsigned int)FileHeader.bfOffBits;


	/*RAM start*/
	buffer=(short *)malloc(width*sizeof(short));
	if(buffer==NULL)
	{
		ReturnMode();
		printf("SVGA.c_Malloc error! in function ReadBMP!");
		getch();
		return 1;
	}

   																			 /*设置宽高限制*/
    if ((w + x) > 800)
        ResX = 800 - x;
    else ResX = w;
	if ((h + y) > 600)
        ResY = 600 - y;
    else ResY = h;
    
	
    k=(width*2%4)?(4-width*2%4):0;											/*拼凑4字节倍数修正宽度*/
	linebytes = width * 2+k;


	fseek(fp,data_offset+linebytes*(height-y0-h)+x0*2L,SEEK_SET);
	old_page=((h-1+y)*800l+x)>>15;
	new_page=old_page;
    SelectPage(old_page);   
	for(i=h-1;i>=0;i--)
    {
		fread(buffer,width*2+k,1,fp);  										//读取一行像素点的信息
		if(i<ResY)
		{
		  for(j=0;j<ResX;j++)     											//把读取的一行像素点显示出来
		  {
			 pos=((i+y)*800l+j+x);
			 new_page=pos>>15;
			 if(new_page!=old_page)											/*Change Pages!!!*/
			 {
				 SelectPage(new_page);
				 old_page=new_page;
             }
             vedio_buffer[pos&0x0000ffffl]=buffer[j];
          }
		}    
	}
    																		
    fclose(fp);																/*Close file*/
    free(buffer);
    return 1;
}



/*********************************************************************
	功能说明：逻辑显存横向像素数量设定
	参数说明：
	返回值说明：
******************************************************************************/
void SetScreenWidth(unsigned pixels)   
{
    static union REGS r;
    r.h.bl=0;
    r.x.ax=0x4f06;
    r.x.cx=pixels;
	int86(0x10,&r,&r);
    return;
}


/*********************************************************************
	功能说明：逻辑显存显示像素起始位置
	参数说明：
	返回值说明：
******************************************************************************/
void SetShowBegin(int x,int y)          
{
    static union REGS r;
    r.x.cx=x;
    r.x.dx=y;
    r.x.ax=0x4f07;
    int86(0x10,&r,&r);
}
