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


/*********
图像平滑化
通过平均值法求得平滑后的点的高度（颜色）数据（均值滤波）
const unsigned int map_scale , //地形图规模
const int scale ,	//均值滤波的规模
FILE *map , //输入的待处理的图像
FILE *new_map //输出滤波后的图像
**********/
void SmoothMap(
			   const unsigned int map_scale , //地形图规模
			   const int scale ,	//均值滤波的规模
			   FILE *map , //输入的待处理的图像
			   FILE *new_map //输出滤波后的图像
			   )
{
	int *p[21] , *info_scale;	//一次读取多行信息，加快平滑化速度
	int loop_y , loop_x , loop , loop_p;
	int temp_scale , loop_y_temp , loop_x_temp , half_scale;
	long int scale_temp , map_scale_temp;
	char *info_precision;

	temp_scale = scale * scale; 
	loop_y_temp = map_scale - scale - 1;
	loop_x_temp = map_scale - (scale / 2);
	half_scale = scale / 2;
	scale_temp = - (long)sizeof(int) * (long)map_scale * (scale - 1);
	map_scale_temp = sizeof(int) * map_scale;
	
	rewind(map);
	rewind(new_map);
	
	for(loop = 0 ; loop < scale ; loop++)	
		if((p[loop] = (int *)malloc(map_scale_temp)) == NULL)
		{
			
			exit(0);
		}

	for(loop_y = 0 ; loop_y < loop_y_temp ; loop_y++)
	{
		for(loop = 0 ; loop < scale ; loop++)
			fread(p[loop] , map_scale_temp , 1 , map);
		fseek(map , scale_temp , 1);
		
		for(loop_x = half_scale ; loop_x < loop_x_temp ; loop_x++)
		{
			for(loop = 0 ; loop < scale ; loop++)
				for(loop_p = - half_scale ; loop_p < half_scale + 1 ; loop_p++)
					p[half_scale][loop_x] += p[loop][loop_x + loop_p] / temp_scale; 
		}

		for(loop_p = 0 ; loop_p < half_scale ; loop_p++)
			if(loop_y == loop_p)
				fwrite(p[loop_p] , map_scale_temp , 1 , new_map);

		for(loop_p = half_scale + 1 ; loop_p < scale ; loop_p++)
			if(loop_y == loop_p)
				fwrite(p[loop_p] , map_scale_temp , 1 , new_map);
		
		fwrite(p[half_scale] , map_scale_temp , 1 , new_map);
	}
	for(loop = 0 ; loop < scale ; loop++)	
		free(p[loop]);
	if((info_scale = (int *)malloc(sizeof(int))) == NULL)
		{
			exit(0);
		}
	if((info_precision = (char *)malloc(sizeof(char))) == NULL)
		{
			exit(0);
		}
	
	/******将地形图复制到平滑化后的地形图文件尾*******/
	fseek(new_map , 0l , 2);
	fseek(map , -(long)(sizeof(int) + sizeof(char)) , 2);
	fread(info_scale , sizeof(int) , 1 , map);
	fwrite(info_scale , sizeof(int) , 1 , new_map);
	fread(info_precision , sizeof(char) , 1 , map);
	fwrite(info_precision , sizeof(char) , 1 , new_map);
	free(info_precision);
	free(info_scale);
}
 
 
void CopyMap(
			   const unsigned int map_scale , //地形图规模
			   FILE *map , //输入的待处理的图像
			   FILE *new_map //输出滤波后的图像
			   )
{
	int *p , *info_scale;	//一次读取多行信息，加快平滑化速度
	int loop_y;
	long int map_scale_temp;
	char *info_precision;

	map_scale_temp = sizeof(int) * map_scale;
	
	rewind(map);
	rewind(new_map);
	
		if((p = (int *)malloc(map_scale_temp)) == NULL)
		{
			
			exit(0);
		}

	for(loop_y = 0 ; loop_y < map_scale ; loop_y++)
	{
		fread(p , map_scale_temp , 1 , map);
		fwrite(p , map_scale_temp , 1 , new_map);
	}
	free(p);
	if((info_scale = (int *)malloc(sizeof(int))) == NULL)
		{
			exit(0);
		}
	if((info_precision = (char *)malloc(sizeof(char))) == NULL)
		{
			exit(0);
		}
	
	/******将地形图复制到平滑化后的地形图文件尾*******/
	fseek(new_map , 0l , 2);
	fseek(map , -(long)(sizeof(int) + sizeof(char)) , 2);
	fread(info_scale , sizeof(int) , 1 , map);
	fwrite(info_scale , sizeof(int) , 1 , new_map);
	fread(info_precision , sizeof(char) , 1 , map);
	fwrite(info_precision , sizeof(char) , 1 , new_map);
	free(info_precision);
	free(info_scale);
} 
 
