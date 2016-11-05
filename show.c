#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <dir.h>

#include "head.h"
#include "account.h"
#include "SVGA.h"
#include "mouse.h"
#include "input.h"
#include "show.h"
#include "button.h"
#include "HANZI.h"

/**************************************************************************
����˵����ȫ�ֳ�ʼ������
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
����ֵ˵������
**************************************************************************/
void UAVInit(UAVPara *para,UAVMap *map)
{

	SetSVGAMode(0x113);
	SetScreenWidth(800L);
	MouseInit();
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
	para->mouse_buffer=(short *)malloc(32*16);
	map->virtual_point=0;

	if(para->mouse_buffer==NULL)
	{

		printf("malloc error in function UAVInit\n");
		getch();
		exit(1);
	}

}
/**************************************************************************
����˵������¼�����ʼ������
����˵������
����ֵ˵������
**************************************************************************/
void LoginInit()
{
	ReadBmp(0,0,"back\\login.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
	
}
/**************************************************************************
����˵������¼�����߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/
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
		if(Button(105,350,440,385)==1)//ȷ��
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
		if(Button(105,418,440,455)==1)//��������
		{
			*flag=3;
			return;
		}
		if(Button(105,485,240,525)==1)//����
		{
			HelpInit("login");
			HelpCheck("login",flag);
			return;
		}
		if(Button(295,485,440,525)==1)//ע��
		{
			*flag=2;
			return;
		}

	}
}

/**************************************************************************
����˵����ע������ʼ������
����˵������
����ֵ˵������
**************************************************************************/

void RegisterInit()
{
	ReadBmp(0,0,"back\\register.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
/**************************************************************************
����˵����ע�� �����߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/
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
				//PrintHZ16(235,385,"�������벻һ��",0xffff,1,1);
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

/**************************************************************************
����˵���������������1��ʼ������
����˵������
����ֵ˵������
**************************************************************************/

void Forget1Init()
{
	ReadBmp(0,0,"back\\forget1.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

/**************************************************************************
����˵���������������1�߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/

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
				//PrintHZ16(225,305,"������֤����",0xffff,1,1);
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

/**************************************************************************
����˵���������������2��ʼ������
����˵������
����ֵ˵������
**************************************************************************/

void Forget2Init()
{
	ReadBmp(0,0,"back\\forget2.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
/**************************************************************************
����˵���������������2�߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/

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
				//PrintHZ16(225,305,"�������벻һ��",0xffff,1,1);
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

/**************************************************************************
����˵�������������ʼ������
����˵����char *page: Ҫ��ʾ�İ���ҳ��
����ֵ˵����
**************************************************************************/

void HelpInit(char *page)
{	
	if(strcmp(page,"login")==0)				//��¼�İ���ҳ��
	{
		ReadBmp(0,0,"back\\helpLog.bmp");	
	} else if(strcmp(page,"register")==0){	//ע��İ���ҳ��
		ReadBmp(0,0,"back\\helpR.bmp");
	}else if(strcmp(page,"forget1")==0)		//��������1�İ���ҳ��
	{
		ReadBmp(0,0,"back\\helpCP1.bmp");	
	}else if(strcmp(page,"forget2")==0)		//��������2�İ���ҳ��
	{
		ReadBmp(0,0,"back\\helpCP2.bmp");
	}else if(strcmp(page,"main")==0)	//��ҳ��İ�������
	{
		ReadBmp(0,0,"back\\HelpC.bmp");
	}else if(strcmp(page,"make_map")==0)	//��ҳ��İ�������
	{
		ReadBmp(0,0,"back\\HelpS.bmp");//���ɵ�ͼ�İ���ҳ��
	}
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

/**************************************************************************
����˵�������������߼���֤
����˵����char *page: Ҫ��ʾ�İ���ҳ��
			int *flag Ҫ���ص�ҳ���־λ
����ֵ˵������
**************************************************************************/

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
			}else if(strcmp(page,"make_map")==0)
			{
				*flag=8;
				break;
			}else if(strcmp(page,"main")==0)
			{
				*flag=4;
				break;
			}
		
		}
	}
}

/**************************************************************************
����˵������������ʼ������
����˵����int error������Ϣ 1:�û��Ѵ��ڣ�2���û������ڣ�3���������4�����벻һ��,5:������֤����,6���ݸ�ʽ����
							7.�ļ��Ѵ��ڣ�8���ļ�������
����ֵ˵������
**************************************************************************/

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
	else if(error==6)
		ReadBmp(220,208,"back\\ErrorD.bmp");
	else if(error==7)
		ReadBmp(220,208,"back\\FileE.bmp");
	else if(error==8)
		ReadBmp(220,208,"back\\ErrorF.bmp");
	
}

/**************************************************************************
����˵������������߼���֤
����˵������
����ֵ˵������
**************************************************************************/

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

/**************************************************************************
����˵�����������ʼ������
����˵������
����ֵ˵������
**************************************************************************/

void MainInit()
{
	ReadBmp(0,0,"back\\app.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

/**************************************************************************
����˵�����������߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/

void MainCheck(UAVPara *para,Account *account,int *flag)
{
	Coord mouse;
	char mouse_butt;
	Account temp;
	FILE *fmap,*flog;
	int number;
	char path[MAXLEN*3],path1[MAXLEN*3],dir[MAXLEN*3];
	strcpy(path,BASEDIR);
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\map.list");
	strcpy(path,BASEDIR);
	strcat(path1,"account\\");
	strcat(path1,account->user_name);
	strcat(path1,"\\log.dat");
	strcpy(path,BASEDIR);
	strcat(dir,"account\\");
	strcat(dir,account->user_name);
	mkdir(dir);
	if(fopen(path,"r+")==NULL)
	{
		fmap=fopen(path,"w");
		rewind(fmap);
		fprintf(fmap,"%3d\t",0);
		fclose(fmap);
	}
		
	if(fopen(path1,"r+")==NULL)
	{
		flog=fopen(path1,"w");
		rewind(flog);
		fprintf(flog,"%3d\t",0);
		fclose(fmap);
	}
		
	
	
	
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		if(Button(60,180,200,310)==1)
		{
			*flag=11;		//�򿪵�ͼҳ���־λ
			break;
		}
		if(Button(220,180,365,310)==1)
		{
			*flag=8;		//���ɵ�ͼҳ���־λ
			break;
		}
		if(Button(60,330,200,480)==1)
		{
			*flag=9;		//������־
			break;
		}
		if(Button(220,325,370,400)==1)
		{
			
			HelpInit("main");
			HelpCheck("main",flag);
			return;
		}				//����  ##############################
		
		if(Button(220,410,365,480)==1)
		{
			exit(1);		//�˳�
		}
		if(Button(385,180,460,480)==1)
		{
			*flag=1;		//���µ�¼
			break;
		}
	}
	
}

/**************************************************************************
����˵�����򿪵�ͼ�����ʼ��
����˵������
����ֵ˵������
**************************************************************************/
void OpenMapInit()
{
	ReadBmp(0,0,"back\\openMap.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

/**************************************************************************
����˵�����򿪵�ͼ�����߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/

void OpenMapCheck(UAVPara *para,Account *account,int *flag,UAVMap *map)
{
	Coord mouse;
	int page=1;
	int new_page=1;
	int number;
	int page_number=0;
	int i,n=5;
	int show_number=0;//��ʾ����Ŀ
	int showed_number=0;
	int perpage_number=0;//ÿһҳ��ʾ����Ŀ
	int postpage_number=0;
	char mouse_butt;
	Account temp;
	FILE *fmap;
	char file_name[MAXLEN];//Ҫ��ʾ��file_name 
	char file_name1[MAXLEN];//Ҫ�򿪵�file_name
	char path[MAXLEN*4];
	strcpy(path,BASEDIR);
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcpy(map->map,path);
	strcat(map->map,"\\");
	strcat(path,"\\map.list");	//��ʽΪ%3d\t%s\t%s\t.....
	fmap=fopen(path,"r+");
	if(fmap==NULL)
	{
		fmap=fopen(path,"w+");
		fprintf(fmap,"%3d\t",0);
		number=0;
	}else 
		fscanf(fmap,"%3d\t",&number);//number�洢��ͼ����Ŀ
	

	page_number=1+number/(n*2);
	show_number=(number-showed_number)/n==0?(number-showed_number)%n:n;
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
	for(i=0;i<show_number;i++)
	{
		
		fscanf(fmap,"%s\t",file_name);
		PrintASC(file_name,410,165+i*40,1,1,0x0000);
	}
	showed_number=showed_number+show_number;
	perpage_number=perpage_number+show_number;
	rewind(fmap);
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		if(Button(40,50,110,115)==1)
		{
			*flag=11;
			return;
		}
		
		if(page>1&&Button(190,435,290,470)==1)
			new_page--;
		if(page<page_number&&Button(510,435,610,470)==1)
			new_page++;
		if(page!=new_page)
		{
			ReadPartBMP(110,140,110,140,575,275,"back\\openMap.bmp");
			//showed_number=showed_number+(new_page-page)*perpage_number;
			if(new_page<page)
				showed_number=showed_number-perpage_number-postpage_number;
			if(new_page>page)
				postpage_number=perpage_number;
			page=new_page;
			show_number=(number-showed_number)/n==0?(number-showed_number)%n:n;
			fscanf(fmap,"%3d\t",&number);//number�洢��ͼ����Ŀ
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
		if(Button(585,500,680,540)==1&&IsFileExisted(account,file_name1)==0)
		{
			ErrorInfo(8);
			ErrorCheck();
			ReadPartBMP(220,208,220,208,360,184,"back\\openMap.bmp");
		}else if(Button(585,500,680,540)==1&&IsFileExisted(account,file_name1)==1)
		{
			strcat(map->map,file_name1);
			strcat(map->map,".mapdat");
			*flag=12;								//��ͼ��ʾҳ��
			break;
		}

	}
}
/**************************************************************************
����˵������־�����ʼ��
����˵������
����ֵ˵������
**************************************************************************/
void LogInit()
{
	ReadBmp(0,0,"back\\logs.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}

/**************************************************************************
����˵������־�����߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/

void LogCheck(UAVPara *para,Account *account,int *flag)
{
	Coord mouse;
	char mouse_butt;
	Account temp;
	FILE *log;
	char path[MAXLEN*3];
	char content[MAXLEN*3];//log ����
	int page=1;
	int new_page=1;
	int n=5,i;
	int page_number;//ҳ��
	int number;
	int per_number;
	strcpy(path,BASEDIR);
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\log.dat");
	log=fopen(path,"r+");
	if(log==NULL)
	{
		log=fopen(path,"w+");
		fprintf(log,"%3d\t",0);
		number=0;
	}else
		fscanf(log,"%3d\t",&number);//number�洢��ͼ����Ŀ
		
	
	page_number=1+number/n;
	for(i=0;i<(page-1)*n;i++)
		fscanf(log,"%s\t",content);
	per_number=(number-(page-1)*n)/n==0?number%n:n;
	if((number-(page-1)*n)==0)
		per_number=0;
	for(i=0;i<per_number;i++)
	{
		fscanf(log,"%s\t",content);
		if(strcmp(content,"ADD")==0)
			PrintASC("add a map",140,165+i*40,1,1,0x0000);
		else if(strcmp(content,"Delete")==0)
			PrintASC("delete a map",140,165+i*40,1,1,0x0000);
		else if(strcmp(content,"Read")==0)
			PrintASC("read a map",140,165+i*40,1,1,0x0000);
		
	}
	rewind(log);
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		if(Button(40,50,110,115)==1)
		{
			*flag=4;
			break;
		}
		
		if(page>1&&Button(145,510,245,545)==1)
		{
			new_page--;
			
		}
		if(page<page_number&&Button(560,510,665,545)==1)
			new_page++;
		if(new_page!=page)
		{
			ReadPartBMP(110,140,110,140,575,275,"back\\logs.bmp");
			page=new_page;
			fscanf(log,"%3d\t",&number);	//number�洢��ͼ����Ŀ
			for(i=0;i<(page-1)*n;i++)
				fscanf(log,"%s\t",content);
			per_number=(number-(page-1)*n)/n==0?number%n:n;
			if((number-(page-1)*n)==0)
				per_number=0;
			for(i=0;i<per_number;i++)
			{
				
				fscanf(log,"%s\t",content);
				if(strcmp(content,"ADD")==0)
					PrintASC("add a map",140,165+i*40,1,1,0x0000);
				else if(strcmp(content,"Delete")==0)
					PrintASC("delete a map",140,165+i*40,1,1,0x0000);
				else if(strcmp(content,"Read")==0)
					PrintASC("read a map",140,165+i*40,1,1,0x0000);
			}
			rewind(log);
		}
			
	}
}
/**************************************************************************
����˵�������ɵ�ͼ�����ʼ��
����˵������
����ֵ˵������
**************************************************************************/
void MakeMapInit()
{
	ReadBmp(0,0,"back\\makeMap.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
/**************************************************************************
����˵�������ɵ�ͼ�����߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/
void MakeMapCheck(UAVPara *para,UAVMap *map,int *flag,Account *account)
{
	Coord mouse;
	FILE *fmap;
	char mouse_butt;
	char path[MAXLEN*3];
	char map_scale[20]={""};
	char precison[20]={""};
	char virtual_point[20]={""};
	char map_name[20]={""};
	char height[20]={""};
	char file_name[30];
	int l1,l2,l3,l4,l5,i;
	int number;//��ͼ����Ŀ
	strcpy(map->map,BASEDIR);
	strcat(map->map,"account\\");
	strcat(map->map,account->user_name);
	strcat(map->map,"\\");
	strcpy(path,BASEDIR);
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\map.list");	//��ʽΪ%3d\t%s\t%s\t.....
	fmap=fopen(path,"r+");
	if(fmap==NULL)
	{
		fmap=fopen(path,"w+");
		fprintf(fmap,"%3d\t",0);
		number=0;
	}else 
		fscanf(fmap,"%3d\t",&number);//number�洢��ͼ����Ŀ
	rewind(fmap);
	while(1)
	{
		ReadMouse(&mouse.x,&mouse.y,&mouse_butt);
		MouseCopy(&mouse,para->mouse_buffer);
		MouseShow(&mouse);
		MouseReshow(&mouse,para->mouse_buffer);
		TextBox(255,170,380,200,map_scale,1,"make_map");
		TextBox(575,170,700,205,height,1,"make_map");
		TextBox(255,240,380,275,precison,1,"make_map");
		TextBox(580,240,700,270,virtual_point,1,"make_map");
		TextBox(255,310,705,335,map_name,1,"make_map");
		map->map_scale=atoi(map_scale);
		map->precison=atoi(precison);
		map->virtual_point=atoi(virtual_point);
		map->height=atoi(height);
	
		if(Button(245,445,395,505)==1)
		{
	
			HelpInit("make_map");
			HelpCheck("make_map",flag);
			return;
	
			//����
		}
		if(Button(440,445,585,505)==1)
		{
			if(map->map_scale<=0||map->precison<0||map->precison>3||map->height<=0||map->virtual_point<0)
			{
				ErrorInfo(6);
				ErrorCheck();
				ReadPartBMP(80,145,80,145,650,275,"back\\makeMap.bmp");
			}else if(IsFileExisted(account,map_name)==1)
			{
				ErrorInfo(7);
				ErrorCheck();
				ReadPartBMP(80,145,80,145,650,275,"back\\makeMap.bmp");
			}else{
				map->map_scale=pow(2,map->map_scale)+1;
				strcat(map->map,map_name);
				strcat(map->map,".mapdat");
				rewind(fmap);
				fprintf(fmap,"%3d\t",number+1);
				rewind(fmap);
				fscanf(fmap,"%3d\t",&number);
				for(i=0;i<number-1;i++)
					fscanf(fmap,"%s\t",file_name);
				fprintf(fmap,"%s\t",map_name);
				fclose(fmap);
				*flag=10;
				return ;
			}
		}
			if(Button(40,50,110,115))
			{
			*flag=4;
			return;
			}
	
	}
		
	
}
/**************************************************************************
����˵����ѡ������ʼ��
����˵������
����ֵ˵������
**************************************************************************/
void ChooseInit()
{
	ReadBmp(0,0,"back\\choose.bmp");
	SetMouseRange(0,0,800,600);
	SetMousePosition(400,300);
}
/**************************************************************************
����˵����ѡ������߼���֤
����˵����UAVPara *para:ȫ�ֻ�������
		  Account *account �˻���Ϣ
		  int *flagҳ���־λ
����ֵ˵������
**************************************************************************/
void ChooseCheck(UAVPara *para,Account *account,int *flag)
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
		if(Button(40,50,110,115)==1)
		{
			*flag=4;//���ش򿪵�ͼҳ��
			return ;
		}
		if(Button(240,220,370,350))
		{
			//����
			*flag=13;
			return ;
		}
		if(Button(490,220,630,350))
		{
			*flag=7;
			return ;//ɽ�أ���Ұ
		}
	}
}
/**************************************************************************
����˵����ɾ��һ����ͼ
����˵����
		  Account *account �˻���Ϣ
		
����ֵ˵������
**************************************************************************/
void DeleteMap(Account *account)
{
	char path[MAXLEN*3];
	
	int number;
	FILE *fmap;
	strcpy(path,BASEDIR);
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\map.list");	//��ʽΪ%3d\t%s\t%s\t.....
	fmap=fopen(path,"r+");
	fscanf(fmap,"%3d\t",&number);
	rewind(fmap);
	fprintf(fmap,"%3d\t",number-1);
	fclose(fmap);
}

/**************************************************************************
����˵�������һ����־
����˵����
		  Account *account �˻���Ϣ
		  int *log Ҫ��ӵ���־��Ϣ
����ֵ˵������
**************************************************************************/
void AddLog(Account *account,char *log)
{
	char path[MAXLEN*4];
	char temp[MAXLEN*2];
	int number,i;
	FILE *flog;
	strcpy(path,BASEDIR);
	
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\log.dat");	//��ʽΪ%3d\t%s\t%s\t.....
	flog=fopen(path,"r+");
	fscanf(flog,"%3d\t",&number);
	for(i=0;i<number;i++)
		fscanf(flog,"%s\t",temp);
	fprintf(flog,"%s\t",log);
	rewind(flog);
	fprintf(flog,"%3d\t",number+1);
	fclose(flog);
}	

/**************************************************************************
����˵�����ж��ļ��Ƿ����
����˵����
		  Account *account �˻���Ϣ
		  char *file_name Ҫ���ҵ��ļ�
����ֵ˵����1������ 0��������
**************************************************************************/	
int IsFileExisted(Account *account,char *file_name)
{
	int number,temp;
	int i;
	FILE *fmap;
	char file_name1[MAXLEN];//Ҫ��ʾ��file_name 
	char path[MAXLEN*4];
	strcpy(path,BASEDIR);
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\map.list");	//��ʽΪ%3d\t%s\t%s\t.....
	fmap=fopen(path,"r+");
	if(fmap==NULL)
	{
		fmap=fopen(path,"w+");
		fprintf(fmap,"%3d\t",0);
		number=0;
	}else 
		fscanf(fmap,"%3d\t",&number);//number�洢��ͼ����Ŀ
	rewind(fmap);
	fscanf(fmap,"%3d\t",&temp);
	for(i=0;i<number;i++)
	{
		fscanf(fmap,"%s\t",file_name1);
		if(strcmp(file_name1,file_name)==0)
			return 1;
	}
	return 0;
}
