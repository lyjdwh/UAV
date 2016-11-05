#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "SVGA.h"
#include "account.h"
#include "PAINTMAP.h"
#include "MakeMap.h"
#include "InfoShow.h"
#include "ProMap.h"



/******��ȡ��������ݣ���������*****/
void LoadAnglePoint(
					LOCATION *angle , 
					const int x , 
					const int y , 
					const int height 
					)
{
	angle->x = x;
	angle->y = y;
	angle->height = height;
}

/*******
������ͼ�ĸ߳����ݴ����ļ�
�ļ�Ϊһ�У�ĩβ������εĹ�ģ��map_scale���Լ���ϸ�ȣ�precision��
*******/
void WriteMap(
			  const unsigned int map_scale ,	//��ͼ��ģ
			  const LOCATION point , //�����ļ��ĵ�
			  FILE *map //�������ͼ���ļ�ָ��
			  )
{
	unsigned long int position;
	position = (unsigned long int)(((long)point.y * (long)map_scale + (long)point.x) * (long)sizeof(int));
	fseek(map , position , 0);
	fwrite(&(point.height) , sizeof(int) , 1 , map);
}

/*******
DS�㷨���ĵ������߶�����ֵ�������������ָ���ֲ�������ά���ε��ε��о���ʵ�֡�.���갶����P10��
********/
/* int RandHeight()
{
	return -log(rand()*3.1415+1.0)+50;
} */

/*****
������-���Σ�Diamond-Square���㷨��
�������ε��Ρ�
const unsigned int map_scale ,	//����ͼ��ģ
const int virtual_point , //�߽��������
const char diamond , //�������Ķ�����
const char precision , //����ͼ��ϸ��
const LOCATION top_left , //���ζ�������(λ�á��߶�)
const LOCATION top_right , 
const LOCATION bottom_right , 
const LOCATION bottom_left , 
FILE *map //�����ͼ�ļ�ָ��
*******/
void DiamondSquare(
				   const unsigned int map_scale ,	//����ͼ��ģ
				   const int virtual_point , //�߽��������
				   const char diamond , //�������Ķ�����
				   const char precision , //����ͼ��ϸ��
				   const LOCATION top_left , //���ζ�������(λ�á��߶�)
				   const LOCATION top_right , 
				   const LOCATION bottom_right , 
				   const LOCATION bottom_left , 
				   FILE *map //�����ͼ�ļ�ָ��
				   )
{
	LOCATION middle , top , right , bottom , left;
	unsigned long int position;
	unsigned long int type_size , map_scale_temp;
	int height_temp_1;
	height_temp_1 = middle.height + virtual_point;
	type_size = sizeof(int);
	map_scale_temp = (unsigned long)map_scale;

	middle.x = (top_left.x + top_right.x) / 2;
	middle.y = (top_left.y + bottom_left.y) / 2;
	/******
	����ѡȡ�������ƫ�����ļ������һ��ʽ������ɣ��п��ǵ������ú����Ļ������ձ�ﵽ���������ǧ������ϵĵ��ã�ʱ�俪���޴󣬹ʲ����ú������õķ�ʽ
	*****/
	middle.height = (top_left.height + top_right.height + bottom_right.height + bottom_left.height) / 4 -log(rand()*3.1415+1.0)+50;
	position = (middle.y * map_scale_temp + middle.x) * type_size;
	fseek(map , position , 0);
	fwrite(&(middle.height) , type_size , 1 , map);

	top.x = middle.x;
	top.y = top_left.y;
	top.height = (top_left.height + top_right.height + height_temp_1) / diamond -log(rand()*3.1415+1.0)+50;
	position = (top.y * map_scale_temp + top.x) * type_size;
	fseek(map , position , 0);
	fwrite(&(top.height) , type_size , 1 , map);

	right.x = top_right.x;
	right.y = middle.y;
	right.height = (top_right.height + bottom_right.height + height_temp_1) / diamond -log(rand()*3.1415+1.0)+50;
	position = (right.y * map_scale_temp + right.x) * type_size;
	fseek(map , position , 0);
	fwrite(&(right.height) , type_size , 1 , map);

	bottom.x = middle.x;
	bottom.y = bottom_left.y;
	bottom.height = (bottom_right.height + bottom_left.height + height_temp_1) / diamond -log(rand()*3.1415+1.0)+50;
	position = (bottom.y * map_scale_temp + bottom.x) * type_size;
	fseek(map , position , 0);
	fwrite(&(bottom.height) , type_size , 1 , map);

	left.x = top_left.x;
	left.y = middle.y;
	left.height = (top_left.height + bottom_left.height + height_temp_1) / diamond -log(rand()*3.1415+1.0)+50;
	position = (left.y * map_scale_temp + left.x) * type_size;
	fseek(map , position , 0);
	fwrite(&(left.height) , type_size , 1 , map);

	if(abs(top_left.x-top.x) > precision)
	{
		DiamondSquare(map_scale , virtual_point , diamond , precision , top_left , top , middle , left , map);
		DiamondSquare(map_scale , virtual_point , diamond , precision , top , top_right , right , middle , map);
		DiamondSquare(map_scale , virtual_point , diamond , precision , middle,right , bottom_right , bottom , map);
		DiamondSquare(map_scale , virtual_point , diamond , precision , left , middle , bottom , bottom_left , map);
	}
}

