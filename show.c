#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "head.h"
#include "account.h"
#include "SVGA.h"
#include "mouse.h"
#include "input.h"
#include "show.h"
#include "button.h"
#include "HANZI.h"


void UAVInit(UAVPara *para)
{

	SetSVGAMode(0x113);
	SetScreenWidth(1600L);
	MouseInit();
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
	para->mouse_buffer=(short *)malloc(32*16);
	if(para->mouse_buffer==NULL)
	{
		ReturnMode();
		printf("malloc error in function UAVInit\n");
		getch();
		exit(1);
	}

}
/**************************************************************************
功能说明：登录界面初始化设置
参数说明：
返回值说明：
**************************************************************************/
void LoginInit()
{
	ReadBmp(0,0,"back\\login.bmp");
	SetMouseRange(0,0,600,800);
	SetMousePosition(400,300);
	
}

void LoginCheck(UAVPara *para,Account *account,int *flag)
{
	Coord mouse;
	char mouse_butt;
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		TextBox(225,205,445,240,account->user_name,1,"login");
		TextBox(225,260,445,295,account->password,0,"login");
		if(Button(105,350,440,385)==1)//确认
		{
			SearchAccount(account);
			if(ProcessMessage(account->message,225,310)==1)
			{	
				ReadPartBMP(225,310,225,310,150,30,"back\\login.bmp");
				*flag=4;
				return;
			}
			ReadPartBMP(225,310,225,310,150,30,"back\\login.bmp");
		}
		if(Button(105,418,440,455)==1)//忘记密码
		{
			*flag=3;
			return;
		}
		if(Button(105,485,240,525)==1)//帮助
		{
			*flag=5;
			return;
		}
		if(Button(295,485,440,525)==1)//注册
		{
			*flag=2;
			return;
		}

	}
}
void RegisterInit()
{
	ReadBmp(0,0,"back\\register.bmp");
	SetMouseRange(0,0,600,800);
	SetMousePosition(400,300);
}
void RegisterCheck(UAVPara *para,Account *account,int *flag)
{
	Coord mouse;
	char mouse_butt;
	Account temp;
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		TextBox(235,180,455,215,account->user_name,1,"register");
		TextBox(235,230,455,265,account->password,0,"register");
		TextBox(235,285,455,320,temp.password,0,"register");
		TextBox(235,340,455,380,account->email,1,"register");
		if(Button(90,425,430,465)==1)
		{
			SearchName(account);
			if(account->message==4)
			{
				ProcessMessage(account->message,235,385);
				ReadPartBMP(235,385,235,385,400,60,"back\\register.bmp");
			}else if(strcmp(account->password,temp.password)!=0)
			{
				PrintHZ16(235,385,"两次密码不一致",0xffff,1,1);
				getch();
				ReadPartBMP(235,385,235,385,400,60,"back\\register.bmp");
			}else{
				AddAccount(*account);
				*flag=4;
				return;
			}


		}
		if(Button(90,500,230,535)==1)
		{
			*flag=5;
			return;
		}
		if(Button(280,500,425,535)==1)
		{
			*flag=1;
			return;
		}
	}
}
void ForgetInit()
{
	ReadBmp(0,0,"back\\forget1.bmp");
	SetMouseRange(0,0,600,800);
	SetMousePosition(400,300);
}
void ForgetCheck(UAVPara *para,Account *account,int *flag)
{
	Coord mouse;
	char mouse_butt;
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		TextBox(224,205,445,240,account->user_name,1,"forget");
		TextBox(224,260,445,295,account->password,0,"forget");
		
		if(Button(295,485,440,525)==1)
		{
			*flag=2;
			return ;
		}
		if(Button(105,350,440,390)==1)
		{
			*flag=6;
			return;
		}
		if(Button(105,420,440,455)==1)
		{
			*flag=1;
			return;
		}
		if(Button(105,485,240,525)==1)
		{
			*flag=5;
			return;
		}
		
	}

}