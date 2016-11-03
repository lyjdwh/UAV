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
	char map[20];		//地图文件名
	int height;			//地图4个角点高度

} UAVMap;
	
#endif
/*
void OpenMapCheck(UAVPara *para,Account *account,int *flag)
{
	Coord mouse;
	int page=1;
	int new_page=1;
	int number;
	int page_number=0;
	int i,n=5;
	int show_number;//显示的数目
	int showed_number=0;
	int perpage_number;//每一页显示的数目
	int postpage_number;//上一页显示的数目
	char mouse_butt;
	Account temp;
	FILE *fmap;
	char file_name[MAXLEN];//要显示的file_name
	char file_name1[MAXLEN];//要打开的file_name
	char path[MAXLEN*2];
	strcat(path,"account\\");
	strcat(path,account->user_name);
	strcat(path,"\\map.list");	//格式为%3d\t%s\t%s\t.....
	fmap=fopen(path,"r+");
	if(fmap==NULL)
	{
		fmap=fopen(path,"w+");
	}
	fscanf(fmap,"%3d\t",&number);//number存储地图的数目
	page_number=1+number/(n*2);
	show_number=(number-showed_number)/n==0?(number-showed_number)%n:n;
	if(number==0)
		show_number=0;
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
	if(number==0)
		show_number=0;
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
	}
} */