void AddCity(
			   const unsigned int map_scale , //地形图规模
			   const int scale ,	//均值滤波的规模
			   FILE *map , //输入的待处理的图像
			   FILE *new_map //输出滤波后的图像
			   )
{
	int *p[21] , *info_scale ;	//一次读取多行信息，加快平滑化速度
	int loop_y , loop_x , loop , loop_p;
	int temp_scale , loop_y_temp , loop_x_temp , half_scale;
	long int scale_temp , map_scale_temp;
	char *info_precision;
	float average = 0 , s_deviation = 0 ;
	
	temp_scale = scale * scale; 
	loop_y_temp = map_scale - scale - 1;
	loop_x_temp = map_scale - (scale / 2);
	half_scale = scale / 2;
	scale_temp = - (long)sizeof(int) * (long)map_scale * (scale - 1);
	map_scale_temp = sizeof(int) * map_scale;
	
	rewind(map);
	rewind(new_map);
	
	for(loop = 0 ; loop < scale ; loop++)	
		if((p[loop] = (int *)malloc(map_scale_temp)) == NULL)
		{
			
			exit(0);
		}

	for(loop_y = 0 ; loop_y < loop_y_temp ; loop_y++)
	{
		for(loop = 0 ; loop < scale ; loop++)
			fread(p[loop] , map_scale_temp , 1 , map);
		fseek(map , scale_temp , 1);
		
		for(loop_x = half_scale ; loop_x < loop_x_temp ; loop_x++)
		{
			for(loop = 0 ; loop < scale ; loop++)
				for(loop_p = - half_scale ; loop_p < half_scale + 1 ; loop_p++)
					average = ((float)p[loop][loop_x + loop_p])/ temp_scale; 
		}
		
		for(loop_x = half_scale ; loop_x < loop_x_temp ; loop_x++)
		{
			for(loop = 0 ; loop < scale ; loop++)
				for(loop_p = - half_scale ; loop_p < half_scale + 1 ; loop_p++)
					s_deviation += ((float)p[loop][loop_x + loop_p] - average)*((float)p[loop][loop_x + loop_p] - average); 
		}
		
		s_deviation = sqrt(s_deviation / (scale * scale));
		
		if(s_deviation < 5000)
			for(loop_x = half_scale ; loop_x < loop_x_temp ; loop_x++)
			{
				for(loop = 0 ; loop < scale ; loop++)
					for(loop_p = - half_scale ; loop_p < half_scale + 1 ; loop_p++)
						p[loop][loop_x + loop_p] = 0xb312; 
			}
			
		for(loop_p = 0 ; loop_p < half_scale ; loop_p++)
			if(loop_y == loop_p)
				fwrite(p[loop_p] , map_scale_temp , 1 , new_map);

		for(loop_p = half_scale + 1 ; loop_p < scale ; loop_p++)
			if(loop_y == loop_p)
				fwrite(p[loop_p] , map_scale_temp , 1 , new_map);
		
		fwrite(p[half_scale] , map_scale_temp , 1 , new_map);
	}
	for(loop = 0 ; loop < scale ; loop++)	
		free(p[loop]);
	if((info_scale = (int *)malloc(sizeof(int))) == NULL)
		{
			exit(0);
		}
	if((info_precision = (char *)malloc(sizeof(char))) == NULL)
		{
			exit(0);
		}
	
	/******将地形图复制到平滑化后的地形图文件尾*******/
	fseek(new_map , 0l , 2);
	fseek(map , -(long)(sizeof(int) + sizeof(char)) , 2);
	fread(info_scale , sizeof(int) , 1 , map);
	fwrite(info_scale , sizeof(int) , 1 , new_map);
	fread(info_precision , sizeof(char) , 1 , map);
	fwrite(info_precision , sizeof(char) , 1 , new_map);
	free(info_precision);
	free(info_scale);
}

