/*******************************
地形图显示的函数的头文件
*******************************/
#ifndef _ProMap_H_
#define _ProMap_H_



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
			   );
void MidValueMap(
			   const unsigned int map_scale , //地形图规模
			   const int scale ,	//均值滤波的规模
			   FILE *map , //输入的待处理的图像
			   FILE *new_map //输出滤波后的图像
			   );
void StartSmooth(
				 const char *map_1 ,
			     const unsigned int map_scale , 
				 const int _loop , 
				 const int size
			     );
void StartMidValue(
				 const char *map_1 ,
			     const unsigned int map_scale , 
				 const int _loop , 
				 const int size
			     );
void StartAddCity(
				 const char *map_1 ,
			     const unsigned int map_scale , 
				 const int _loop , 
				 const int size
			     );				 
				 #endif