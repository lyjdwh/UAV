/************************************
���ļ�ΪһЩͼ����ʾ�ĺ���
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
	����˵������������(x,y)�㻭ָ����ɫ�ĵ�
	����˵����
		int x        Ŀ��λ�ú�����
		int y        Ŀ��λ��������
		int color    ָ������ɫ
	����ֵ˵��:�� 
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
	����˵������������(x,y)���ȡָ����ɫ�ĵ�
	����˵����
		int x        Ŀ��λ�ú�����
		int y        Ŀ��λ��������
		int color    ָ������ɫ
	����ֵ˵��:wu 
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
	����˵������(x,y)��ʼ�������һ�ָ������ˮƽ��
	����˵����int x        ���軭�ߵ���˵������
		int y        ���軭�ߵ���˵�������
		int lenth    ���ߵĳ���(����)
		int color    ���ߵ���ɫ
	����ֵ˵������
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
	����˵������(x,y)��ʼ���ϵ��´�ֱ��
	����˵����int x        ���軭�ߵ���˵������
			int y        ���軭�ߵ���˵�������
			int lenth    ���ߵĳ���(����)
			int color    ���ߵ���ɫ
	����ֵ˵������
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
	����˵��������SVGA��ģʽ
	����˵����Mode���
	����ֵ˵����int10�ж��е�_AH
   ���� ��� ˵��
   ͼ�� 100h 640*400*256
   ͼ�� 101h 640*480*256
   ͼ�� 102h 800*600*16
   ͼ�� 103h 800*600*256
   ͼ�� 104h 1024*768*16
   ͼ�� 105h 1024*768*256
   ͼ�� 106h 1280*1024*16
   ͼ�� 107h 1280*1024*256
   �ı� 108h 80*60*16
   �ı� 109h 132*25*16
   �ı� 10Ah 132*43*16
   �ı� 10Bh 132*50*16
   �ı� 10Ch 132*60*16
   ͼ�� 10Dh 320*200*32K
   ͼ�� 10Eh 320*200*64K
   ͼ�� 10Fh 320*200*16M
   ͼ�� 110h 640*480*32K
   ͼ�� 111h 640*488*64K
   ͼ�� 112h 640*480*16M
   ͼ�� 113h 800*600*32K
   ͼ�� 114h 800*600*64K
   ͼ�� 115h 800*600*16M
   ͼ�� 116h 1024*768*32K
   ͼ�� 117h 1024*768*64K
   ͼ�� 118h 1024*768*16M
   ͼ�� 119h 1280*1024*32K
   ͼ�� 11Ah 1280*1024*64K
   ͼ�� 10Bh 1280*1024*16M
   ��ax  ˵ ��
   0x4f00  ��SVGA����Ϣ
   0x4f01  ����ʾģʽ��Ϣ
   0x4f02  ������ʾģʽ
   0x4f03  ����ǰ��ʾģʽ
   0x4f04  �洢��ָ�SVGA����Ƶ״̬
   0x54f05  �����ڴ�ҳ�����л�
   0x4f06  ���û��ȡ�߼�ɨ���߿��
   0x4f07  ���û��ȡ��Ƶ�ڴ�����Ļ�ĳ�ʼ��Ӧλ��
   0x4f08  ���û��ȡDAC��ԭɫ��Чλ��
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
        printf("Set SVGA error!"); /*�ж�*/
        getch();
        exit(1);
    }
    return(out.h.ah);
}

/************************************************
	����˵��: ����SVGAģʽ
	����˵�� : ��
	����ֵ˵��: SVGA mode

**************************************************/
		
unsigned char GetSVGAMode()
{
	union REGS in,out;
	in.x.ax=0x4f03;
	int86(0x10,&in,&out);
	return out.h.ah;
}


/************************************************
	����˵����SVGA�Դ滻ҳ��
	����˵����index��ҳ���
	����ֵ˵����0
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
	����˵�����˳�SVGAģʽ������ԭģʽ
	����˵�����޲���
	����ֵ˵�����޷���ֵ
**********************************************/