void MidValueMap(
			   const unsigned int map_scale , //地形图规模
			   const int scale ,	//均值滤波的规模
			   FILE *map , //输入的待处理的图像
			   FILE *new_map //输出滤波后的图像
			   )
{
	int *p[21] , *info_scale;	//一次读取多行信息，加快平滑化速度
	int loop_y , loop_x , loop , loop_p;
	int temp_scale , loop_y_temp , loop_x_temp , half_scale;
	long int scale_temp , map_scale_temp;
	char *info_precision;
	typedef struct extremum{
		int extre;
		int x;
		int y;
	}EXTREMUM;
	EXTREMUM min_height , max_height;
	
	min_height.extre = 0xffff;
	max_height.extre = 0;
	temp_scale = scale * scale; 
	loop_y_temp = map_scale - scale - 1;
	loop_x_temp = map_scale - (scale / 2);
	half_scale = scale / 2;
	scale_temp = - (long)sizeof(int) * (long)map_scale * (scale - 1);
	map_scale_temp = sizeof(int) * map_scale;
	
	rewind(map);
	rewind(new_map);
	
	for(loop = 0 ; loop < scale ; loop++)	
		if((p[loop] = (int *)malloc(map_scale_temp)) == NULL)
		{
			
			exit(0);
		}

	for(loop_y = 0 ; loop_y < loop_y_temp ; loop_y++)
	{
		for(loop = 0 ; loop < scale ; loop++)
			fread(p[loop] , map_scale_temp , 1 , map);
		fseek(map , scale_temp , 1);
		
		for(loop_x = half_scale ; loop_x < loop_x_temp ; loop_x++)
		{
			for(loop = 0 ; loop < scale ; loop++)
				for(loop_p = - half_scale ; loop_p < half_scale + 1 ; loop_p++)
				{
					if(p[loop][loop_x + loop_p] > max_height.extre)
					{
						max_height.extre = p[loop][loop_x + loop_p];
						max_height.x = loop_x + loop_p;
						max_height.y = loop;
					}
					if(p[loop][loop_x + loop_p] < min_height.extre)
					{
						min_height.extre = p[loop][loop_x + loop_p];
						min_height.x = loop_x + loop_p;
						min_height.y = loop;
					}
				}
			if((max_height.extre - min_height.extre) > 10)
			{
				p[min_height.y][min_height.x] = (max_height.extre + min_height.extre)/2;
				p[max_height.y][max_height.x] = (max_height.extre + min_height.extre)/2;
			}
			 max_height.extre = 0;
			 min_height.extre = 0xffff;
		}

		for(loop_p = 0 ; loop_p < half_scale ; loop_p++)
			if(loop_y == loop_p)
				fwrite(p[loop_p] , map_scale_temp , 1 , new_map);

		for(loop_p = half_scale + 1 ; loop_p < scale ; loop_p++)
			if(loop_y == loop_p)
				fwrite(p[loop_p] , map_scale_temp , 1 , new_map);
		
		fwrite(p[half_scale] , map_scale_temp , 1 , new_map);
	}
	for(loop = 0 ; loop < scale ; loop++)	
		free(p[loop]);
	if((info_scale = (int *)malloc(sizeof(int))) == NULL)
		{
			exit(0);
		}
	if((info_precision = (char *)malloc(sizeof(char))) == NULL)
		{
			exit(0);
		}
	
	/******将地形图复制到平滑化后的地形图文件尾*******/
	fseek(new_map , 0l , 2);
	fseek(map , -(long)(sizeof(int) + sizeof(char)) , 2);
	fread(info_scale , sizeof(int) , 1 , map);
	fwrite(info_scale , sizeof(int) , 1 , new_map);
	fread(info_precision , sizeof(char) , 1 , map);
	fwrite(info_precision , sizeof(char) , 1 , new_map);
	free(info_precision);
	free(info_scale);
}


