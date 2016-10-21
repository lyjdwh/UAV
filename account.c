#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "head.h"
#include "SVGA.h"
#include "HANZI.h"
#include "mouse.h"
#include "button.h"
#include "account.h"
#include "input.h"

/**********************************************************************
	功能说明：添加新的账户
	参数说明：p 为要添加的账户
	返回值说明：无
*********************************************************************/
void AddAccount(Account p)
{
	FILE *fp, *tfp;
	int count;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",USERFILE);
		getch();
		exit(1);
	}
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",TUSERFILE);
		getch();
		exit(1);
	}
	fscanf(fp, "%3d", &count);
	fseek(fp, 0, 2);
	fprintf(fp, FORMAT, p.user_name, p.password, p.email);
	count++;
	rewind(fp);
	fprintf(fp, "%3d", count);
	fclose(fp);
	rewind(tfp);
	fprintf(tfp, FORMAT, p.user_name, p.password, p.email);
	fclose(tfp);
}

/**********************************************************************
	功能说明：验证账户
	参数说明：p 为要验证的账户
	返回值说明：通过p中的message元素返回验证结果，若密码正确则1，找不到用户为2，密码错误为3,用户名重复为4
*********************************************************************/
void SearchAccount(Account * p)
{

	FILE *fp,*tfp;
	Account temp;
	int n,i;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",USERFILE);
		getch();
		exit(1);
	}
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",TUSERFILE);
		getch();
		exit(1);
	}
	fscanf(fp,"%3d",&n);
	
		for(i=0;i<n+1;i++)
		{
			fscanf(fp,FORMAT,temp.user_name,temp.password,temp.email);
			if (strcmp(temp.user_name,p->user_name)==0)
				strcpy(p->email,temp.email);
			if(strcmp(temp.user_name,p->user_name)==0&&strcmp(temp.password,p->password)==0)
			{
				rewind(tfp);
				fprintf(tfp, FORMAT,temp.user_name,temp.password,p->email );
				fclose(tfp);
				p->message=1;
				return;
			}
			else if(strcmp(temp.user_name,p->user_name)==0&&strcmp(temp.password,p->password)!=0)
			{
				p->message=3;
				return;
			}
		}
	
	p->message=2;
	fclose(fp);

}

/**********************************************************************
	功能说明：寻找账户
	参数说明：p 为要寻找的账户
	返回值说明：未找到返回-1,找到返回用户注册的序号
*********************************************************************/
int SearchName(Account *p)
{
	FILE *fp;
	int n,i;
	Account temp;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",USERFILE);
		getch();
		exit(1);
	}
	rewind(fp);
	fscanf(fp,"%3d",&n);
	for(i=0;i<n;i++)
	{
		fscanf(fp,FORMAT,temp.user_name,temp.password,temp.email);
		if(strcmp(p->user_name,temp.user_name)==0)
		{
			p->message=4;
			return i;
		}
	}
	fclose(fp);
	p->message=2;
	return -1;
}


/**********************************************************************
	功能说明：对Account中的message信息处理
	参数说明：message 为信息标志，(x,y)为要显示结果的位置
	返回值说明：无
*********************************************************************/
int ProcessMessage(int message,int x,int y)
{
	switch (message)
	{
		case 1:
		{	
			return 1;
		}
		case 2:
		{
			PrintHZ16(x,y,"找不到用户",0xffff,1,1); 
			getch();
			return 0;
		}
		case 3:
		{
			PrintHZ16(x,y,"密码不正确",0xffff,1,1); 
			getch();
			return 0;
		}
		case 4:
		{
			PrintHZ16(x,y,"已经有同名用户",0xffff,1,1); 
			getch();
			return 0;
		}
	}
	return 1;
}
/**********************************************************************
	功能说明：修改账号密码
	参数说明：p为要修改的账户
	返回值说明：无
*********************************************************************/
void ChangePassword(Account p)
{	
	int sta;
	Account temp;
	FILE *fp,*tfp;
	sta=SearchName(&p);
	if(sta==-1)
	{
		ProcessMessage(p.message,400,0);
		return ;
	}
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",USERFILE);
		getch();
		exit(1);
	}
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",TUSERFILE);
		getch();
		exit(1);
	}
	fseek(fp,3+sta*60,0);
	fscanf(fp,FORMAT,temp.user_name,temp.password,temp.email);
	if(strcmp(p.email,temp.email)!=0)
	{
		PrintHZ16(400,0,"邮箱错误",0xffff,1,1);
		return;
	}
	fseek(fp,3+sta*60,0);
	fprintf(fp, FORMAT,p.user_name,p.password,p.email );
	fclose(fp);
	rewind(tfp);
	fprintf(tfp,FORMAT,p.user_name,p.password,p.email);
	fclose(tfp);
	return;

}

/**********************************************************************
	功能说明：读取当前账户信息
	参数说明：p为地址传递的账户的地址
	返回值说明：无
*********************************************************************/
void ReadCurrentAccount(Account *p)
{
	FILE * tfp;
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{	
		ReturnMode();
		printf("can't open %s\n",TUSERFILE);
		getch();
		exit(1);
	}
	rewind(tfp);
	fscanf(tfp,FORMAT,p->user_name,p->password,p->email);
	return;
}

/**********************************************************************
	功能说明：密码加密
	参数说明：p为要加密的账户
	返回值说明：无
*********************************************************************/
void Encrypt(Account *p)
{
	char password[MAXLEN];
	int i;
	strcpy(password,p->password);
	for(i=0;password[i]!='\0';i++)
	{
		password[i]=password[i]+3;
		if(password[i]>'z'||password[i]>'Z'&&password[i]<'a')
		{
			password[i]-=26;
		}
		if(password[i]>'9'&&password[i]<'A')
		{
			password[i]-=10;
		}
	}
	strcpy(p->password,password);
}