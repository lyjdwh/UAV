/*******************************
地形图显示的函数的头文件
*******************************/

#ifndef _InfoShow_H_
#define _InfoShow_H_


/****
辅助函数，为DisplayData（）的辅助显示
int char_set[16][16] ,//传入的字符矩阵
int x ,//显示信息的位置x
int y ,//显示信息的位置y 
int color //显示信息的颜色
*****/
void DisplayDataOrder(
					int char_set[16][16] ,//传入的字符矩阵
					int x ,//显示信息的位置x
					int y ,//显示信息的位置y 
					int color //显示信息的颜色
					);
/******
显示希望得到的数据
*****/
void DisplayData(
				 int x ,	//输出位置X
				 int y ,	//输出位置y
				 char *str ,//输出内容
				 const int color
				);
/******
将得到的数据按照用户希望的格式构建成字符串
char *format , //输出的字符串格式
int data_1 , //输入的数据1
int data_2 , //输入的数据2
int x , //输出位置x
int y 	//输出位置y
******/
void ConstructeStr(
				   char *title ,
				   char *format , //输出的字符串格式
				   int data_1 , //输入的数据1
				   int data_2 , //输入的数据2
				   int x , //输出位置x
				   int y 	//输出位置y
				   );
void DisplayStatus(char *str,
				char *file,
				int x ,
				int y);
#endif