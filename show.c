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
	SetMouseRange(0,0,800,600);
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
			//ReadPartBMP(225,310,225,310,150,30,"back\\login.bmp");
			ReadPartBMP(220,208,220,208,360,184,"back\\login.bmp");
		}
		if(Button(105,418,440,455)==1)//忘记密码
		{
			*flag=3;
			return;
		}
		if(Button(105,485,240,525)==1)//帮助
		{
			HelpInit("login");
			HelpCheck("login",flag);
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
	SetMouseRange(0,0,800,600);
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
				//ReadPartBMP(235,385,235,385,400,60,"back\\register.bmp");
				ReadPartBMP(220,208,220,208,360,184,"back\\register.bmp");
			}else if(strcmp(account->password,temp.password)!=0)
			{
				//PrintHZ16(235,385,"两次密码不一致",0xffff,1,1);
				//getch();
				//ReadPartBMP(235,385,235,385,400,60,"back\\register.bmp");
				ErrorInfo(4);
				ErrorCheck();
				ReadPartBMP(220,208,220,208,360,184,"back\\register.bmp");
			}else{
				AddAccount(*account);
				*flag=4;
				return;
			}


		}
		if(Button(90,500,230,535)==1)
		{
			HelpInit("register");
			HelpCheck("register",flag) ;
			return;
		}
		if(Button(280,500,425,535)==1)
		{
			*flag=1;
			return;
		}
	}
}
void Forget1Init()
{
	ReadBmp(0,0,"back\\forget1.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
void Forget1Check(UAVPara *para,Account *account,int *flag)
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
		TextBox(224,205,445,240,account->user_name,1,"forget");
		TextBox(224,260,445,295,temp.email,1,"forget");
		
		if(Button(295,485,440,525)==1)
		{
			*flag=2;
			return ;
		}
		if(Button(105,350,440,390)==1)
		{	SearchAccount(account);
			if(account->message==2)
			{
				ProcessMessage(account->message,225,305);
				
				//ReadPartBMP(225,305,225,305,400,60,"back\\forget1.bmp");
				ReadPartBMP(220,208,220,208,360,184,"back\\forget1.bmp");
			}else if(strcmp(account->email,temp.email)!=0)
			{
				//PrintHZ16(225,305,"邮箱验证错误",0xffff,1,1);
				//getch();
				//ReadPartBMP(225,305,225,305,400,60,"back\\forget1.bmp");
				ErrorInfo(5);
				ErrorCheck();
				ReadPartBMP(220,208,220,208,360,184,"back\\forget1.bmp");
			}else{
				*flag=6;
				return;
			}
			
		}
		if(Button(105,420,440,455)==1)
		{
			*flag=1;
			return;
		}
		if(Button(105,485,240,525)==1)
		{
			HelpInit("forget1");
			HelpCheck("forget1",flag);
			return;
		}
		
	}

}
void Forget2Init()
{
	ReadBmp(0,0,"back\\forget2.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
void Forget2Check(UAVPara *para,Account *account,int *flag)
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
		TextBox(225,205,450,240,account->password,0,"forget1");
		TextBox(225,260,450,300,temp.password,0,"forget1");
		if(Button(105,348,440,385)==1)
		{
			
			if(strcmp(account->password,temp.password)!=0)
			{
				//PrintHZ16(225,305,"两次密码不一致",0xffff,1,1);
				//getch();
				//ReadPartBMP(225,305,225,305,400,60,"back\\forget2.bmp");
				ErrorInfo(4);
				ErrorCheck();
				ReadPartBMP(220,208,220,208,360,184,"back\\forget2.bmp");
			}else{
				ChangePassword(*account);
				*flag=4;
				return;
			}
		}
		if(Button(105,415,440,455)==1)
		{
			*flag=1;
			return;
		}
		if(Button(105,485,240,525)==1)
		{
			HelpInit("forget2");
			HelpCheck("forget2",flag);
			return;
		}
		if(Button(290,490,440,525)==1)
		{
			*flag=2;
			return;
		}
	}
}
void HelpInit(char *page)
{	
	if(strcmp(page,"login")==0)
	{
		ReadBmp(0,0,"back\\helpLog.bmp");
	} else if(strcmp(page,"register")==0){
		ReadBmp(0,0,"back\\helpR.bmp");
	}else if(strcmp(page,"forget1")==0)
	{
		ReadBmp(0,0,"back\\helpCP1.bmp");	
	}else if(strcmp(page,"forget2")==0)
	{
		ReadBmp(0,0,"back\\helpCP2.bmp");
	}else if(strcmp(page,"main")==0)	//主页面的帮助界面
	{
		ReadBmp(0,0,"back\\app.bmp");
	}
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
void HelpCheck(char *page,int *flag)
{	
	Coord mouse;
	char mouse_butt;
	short mouse_buffer[16*16];
	while(1)
	{	
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,mouse_buffer);
		
			if(Button(40,50,110,115)==1)
		{
				if(strcmp(page,"login")==0)
			{
				*flag=1;
				break;
			} else if(strcmp(page,"register")==0){
				*flag=2;
				break;
			}else if(strcmp(page,"forget1")==0)
			{			
				break;
			}else if(strcmp(page,"forget2")==0)
			{
				*flag=6;
				break;
			}
		}
	}
}
/*
1:用户已存在，2：用户不存在，3：密码错误，4：密码不一致,5:邮箱验证错误
*/
void ErrorInfo(int error)
{	if(error==1)
		ReadBmp(220,208,"back\\userE.bmp");
	else if(error==2)
		ReadBmp(220,208,"back\\noUser.bmp");
	else if(error==3)
		ReadBmp(220,208,"back\\passE.bmp");
	else if(error==4)
		ReadBmp(220,208,"back\\diffP.bmp");
	else if(error==5)
		ReadBmp(220,208,"back\\emailCE.bmp");
}
void ErrorCheck()
{	
	Coord mouse;
	char mouse_butt;
	short mouse_buffer[16*16];
	while(1)
	{	
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,mouse_buffer);
		if (Button(540,210,580,253)==1)//320,2,360,45
		{
			break;
		}
	}
}
void MainInit()
{
	ReadBmp(0,0,"back\\app.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

void MainCheck(UAVPara *para,Account *account,int *flag)
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
		if(Button(60,180,200,310)==1)
		{
			*flag=7;		//打开地图页面标志位
			break;
		}
		if(Button(220,180,365,310)==1)
		{
			*flag=8;		//生成地图页面标志位
			break;
		}
		if(Button(60,330,200,480)==1)
		{
			*flag=9;		//运行日志
			break;
		}
		if(Button(220,325,370,400)==1)
		{
							//帮助  ##############################
		}
		if(Button(220,410,365,480)==1)
		{
			exit(1);		//退出
		}
		if(Button(385,180,460,480)==1)
		{
			*flag=1;		//从新登录
			break;
		}
	}
	
}

void OpenMapInit()
{
	ReadBmp(0,0,"back\\openMap.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

void OpenMapCheck(UAVPara *para,Account *account,int *flag)
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
}
}
