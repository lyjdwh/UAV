#include <stdio.h>
#include <process.h>

#include "HANZI.h"
#include "SVGA.h"

/********************************
	����˵����12*12������ĸ����ʾ
	����˵����
		char *s Ҫ��ʾ���ַ���ַ
		int x        ��ʼx����
		int y        ��ʼy����
		int color    ָ������ɫ
		int gap		 �g��
		modeΪ0����������1���������
	����ֵ˵��:�� 
********************************/
void PrintASC(char *s,int x,int y,int dx,int dy,short color)//dxΪ�־࣬dyΪ�����ϸ
{
	char *s1;
	unsigned long offset;
	FILE *fp;
	char buffer[16]; 										//buffer�����洢һ���ַ�
	int m,n,i,j;
	if ((fp=fopen("asc16","rb"))==NULL)
	{
		printf("Can't open asc16,Please add it");
		exit(1);
	}
	s1=s;
	while(*s)
	{
		offset=(*s)*16+1; 									//������ַ����ֿ���ƫ����
		fseek(fp,offset,SEEK_SET);
		fread(buffer,16,1,fp); 								//ȡ���ַ�16�ֽڵĵ�����ģ����buffer��

		for(n=0;n<dx;n++) 									//��16λ�ֽڵĵ���λ����Ļ�ϴ�ӡ����(1:��ӡ,0:����ӡ),��ʾ�ַ�
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
		s++; 												//һ���ַ�����ռ��һ���ֽ�
		x+=8*dx;											//�ַ�����
	}
	s=s1;
	fclose(fp);

}
/********************************
	����˵����12*12�����ֵ���ʾ
	����˵����
		int x        ��ʼx����
		int y        ��ʼy����
		int color    ָ������ɫ
		int gap		 �g��
		modeΪ0����������1���������
	����ֵ˵��:�� 
********************************/
void PrintHZ12(int x,int y,char *s,int color,int dx,int dy,int gap,int mode)  
{
	char *s1;
	unsigned long offset;
	FILE *fp;
	char buffer[24]; 											//buffer�����洢һ������
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
		qh=*(s)-0xa0; 											//������λ��
		wh=*(s+1)-0xa0;
		offset=(94*(qh-1)+(wh-1))*24L; 							//����ú������ֿ���ƫ����
		fseek(fp,offset,SEEK_SET);
		fread(buffer,24,1,fp); 									//ȡ������32�ֽڵĵ�����ģ����buffer�У�һ�����֣�

		for(i=0;i<12;i++) 										//��24λ�ֽڵĵ���λ����Ļ�ϴ�ӡ����(1:��ӡ,0:����ӡ),��ʾ����
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
		s+=2; 													//һ����������ռ�������ֽ�
		if(mode==0)
		{
			x+=gap;												//�ּ���
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
	����˵����16*16�����ֵ���ʾ
	����˵����
		int x        ��ʼx����
		int y        ��ʼy����
		int color    ָ������ɫ
		int dx,dy
		
	����ֵ˵��:�� 
********************************/

void PrintHZ16(int x,int y,char *s,int color,int dx,int dy)  
{
	char *s1;
	unsigned long offset;
 	FILE *fp;
 	char buffer[32]; 											//buffer�����洢һ������
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
		qh=*(s)-0xa0; 											//������λ��
		wh=*(s+1)-0xa0;
		offset=(94*(qh-1)+(wh-1))*32L; 							//����ú������ֿ���ƫ����
		fseek(fp,offset,SEEK_SET);
		fread(buffer,32,1,fp); 									//ȡ������32�ֽڵĵ�����ģ����buffer�У�һ�����֣�
		
		for(i=0;i<16;i++) 										//��32λ�ֽڵĵ���λ����Ļ�ϴ�ӡ����(1:��ӡ,0:����ӡ),��ʾ����
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
		s+=2; 													//һ����������ռ�������ֽ�
		x+=16;													//�ּ���

	}
	s=s1;
	fclose(fp);
}