void ReturnMode()        
{
    union REGS in;
    in.h.ah=0;
    in.h.al=(char)0x03;
    int86(0x10,&in,&in);  /*�ж�*/
    return;
}
/*******************************************************
	����˵������Ӳ�̶�ȡBMPֱ�ӵ��Դ�,֧�ֲ�ͬ
	����˵����x��y��ͼƬ���Ͻ����꣬FileName���ļ�·��
	����ֵ˵�����޷���ֵ
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
	 																/*  ���ļ�ͷ */
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
	 																/*  ����Ϣͷ */
	if (fread((char *)&bmiHeader, sizeof(bmiHeader), 1, fp) != 1)
	{
		fprintf(stderr, "Can't read bmiHeader !\n");  
		return 0;
	}
																	/*  ������ʾ���ɫͼ�� */
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

   
	k=(width*2%4)?(4-width*2%4):0;									/*����ƫ������windosֻ�ܶ�ȡ4���������ֽ�*/
	old_page=((height-1+y)*8001+x)>>15;							/*������ʾҳ*/
	new_page=old_page;
    SelectPage(old_page);   
	for(i=height-1;i>=0;i--)
    {
		fread(buffer,width*2+k,1,fp); 								//��ȡһ�����ص����Ϣ
        for(j=0;j<width;j++)     									//�Ѷ�ȡ��һ�����ص���ʾ����
        {
			pos=((i+y)*800l+j+x);									/*����Ҫ��ʾ�����ʾλ��POSITION*/
            new_page=pos>>15;										/*������ʾҳ*/
			pos=pos&0x0000ffffl;									/*������һ��ҳ���ϵ�ƫ��λ�ã�����65536�Ŀ��ٷ���*/
            if(new_page!=old_page)//��ҳ
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
	����˵������Ӳ�̶�ȡBMPֱ�ӵ��Դ�
	����˵����x��y��ͼƬ���Ͻ����꣬FileName���ļ�·��
	          x0,y0��ȡͼƬ���ֵ����Ͻ����꣬H,W��ȡͼƬ���ֵĸ����
	����ֵ˵�����ɹ�����1�����򷵻�0
***********************************************************/
char ReadPartBMP(int x,int y,int x0,int y0,int w,int h,char *FileName)
{
    int i,j,k=0;
    FILE *fp;
	char old_page=0,new_page=0;
	unsigned int data_offset;
	long width,height;
    long linebytes;
	
																			/*�������*/
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
		printf("Can't read file header !\n"); 								/*  ���ļ�ͷ */
		return 0;
	}
	if (FileHeader.bfType != 0X4D42)
	{																		/* BM */
		fprintf(stderr, "Not a BMP file !\n");
		return 0;
	}

	if (fread((char *)&bmiHeader, sizeof(bmiHeader), 1, fp) != 1)
	{
		fprintf(stderr, "Can't read bmiHeader !\n");   						/*  ����Ϣͷ */
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

   																			 /*���ÿ������*/
    if ((w + x) > 800)
        ResX = 800 - x;
    else ResX = w;
	if ((h + y) > 600)
        ResY = 600 - y;
    else ResY = h;
    
	
    k=(width*2%4)?(4-width*2%4):0;											/*ƴ��4�ֽڱ����������*/
	linebytes = width * 2+k;


	fseek(fp,data_offset+linebytes*(height-y0-h)+x0*2L,SEEK_SET);
	old_page=((h-1+y)*800l+x)>>15;
	new_page=old_page;
    SelectPage(old_page);   
	for(i=h-1;i>=0;i--)
    {
		fread(buffer,width*2+k,1,fp);  										//��ȡһ�����ص����Ϣ
		if(i<ResY)
		{
		  for(j=0;j<ResX;j++)     											//�Ѷ�ȡ��һ�����ص���ʾ����
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
	����˵�����߼��Դ�������������趨
	����˵����
	����ֵ˵����
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
	����˵�����߼��Դ���ʾ������ʼλ��
	����˵����
	����ֵ˵����
******************************************************************************/
void SetShowBegin(int x,int y)          
{
    static union REGS r;
    r.x.cx=x;
    r.x.dx=y;
    r.x.ax=0x4f07;
    int86(0x10,&r,&r);
}
