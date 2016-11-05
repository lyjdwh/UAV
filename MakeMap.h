/*******************************
地形图显示的函数的头文件
*******************************/

#ifndef _MakeMap_H_
#define _MakeMap_H_


/******获取顶点的数据，辅助函数*****/
void LoadAnglePoint(LOCATION *angle , const int x , const int y , const int height );
					
					
					
					
					
/*******
将地形图的高程数据存入文件
文件为一行，末尾储存地形的规模（map_scale）以及精细度（precision）
*******/
void WriteMap(
			  const unsigned int map_scale ,	//地图规模
			  const LOCATION point , //输入文件的点
			  FILE *map //储存地形图的文件指针
			  );
/*****
正方形-菱形（Diamond-Square）算法：
见“分形地形”
const unsigned int map_scale ,	//地形图规模
const int virtual_point , //边界外虚拟点
const char diamond , //参与计算的顶点数
const char precision , //地形图精细度
const LOCATION top_left , //矩形顶点数据(位置、高度)
const LOCATION top_right , 
const LOCATION bottom_right , 
const LOCATION bottom_left , 
FILE *map //储存地图文件指针
*******/
void DiamondSquare(
				   const unsigned int map_scale ,	//地形图规模
				   const int virtual_point , //边界外虚拟点
				   const char diamond , //参与计算的顶点数
				   const char precision , //地形图精细度
				   const LOCATION top_left , //矩形顶点数据(位置、高度)
				   const LOCATION top_right , 
				   const LOCATION bottom_right , 
				   const LOCATION bottom_left , 
				   FILE *map //储存地图文件指针
				   );
/*****
初始化地形图
包含：最外界顶点数据
*****/
void InitialMap(
				const unsigned int map_scale , 
			    const int height1 , 
			    const int height2 , 
			    const int height3 , 
			    const int height4 , 
			    FILE *map , 
			    LOCATION angle[4]
			    );
/********
装载地形图文件、确定其规模
const unsigned int map_scale , //地形图规模
const char precision , //地形图精度
FILE *map //地形图文件指针
********/
void LoadMap(const unsigned int map_scale , //地形图规模
			 const char precision , //地形图精度
			 FILE *map //地形图文件指针
			 );
			 
/***
将生成的地形图精度规模信息填入文件末尾
****/
void AddInformation(
			 	   unsigned int map_scale , 
				   char precision , 
				   const char *map_str
				   );
/*****
生成地形图框架
****/
void ConstructeMap(
				   const unsigned int map_scale , 
				   const int virtual_point ,
				   const char precision , 
				   const int height[4] , 
				   const char *map_root
					);
					
#endif