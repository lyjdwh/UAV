#ifndef _HEAD_H_
#define _HEAD_H_

typedef struct UAVPara
{
	short *mouse_buffer;
} UAVPara;
typedef struct UAVMap
{
	unsigned int map_scale;	//地图大小,2^n+1
	char precison;			//地图精细度
	int virtual_point;		//虚拟点高度,默认值为0
	char map_user[20];		//地图文件名
	int height[4];			//地图4个角点高度
	char diamod;			//若virtual_point=0则为3,否则为4
} UAVMap;
	
#endif