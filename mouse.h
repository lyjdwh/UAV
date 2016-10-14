#ifndef _MOUSE_H_
#define _MOUSE_H_
typedef struct 
{
	int x;
	int y;
} Coord;	//ЪѓБъзјБъ

void MouseInit(void);
void SetMouseRange(int left,int top,int right,int bottom);
void SetMousePosition(int x,int y);
void  MouseSetSpeed(int vx,int vy);
void ReadMouse(int *mouse_x,int *mouse_y,char *mouse_butt );
void ReadMouse2(int *mouse_x,int *mouse_y,char *mouse_butt );
void MouseCopy(Coord *CoordXY,short  *mouse_buffer) ; 
void MouseReshow(Coord *CoordXY,short *mouse_buffer);
void MouseShow(Coord *CoordXY);


#endif