/*****
��ʼ������ͼ
����������綥������
*****/
void InitialMap(
				const unsigned int map_scale , 
			    const int height1 , 
			    const int height2 , 
			    const int height3 , 
			    const int height4 , 
			    FILE *map , 
			    LOCATION angle[4]
			    )		
{
	int position_temp;

	position_temp = map_scale - 1;

	rewind(map);

	LoadAnglePoint(&angle[0] , 0 , 0 , height1);
	LoadAnglePoint(&angle[1] , position_temp , 0 , height2);
	LoadAnglePoint(&angle[2] , position_temp , position_temp , height3);
	LoadAnglePoint(&angle[3] , 0 , position_temp , height4);
	
	WriteMap(map_scale , angle[0] , map);
	WriteMap(map_scale , angle[1] , map);
	WriteMap(map_scale , angle[2] , map);
	WriteMap(map_scale , angle[3] , map);
}

/********
װ�ص���ͼ�ļ���ȷ�����ģ
const unsigned int map_scale , //����ͼ��ģ
const char precision , //����ͼ����
FILE *map //����ͼ�ļ�ָ��
********/
void LoadMap(const unsigned int map_scale , //����ͼ��ģ
			 const char precision , //����ͼ����
			 FILE *map //����ͼ�ļ�ָ��
			 )
{
	long int i , j;
	int *input;
	int loop;
	int map_scale_temp;

	map_scale_temp = sizeof(int) * map_scale;

	rewind(map);
	
	if( (input = (int *) malloc(map_scale_temp)) == NULL )
	{
		printf("error");
		exit(0);
	}
	for( loop = 0 ; loop < map_scale ; loop++ )
	{
		input[loop] = 0;
	}
	for( loop = 0 ; loop < map_scale ; loop++ )
	{
		fwrite(input , map_scale_temp , 1 , map);
	}
}

/***
�����ɵĵ���ͼ���ȹ�ģ��Ϣ�����ļ�ĩβ
****/
void AddInformation(
			 	   unsigned int *map_scale , 
				   char *precision , 
				   const char *map_str
				   )
{
	FILE *map;
	map = fopen(map_str , "ab+");
	fseek(map , 0l , 2);
	fwrite(map_scale , sizeof(int) , 1 , map);
	fwrite(precision , sizeof(char) , 1 , map);
	fclose(map);
}

/*****
���ɵ���ͼ���
****/
void ConstructeMap(
				   const unsigned int map_scale , 
				   const int virtual_point ,
				   const char precision , 
				   const int height[4] , 
				   const char *map_root
					)
{
	FILE *map;
	LOCATION ang[4];
	int diamond;
	ReadBmp(0 , 0 ,".\\back\\BkImg.bmp");
	DisplayStatus("���ڹ������Ρ�����",".\\back\\BkImg.bmp",340,200);
	
	if(virtual_point == 0)
		diamond = 3;
	else 
		diamond = 4;
	srand((unsigned int)time(NULL));
	if((map=fopen(map_root,"wb+"))==NULL)
	{
		printf("SOMETHING ERROR!");
		exit(0);
	}

	LoadMap(map_scale , precision , map);

		
	InitialMap(map_scale,height[0],height[1],height[2],height[3],map,ang);
	
	DiamondSquare(map_scale,virtual_point,diamond,precision,ang[0],ang[1],ang[2],ang[3],map);

	DisplayStatus("����������ϣ�����",".\\back\\BkImg.bmp",340,200);
	
	fclose(map);
}

