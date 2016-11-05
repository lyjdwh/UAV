/*******************************
地形图显示的函数的头文件
*******************************/

#ifndef _PaintMap_H_
#define _PaintMap_H_

typedef struct{
	int x;     
	int y;        
	int height;			
}LOCATION;
/******
从屏幕上读取点移动，保存点的位置（x，y）信息
flag表示点是否被储存
******/
typedef struct{
	int x;
	int y;
	int flag;
}POINT_STORAGE;
/********
绘制地形图
const unsigned int map_scale , //规模
FILE *map , //地形图文件指针
const int position_x , //地形窗口x方向偏移量
const int position_y , //地形窗口y方向偏移量
const int x , //显示地形图的位置坐标x
const int y , //显示地形图的位置坐标y
const int zoom , //缩放倍数
const int zoom_x , //缩放位置选择坐标x
const int zoom_y , //缩放位置选择坐标y
POINT_STORAGE *storage ,	//储存上一次缩放位置信息，一遍图像能够按照原来位置还原
const float angle_point	//地形旋转角度
**********/
void PaintMap(
			  const unsigned int map_scale , //规模
			  FILE *map , //地形图文件指针
			  const int position_x , //地形窗口x方向偏移量
    		  const int position_y , //地形窗口y方向偏移量
			  const int x , //显示地形图的位置坐标x
			  const int y , //显示地形图的位置坐标y
			  const int zoom , //缩放倍数
			  const int zoom_x , //缩放位置选择坐标x
			  const int zoom_y , //缩放位置选择坐标y
			  POINT_STORAGE *storage ,	//储存上一次缩放位置信息，一遍图像能够按照原来位置还原
			  const float angle_point	//地形旋转角度
			  );

/*********
构建窗口的中心十字标记
const int align_left ,	//窗口偏移量x
const int align_top , //窗口偏移量y
const int width ,	//窗口宽度
const int height , //窗口高度
const int target_scale , //标记的大小
const int thick ,	//标记的厚度
const int color //标记的颜色
**********/
void CenterTarget(
				 const int align_left ,	//窗口偏移量x
				 const int align_top , //窗口偏移量y
				 const int width ,	//窗口宽度
				 const int height , //窗口高度
				 const int target_scale , //标记的大小
				 const int thick ,	//标记的厚度
				 const int color //标记的颜色
				);


/*****
画直线（水平、垂直）
const int x ,	//起点x坐标
const int y ,	//起点y坐标
const int length ,	//直线长度
const int direction ,	//直线的方向
						1--北
						2--东
						3--南
						4--西
const int color , //直线的颜色
int **line //储存直线覆盖除的高度（颜色）信息
*****/
void PaintLine(
				const int x ,	//起点x坐标
				const int y ,	//起点y坐标
				const int length ,	//直线长度
				const int direction ,	//直线的方向
				const int color , //直线的颜色
				int **line //储存直线覆盖除的高度（颜色）信息
				);
/******
绘制缩放选择框
const int align_left ,	//偏移量x
const int align_top ,	//偏移量y
const int x , //选择框位置坐标x
const int y ,	//选择框位置坐标y
const int paint_scale , //地形图显示框规模
LOCATION **lines	//储存缩放选择框边线覆盖部分的颜色（高度）、位置信息
******/
void ZoomArea(
			 const int align_left ,	//偏移量x
			 const int align_top ,	//偏移量y
			 const int x , //选择框位置坐标x
			 const int y ,	//选择框位置坐标y
			 const int paint_scale , //地形图显示框规模
			 LOCATION **lines	//储存缩放选择框边线覆盖部分的颜色（高度）、位置信息
			 );
			 
/*******
清除地形图显示窗口
const int align_left ,	//地形图偏移量x 
const int align_top , //地形图偏移量y
const int width , //地形图宽度
const int height //地形图高度
*********/
void ClearViewport(
					const int align_left ,	//地形图偏移量x 
					const int align_top , //地形图偏移量y
					const int width , //地形图宽度
					const int height //地形图高度
					);
