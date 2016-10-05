#ifndef _mouse_h_
#define _mouse_h_
typedef struct 
{
	int x;
	int y;
} Coord;	//鼠标坐标

void MouseInit(void);
void SetMouseRange(int left,int top,int right,int bottom);
void SetMousePositon(int x,int y);
void  MouseSetSpeed(int vx,int vy);
void ReadMouse(int *mouse_x,int *mouse_y,char *mouse_butt );
void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt );
void MouseCopy(Coord *CoordXY,char *mouse_buffer) ;
void MouseReshow(Coord *CorrdXY,char *mouse_buffer);
void MouseShow(Coord *CoordXY);


#endif