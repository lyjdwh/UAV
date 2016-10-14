#ifndef _ACCOUNT_H_
#define _ACCOUNT_H

#define USERFILE "account\\account.txt"
#define TUSERFILE "account\\taccount.txt"

#define FORMAT "%20s%20s%20s"
#define MAXLEN 20

typedef struct {
	char user_name[MAXLEN];
	char password[MAXLEN];
	char email[MAXLEN];
	int message;	//初始化为0，若密码正确则1，找不到用户为2，密码错误为3,用户名重复为4
}Account;


int ProcessMessage(int message,int x,int y);
void Encrypt(Account *);
void SearchAccount(Account * p);
void AddAccount(Account p);
int SearchName(Account *p);
void ChangePassword(Account p);
void ReadCurrentAccount(Account *p);
void Encrypt(Account *p);
#endif