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
#include "show.h"
#include "mouse.h"
#include "button.h"	
#include "PaintMap.h" 
#include "InfoShow.h"
#include "MakeMap.h"
#include "ProMap.h"




void main()
{
	int flag=1;
	UAVPara para;
	UAVMap map;
	Account account;
	account.message=0;
	strcpy(account.user_name,"");
	UAVInit(&para,&map);
	while(1)
	{
		if(flag==1)												//登录
		{
			LoginInit();
			LoginCheck(&para,&account,&flag);
		}
		if(flag==2)												//注册
		{
			RegisterInit();
			RegisterCheck(&para,&account,&flag);
		}
		if(flag==3)												//忘记密码
		{
			Forget1Init();
			Forget1Check(&para,&account,&flag);
		}
		if(flag==4)												//进入界面
		{
			
			MainInit();
			MainCheck(&para,&account,&flag);
			
		}
		if(flag==5)												//帮助
		{
			exit(1);
		}
		if(flag==6)												//忘记密码的下一页
		{
			Forget2Init();
			Forget2Check(&para,&account,&flag);
		}
		if(flag==7)												//打开地图
		{
			OpenMapInit();
			OpenMapCheck(&para,&account,&flag,&map);
		}
		if(flag==8)											//生成地图
		{
			MakeMapInit();
			MakeMapCheck(&para,&map,&flag,&account);
		}
		if(flag==9)												//日志
		{
			LogInit();
			LogCheck(&para,&account,&flag);
		}
		if(flag==10)											//地图显示页面
		{
			ConstructeMap(map.map_scale,map.virtual_point,map.precison,&(map.height),map.map);
			AddLog(&account , "ADD");
			AddInformation(&(map.map_scale) , &(map.precison) , map.map);
			StartSmooth(map.map, map.map_scale , 1 ,7);
			StartMidValue(map.map, map.map_scale , 1 , 3); 
			//StartAddCity(map.map , map.map_scale , 1 , 7);
			ReadOrder(map.map_scale , map.precison , map.map , &flag , &account);						
		}
		if(flag==11)											//选择页面
		{
			ChooseInit();
			ChooseCheck(&para,&account,&flag);
		}
		if(flag == 12)
		{
			ReadInformation(&(map.map_scale) , &(map.precison) , map.map);
			ReadOrder(map.map_scale , map.precison , map.map , &flag , &account);	
		}
		if(flag == 13)
		{
			ReadInformation(&(map.map_scale) , &(map.precison) , ".\\account\\City.Map");
			ReadOrder(map.map_scale , map.precison , ".\\account\\City.Map" , &flag , &account);	
		}
	}
}
/*
ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		if(Button(40,50,110,115)==1)
		{
			*flag=4;
			break;
		}
		
		if(page>1&&Button(190,435,290,470)==1)
			new_page--;
		if(page<page_number&&Button(510,435,610,470)==1)
			new_page++;
		if(page!=new_page)
		{
			ReadPartBMP(110,140,110,140,575,275,"back\\openMap.bmp");
			showed_number=showed_number+(new_page-page)*perpage_number;
			if(new_page<page)
				showed_number=showed_number-perpage_number-postpage_number;
			if(new_page>page)
				postpage_number=perpage_number;
			page=new_page;
			show_number=(number-showed_number)/n==0?(number-showed_number)%n:n;
			if(number-showed_number==0)
				show_number=0;
			fscanf(fmap,"%3d\t",&number);//number存储地图的数目
			for(i=0;i<showed_number;i++)
				fscanf(fmap,"%s\t",file_name);
			for(i=0;i<show_number;i++)
			{
				fscanf(fmap,"%s\t",file_name);
				PrintASC(file_name,140,165+i*40,1,1,0x0000);
			}
			showed_number=showed_number+show_number;
			perpage_number=show_number;
			show_number=(number-showed_number)/n==0?(number-showed_number)%n:n;
			if(number-showed_number==0)
				show_number=0;
			for(i=0;i<show_number;i++)
			{
				
				fscanf(fmap,"%s\t",file_name);
				PrintASC(file_name,410,165+i*40,1,1,0x0000);
			}
			showed_number=showed_number+show_number;
			perpage_number=perpage_number+show_number;
					
			rewind(fmap);
		}
		TextBox(210,500,560,540,file_name1,1,"open_map");
		if(strlen(file_name1)>0&&Button(585,500,680,540)==1)//确认
		{
			*flag=10;								//地图显示页面
			break;
		}
*/