/*****
读取地形缩放命令
const char order , //命令参数
const unsigned int map_scale , //地形图规模
const int x ,	//显示地形图位置x
const int y , //显示地形图位置x
const int align_left , //偏移量x
const int align_top ,	//偏移量y
const int paint_scale ,//显示窗口规模
const int zoom , //缩放倍数
const int zoom_dis_x ,//缩放选择框显示信息位置x
const int zoom_dis_y ,//缩放选择框显示信息位置y
const int angle_point , //旋转角度
FILE *map ,  //地形图文件指针
LOCATION **lines ,	//缩放选择框边线覆盖部分的颜色（高度）、位置信息
int *zoom_pos_x ,	//缩放位置选择坐标x
int *zoom_pos_y ,	//缩放位置选择坐标y
int *speed_zoom , //缩放框移动速度
const int speed_zoom_x , //缩放框移动速度显示坐标x
const int speed_zoom_y	//缩放框移动速度显示坐标y
*******/
void ReadOrderZoom(
					const char order , //命令参数
					const unsigned int map_scale , //地形图规模
					const int x ,	//显示地形图位置x
					const int y , //显示地形图位置x
					const int align_left , //偏移量x
					const int align_top ,	//偏移量y
					const int paint_scale ,//显示窗口规模
					const int zoom , //缩放倍数
					const int zoom_dis_x ,//缩放选择框显示信息位置x
					const int zoom_dis_y ,//缩放选择框显示信息位置y
					const int angle_point , //旋转角度
					FILE *map ,  //地形图文件指针
					LOCATION **lines ,	//缩放选择框边线覆盖部分的颜色（高度）、位置信息
					int *zoom_pos_x ,	//缩放位置选择坐标x
					int *zoom_pos_y ,	//缩放位置选择坐标y
					int *speed_zoom , //缩放框移动速度
					const int speed_zoom_x , //缩放框移动速度显示坐标x
					const int speed_zoom_y	//缩放框移动速度显示坐标y
				);
				
/*******
读取地形图移动命令
const char order , //命令参数
const unsigned int map_scale ,	//地形图规模 
int *x ,	//地形图显示坐标x
int *y , 	//地形图显示坐标y
const int align_left , //可视窗口偏移量x
const int align_top ,//可视窗口偏移量y
const int paint_scale ,//可视窗口规模
const int bar_length , //中心十字标记规模
const int bar_thick , //中心十字标记厚度
const int bar_color ,//中心十字标记颜色
const int zoom , //缩放倍数
const int zoom_x , //缩放框位置坐标x
const int zoom_y ,//缩放位置选择坐标y
POINT_STORAGE *storage ,//上一次缩放位置信息储存
LOCATION **lines ,//缩放框边界覆盖数据
const int angle_point , //地形图旋转角
FILE *map ,  //地形图文件指针
const int speed , //无人机移动速度
const int center , //窗口中心坐标在地形图中心坐标的位置
const int position_x , //显示无人机位置信息坐标x
const int position_y ,//显示无人机位置信息坐标y
const int max_speed //无人机最大飞行速度
********/
void ReadOrderMove(
					const char order , //命令参数
					const unsigned int map_scale ,	//地形图规模 
					int *x ,	//地形图显示坐标x
					int *y , 	//地形图显示坐标y
					const int align_left , //可视窗口偏移量x
					const int align_top ,//可视窗口偏移量y
					const int paint_scale ,//可视窗口规模
					const int bar_length , //中心十字标记规模
					const int bar_thick , //中心十字标记厚度
					const int bar_color ,//中心十字标记颜色
					const int zoom , //缩放倍数
					const int zoom_x , //缩放框位置坐标x
					const int zoom_y ,//缩放位置选择坐标y
					POINT_STORAGE *storage ,//上一次缩放位置信息储存
					LOCATION **lines ,//缩放框边界覆盖数据
					const int angle_point , //地形图旋转角
					FILE *map ,  //地形图文件指针
					const int speed , //无人机移动速度
					const int center , //窗口中心坐标在地形图中心坐标的位置
					const int position_x , //显示无人机位置信息坐标x
					const int position_y ,//显示无人机位置信息坐标y
					const int max_speed //无人机最大飞行速度
				);
				
/******
读取无人机飞行速度信息
const char order , //命令参数
const int speed_x , //速度显示信息位置x
const int speed_y ,//速度显示信息位置y
const int max_speed , //最大速度
int *speed //无人机飞行速度
******/
void ReadOrderSpeed(
					const char order , //命令参数
					const int speed_x , //速度显示信息位置x
					const int speed_y ,//速度显示信息位置y
					const int max_speed , //最大速度
					int *speed //无人机飞行速度
					);
					