void StartMidValue(
				 const char *map_1 ,	//输入图像
			     const unsigned int map_scale ,//图像规模
				 const int _loop , 
				 const int size
			     )
{
	int loop , ys , temp , loop_temp;
	FILE *map , *new_map;
	const char map_2[20] = "map_temp.dat";
	const int loop_size = _loop;

	
	DisplayStatus("正在打磨尖角》》》",".\\back\\BkImg.bmp",340,200);

	for(loop = 0 ; loop < 500 ; loop++)
		for(ys = 50 ; ys < 70 ; ys++)
			PutPixel(loop + 150 , ys , 0xbebe);
	
	for (loop = 0 ; loop < loop_size ; ++loop)
	{
		map=fopen(map_1 , "ab+");
		rewind(map);
		new_map=fopen(map_2 , "wb+");
		MidValueMap(map_scale , size , map , new_map);
		fclose(map);
		fclose(new_map);
		for(loop_temp = 0 ; loop_temp < (500/(1*2))*(2*loop+1) ; loop_temp++)
			for(ys = 50 ; ys<70 ; ys++)
				PutPixel(loop_temp + 150 , ys , 0x8954);
		map=fopen(map_2 , "ab+");
		rewind(map);
		new_map=fopen(map_1 , "wb+");
		MidValueMap(map_scale , size , map , new_map);
		fclose(map);
		fclose(new_map);
		for(loop_temp = 0 ; loop_temp < (500 / (1 * 2)) * (2 * loop + 2) ; loop_temp++)
			for(ys = 50 ; ys < 70;ys++)
				PutPixel(loop_temp + 150 , ys , 0x8954);
	}
	
	DisplayStatus("完毕！！！",".\\back\\BkImg.bmp",340,200);
}



void StartAddCity(
				 const char *map_1 ,	//输入图像
			     const unsigned int map_scale ,//图像规模
				 const int _loop , 
				 const int size
			     )
{
	int loop , ys , temp , loop_temp;
	FILE *map , *new_map;
	const char map_2[20] = "map_temp.dat";
	const int loop_size = _loop;

	
	DisplayStatus("正在寻找城市落脚点》》》",".\\back\\BkImg.bmp",340,200);

	for(loop = 0 ; loop < 500 ; loop++)
		for(ys = 50 ; ys < 70 ; ys++)
			PutPixel(loop + 150 , ys , 0xbebe);
	
	for (loop = 0 ; loop < loop_size ; ++loop)
	{
		map=fopen(map_1 , "ab+");
		rewind(map);
		new_map=fopen(map_2 , "wb+");
		AddCity(map_scale , size , map , new_map);
		fclose(map);
		fclose(new_map);
		for(loop_temp = 0 ; loop_temp < (500/(1*2))*(2*loop+1) ; loop_temp++)
			for(ys = 50 ; ys<70 ; ys++)
				PutPixel(loop_temp + 150 , ys , 0x8954);
		map=fopen(map_2 , "ab+");
		rewind(map);
		new_map=fopen(map_1 , "wb+");
		CopyMap(map_scale , map , new_map);
		fclose(map);
		fclose(new_map);
		for(loop_temp = 0 ; loop_temp < (500 / (1 * 2)) * (2 * loop + 2) ; loop_temp++)
			for(ys = 50 ; ys < 70;ys++)
				PutPixel(loop_temp + 150 , ys , 0x8954);
	}
	
	DisplayStatus("完毕！！！",".\\back\\BkImg.bmp",340,200);
}


/*****
图像平滑框架
*****/
void StartSmooth(
				 const char *map_1 ,	//输入图像
			     const unsigned int map_scale , //图像规模
				 const int _loop ,
				 const int size
			     )
{
	int loop , ys , temp , loop_temp;
	FILE *map , *new_map;
	const char map_2[20] = "map_temp.dat";
	const int loop_size = _loop;

	
	DisplayStatus("正在打磨边界》》》",".\\back\\BkImg.bmp",340,200);
	for(loop = 0 ; loop < 500 ; loop++)
		for(ys = 50 ; ys < 70 ; ys++)
			PutPixel(loop + 150 , ys , 0xbebe);
	
	for (loop = 0 ; loop < loop_size ; ++loop)
	{
		map=fopen(map_1 , "ab+");
		rewind(map);
		new_map=fopen(map_2 , "wb+");
		SmoothMap(map_scale , size , map , new_map);
		fclose(map);
		fclose(new_map);
		for(loop_temp = 0 ; loop_temp < (500/(1*2))*(2*loop+1) ; loop_temp++)
			for(ys = 50 ; ys<70 ; ys++)
				PutPixel(loop_temp + 150 , ys , 0x8954);
		map=fopen(map_2 , "ab+");
		rewind(map);
		new_map=fopen(map_1 , "wb+");
		SmoothMap(map_scale , size , map , new_map);
		fclose(map);
		fclose(new_map);
		for(loop_temp = 0 ; loop_temp < (500 / (1 * 2)) * (2 * loop + 2) ; loop_temp++)
			for(ys = 50 ; ys < 70;ys++)
				PutPixel(loop_temp + 150 , ys , 0x8954);
	}
	
	
	DisplayStatus("完毕！！！",".\\back\\BkImg.bmp",340,200);
}
