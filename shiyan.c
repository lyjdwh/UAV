#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <time.h>
#include <conio.h>

#include "account.h"
#include "SVGA.h"

void AddUser(Account p)
{
	FILE *fp, *tfp;
	int count;
	fp = fopen(USERFILE, "r+");
	if (fp == NULL)
		puts("open file wrong");
	tfp = fopen(TUSERFILE, "r+");
	if (tfp == NULL)
	{
		puts("user temporary file open wrong");
	}
	fscanf(fp, "%3d", &count);
	fseek(fp, 0, 2);
	fprintf(fp, FORMAT, p.user_name, p.password, 0);
	count++;
	rewind(fp);
	fprintf(fp, "%3d", count);
	fclose(fp);
	rewind(tfp);
	fprintf(tfp, FORMAT, p.user_name, p.password, 0);
	fclose(tfp);
}
void main()
{
	Account account;
	strcpy(account.user_name,"lyjdwh");
	strcpy(account.password,"abc201314");
	account.message=0;
	AddUser(account);
}