/*******
绘制地形图缩放后的地形
const char order , //命令参数
const unsigned int map_scale , //地形图规模
const int x ,//无人机位置x
const int y ,//无人机位置y 
const int align_left , //偏移量x
const int align_top ,//偏移量y
const int paint_scale ,//可视窗口规模
const int bar_length , //窗口中心标记大小
const int bar_thick , //窗口中心标记厚度
const int bar_color ,//窗口中心标记颜色
int *zoom , //缩放倍数
const int zoom_pos_x ,//缩放窗口位置x 
const int zoom_pos_y ,//缩放窗口位置y
POINT_STORAGE *storage ,//上一次缩放位置信息，一遍图像能够按照原来位置还原
LOCATION **lines ,//缩放选择框边线覆盖部分的颜色（高度）、位置信息
const int angle_point , //地形图旋转角
FILE *map ,  //地形图文件指针
const int speed , //无人机飞行速度
const int center , //可视窗口相对于地形图的位置
const int position_x , //缩放信息显示位置x
const int position_y ,	//缩放信息显示位置y
const int max_speed	//最大飞行速度
******/
void ReadOrderPaintZoom(
					const char order , //命令参数
					const unsigned int map_scale , //地形图规模
					const int x ,//无人机位置x
					const int y ,//无人机位置y 
					const int align_left , //偏移量x
					const int align_top ,//偏移量y
					const int paint_scale ,//可视窗口规模
					const int bar_length , //窗口中心标记大小
					const int bar_thick , //窗口中心标记厚度
					const int bar_color ,//窗口中心标记颜色
					int *zoom , //缩放倍数
					const int zoom_pos_x ,//缩放窗口位置x 
					const int zoom_pos_y ,//缩放窗口位置y
					POINT_STORAGE *storage ,//上一次缩放位置信息，一遍图像能够按照原来位置还原
					LOCATION **lines ,//缩放选择框边线覆盖部分的颜色（高度）、位置信息
					const int angle_point , //地形图旋转角
					FILE *map ,  //地形图文件指针
					const int speed , //无人机飞行速度
					const int center , //可视窗口相对于地形图的位置
					const int position_x , //缩放信息显示位置x
					const int position_y ,	//缩放信息显示位置y
					const int max_speed	//最大飞行速度
	);
	/*********
读取地形图旋转角度
const char order , //命令参数
const unsigned int map_scale , //地形图规模
const int x ,//地形图规模
const int y , //无人机位置y 
const int align_left , //偏移量x
const int align_top ,//偏移量x
const int paint_scale ,//可视窗口规模
const int bar_length , //窗口中心标记大小
const int bar_thick , //窗口中心标记厚度
const int bar_color ,//窗口中心标记颜色
const int zoom , //缩放倍数
const int zoom_x , //缩放窗口位置x 
const int zoom_y ,//缩放窗口位置y
POINT_STORAGE *storage ,//上一次缩放位置信息，一遍图像能够按照原来位置还原
LOCATION **lines ,//缩放选择框边线覆盖部分的颜色（高度）、位置信息
int *angle_point , //地形图旋转角
FILE *map ,  //地形图文件指针
const int speed , //地形图文件指针
const int center , //可视窗口相对于地形图的位置
const int gre_x , //旋转角信息显示位置x
const int gre_y ,//旋转角信息显示位置x
const int max_speed//最大飞行速度
*********/
void ReadOrderAngle(
					const char order , //命令参数
					const unsigned int map_scale , //地形图规模
					const int x ,//地形图规模
					const int y , //无人机位置y 
					const int align_left , //偏移量x
					const int align_top ,//偏移量x
					const int paint_scale ,//可视窗口规模
					const int bar_length , //窗口中心标记大小
					const int bar_thick , //窗口中心标记厚度
					const int bar_color ,//窗口中心标记颜色
					const int zoom , //缩放倍数
					const int zoom_x , //缩放窗口位置x 
					const int zoom_y ,//缩放窗口位置y
					POINT_STORAGE *storage ,//上一次缩放位置信息，一遍图像能够按照原来位置还原
					LOCATION **lines ,//缩放选择框边线覆盖部分的颜色（高度）、位置信息
					int *angle_point , //地形图旋转角
					FILE *map ,  //地形图文件指针
					const int speed , //地形图文件指针
					const int center , //可视窗口相对于地形图的位置
					const int gre_x , //旋转角信息显示位置x
					const int gre_y ,//旋转角信息显示位置x
					const int max_speed//最大飞行速度
					);
/****
个命令读取框架
const unsigned int map_scale ,//地形图规模
const char precision ,//地形图精细度
const char *str//地形图存放位置
****/
char ReadOrder(
			   const unsigned int map_scale ,//地形图规模
			   const char precision ,//地形图精细度
			   const char *str ,//地形图存放位置
			   int *return_flag ,
			   Account *account
			   );

/*****
读取地形图精度、规模信息
******/
void ReadInformation(
			 	   unsigned int *map_scale , 
				   char *precision , 
				   const char *map_str
				   );

#endif
