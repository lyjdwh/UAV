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




void main()
{
	int flag=1;
	UAVPara para;
	Account account;
	account.message=0;
	strcpy(account.user_name,"");
	UAVInit(&para);
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
			ForgetInit();
			ForgetCheck(&para,&account,&flag);
		}
		if(flag==4)												//进入界面
		{
			exit(1);
			
		}
		if(flag==5)												//帮助
		{
			exit(1);
		}
		if(flag==6)												//忘记密码的下一页
		{
			exit(1);
		}

	}
}