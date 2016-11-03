#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "SVGA.h"
#include "HANZI.h"
#include "head.h"
#include "account.h"
#include "mouse.h"
#include "button.h"
#include "input.h"

/**********************************************************************
	功能说明: 文本框输入
	参数说明：int x1, int y1, int x2, int y2 为文本框的左上，右下的坐标，
			  *str 保存输入的字符串
			  int flag 为0时为普通文本框，为0时为密码输入框
			  char *flag 为文本框所在页面
	返回值说明：无
*********************************************************************/
void TextBox(int x1,int y1,int x2,int y2,char *str,int flag,char *page)
{
	Coord mouse;
	char mouse_butt;
	char ka;
	char str1[MAXLEN];
	char i=0;
	ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
	
	if((mouse.x>x1)&&(mouse.x<x2)&&(mouse.y>y1)&&(mouse.y<y2)&&(mouse_butt==1))
	{	
			if(strcmp(page,"login")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\login.bmp");
			}
			if(strcmp(page,"register")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\register.bmp");
			}
			if(strcmp(page,"forget")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\forget1.bmp");
			}
			if(strcmp(page,"forget1")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\forget2.bmp");
			}
			if(strcmp(page,"open_map")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\openMap.bmp");
			}
			if(strcmp(page,"make_map")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\makeMap.bmp");
			}
		while((ka=getch())!=13)
		{
			if(strcmp(page,"login")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\login.bmp");
			}
			if(strcmp(page,"register")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\register.bmp");
			}
			if(strcmp(page,"forget")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\forget1.bmp");
			}
			if(strcmp(page,"open_map")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\openMap.bmp");
			}
			if(strcmp(page,"make_map")==0)
			{
				ReadPartBMP(x1,y1,x1,y1,220,35,"back\\makeMap.bmp");
			}
			if((ka>='0'&&ka<='9')||(ka>='a'&&ka<='z')||(ka>='A'&&ka<='Z')||ka==64||ka==46)
			{	

				str[i]=ka;
				str1[i]='*';
				i++;
				str[i]='\0';
				str1[i]='\0';
				if(flag==1)		
				{	
					PrintASC(str,x1+5,y1+10,1,1,0x0000);
				}else if(flag==0){	//密码
					PrintASC(str1,x1+5,y1+10,1,1,0x0000);//0x0000为黑色
				}
 	 	
			}
			

			if(ka==8&&i>0)
			{	i--;
				str[i]='\0';
				str1[i]='\0'; 	 	
				if(flag==1)
				{	
					PrintASC(str,x1+5,y1+10,1,1,0x0000);
				}else if(flag==0){
					PrintASC(str1,x1+5,y1+10,1,1,0x0000);
				}
			}


		}
	}
}